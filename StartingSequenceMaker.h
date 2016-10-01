#ifndef MAKESTARTINGSEQUENCE_H
#define MAKESTARTINGSEQUENCE_H

#define ULONG unsigned long

class StartingSequenceMaker
{
public:
	StartingSequenceMaker(ULONG startTimesArray[], const int maxNumStates);
	~StartingSequenceMaker();
	void initShort(int delayTime_s);
	void addPulse(ULONG pulseDuration_ms, ULONG delayTime_s);
	void addShort(int timeToNextPulse_s);
	void addMedium(int timeToNextPulse_s);
	void addLong(int timeToNextPulse_s);
	void addPip(int timeToNextPulse_s);
	void addRaceEnd(int stateDuration_s);
	
	int getNumStates();
	
	const ULONG preDelay_ms = 5000ul;
	const ULONG SEC_PER_MIN = 60;
	const ULONG MSEC_PER_SEC = 1000ul;
	
private:
	int stepCounter;
	ULONG * startTimes_ms;
  const int startTimesArraySize;
};

#endif // MAKESTARTINGSEQUENCE_H
