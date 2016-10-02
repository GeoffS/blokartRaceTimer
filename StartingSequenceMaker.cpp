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

void StartingSequenceMaker::initShort(int delayTime_s)
{
  //for(int i=0; i<numSteps; i++) startTimes_ms[i] = 0ul;

  startTimes_ms[0] = 0;
  startTimes_ms[1] = shortPulse_ms;
  startTimes_ms[2] = delayTime_s * MSEC_PER_SEC;
  
  spkrStates[0]  = true;
  spkrStates[1]  = false;
  spkrStates[2]  = true;
  
  fpStates[0] = false;
  fpStates[1] = false;
  fpStates[2] = false;
  
  stepCounter = 2;
}

void StartingSequenceMaker::make_2minDU_5minRace()
{
	initShort(1);
	addShort(1);
	addShort(1);
	addShort(1);
	addLong(60);
	addMedium(30);
	addMedium(25);
	addPip(1);
	addPip(1);
	addPip(1);
	addPip(1);
	addPip(1);
	addLong(5 * SEC_PER_MIN);
	addRaceEnd(60);
}

void StartingSequenceMaker::make_1minDU_NoRace()
{
	initShort(1);
	addShort(1);
	addShort(1);
	addShort(1);
	addLong(30);
	addMedium(25);
	addPip(1);
	addPip(1);
	addPip(1);
	addPip(1);
	addPip(1);
	addLong(30);
}

void StartingSequenceMaker::addPulse(ULONG pulseDuration_ms, ULONG delayTime_s)
{
  if (stepCounter >= startTimesArraySize) return;
  
  startTimes_ms[stepCounter + 1] = startTimes_ms[stepCounter] + pulseDuration_ms;
  startTimes_ms[stepCounter + 2] = startTimes_ms[stepCounter] + (delayTime_s * MSEC_PER_SEC);
  
  spkrStates[stepCounter + 1] = false;
  spkrStates[stepCounter + 2] = true;
  
  fpStates[stepCounter + 1] = false;
  fpStates[stepCounter + 2] = false;
  
  stepCounter += 2;
}

void StartingSequenceMaker::addShort(int timeToNextPulse_s)
{
  addPulse(shortPulse_ms, timeToNextPulse_s);
}

void StartingSequenceMaker::StartingSequenceMaker::addMedium(int timeToNextPulse_s)
{
  addPulse(mediumPulse_ms, timeToNextPulse_s);
}

void StartingSequenceMaker::addLong(int timeToNextPulse_s)
{
  addPulse(longPulse_ms, timeToNextPulse_s);
}

void StartingSequenceMaker::addPip(int timeToNextPulse_s)
{
  addPulse(pipPulse_ms, timeToNextPulse_s);
}

void StartingSequenceMaker::addRaceEnd(int stateDuration_s)
{
  if (stepCounter >= startTimesArraySize) return;
  
  startTimes_ms[stepCounter + 1] = startTimes_ms[stepCounter] + (stateDuration_s * MSEC_PER_SEC);
  
  spkrStates[stepCounter] = false;
  spkrStates[stepCounter + 1] = false;
  
  fpStates[stepCounter] = true;
  fpStates[stepCounter + 1] = false;
  
  stepCounter += 2;
}

int StartingSequenceMaker::getNumStates()
{
	return stepCounter;
}
