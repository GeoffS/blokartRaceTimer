#include "StartingSequenceMaker.h"

StartingSequenceMaker::StartingSequenceMaker(ULONG startTimesArray[], bool spkrStatesArray[], bool fpStatesArray[], const int maxNumStates): startTimesArraySize(maxNumStates)
{
	startTimes_ms = startTimesArray;
	fpStates = fpStatesArray;
	spkrStates = spkrStatesArray;
}

StartingSequenceMaker::~StartingSequenceMaker()
{
}

const ULONG pipPulse_ms = 120ul;
const ULONG shortPulse_ms = 250ul;
const ULONG mediumPulse_ms = 1000ul;
const ULONG longPulse_ms = 2000ul;

const ULONG raceTime_min = 5ul;
const ULONG preDelay_ms = 5000ul;
const ULONG SEC_PER_MIN = 60;
const ULONG MSEC_PER_SEC = 1000ul;

void StartingSequenceMaker::initShort(int delayTime_s, bool spkr=true, bool light=false)
{
  //for(int i=0; i<numSteps; i++) startTimes_ms[i] = 0ul;

  startTimes_ms[0] = 0;
  startTimes_ms[1] = shortPulse_ms;
  startTimes_ms[2] = delayTime_s * MSEC_PER_SEC;
  
  spkrStates[0]  = spkr;
  spkrStates[1]  = false;
  spkrStates[2]  = spkr;
  
  fpStates[0] = light;
  fpStates[1] = false;
  fpStates[2] = light;
  
  stepCounter = 2;
}


void StartingSequenceMaker::addPulse(ULONG pulseDuration_ms, ULONG delayTime_s, bool spkr=true, bool light=false)
{
  if (stepCounter >= startTimesArraySize) return;
  
  startTimes_ms[stepCounter + 1] = startTimes_ms[stepCounter] + pulseDuration_ms;
  startTimes_ms[stepCounter + 2] = startTimes_ms[stepCounter] + (delayTime_s * MSEC_PER_SEC);
  
  spkrStates[stepCounter + 1] = false;
  spkrStates[stepCounter + 2] = spkr;
  
  fpStates[stepCounter + 1] = false;
  fpStates[stepCounter + 2] = light;
  
  stepCounter += 2;
}

void StartingSequenceMaker::addShort(int timeToNextPulse_s, bool spkr=true, bool light=false)
{
  addPulse(shortPulse_ms, timeToNextPulse_s, spkr, light);
}

void StartingSequenceMaker::StartingSequenceMaker::addMedium(int timeToNextPulse_s, bool spkr=true, bool light=false)
{
  addPulse(mediumPulse_ms, timeToNextPulse_s, spkr, light);
}

void StartingSequenceMaker::addLong(int timeToNextPulse_s, bool spkr=true, bool light=false)
{
  addPulse(longPulse_ms, timeToNextPulse_s, spkr, light);
}

void StartingSequenceMaker::addPip(int timeToNextPulse_s, bool spkr=true, bool light=false)
{
  addPulse(pipPulse_ms, timeToNextPulse_s, spkr, light);
}

void StartingSequenceMaker::addRaceEnd(int stateDuration_s, bool spkr=false, bool light=true)
{
  if (stepCounter >= startTimesArraySize) return;
  
  startTimes_ms[stepCounter + 1] = startTimes_ms[stepCounter] + (stateDuration_s * MSEC_PER_SEC);
  
  spkrStates[stepCounter] = spkr;
  spkrStates[stepCounter + 1] = false;
  
  fpStates[stepCounter] = light;
  fpStates[stepCounter + 1] = false;
  
  stepCounter += 2;
}

int StartingSequenceMaker::getNumStates()
{
	return stepCounter;
}
