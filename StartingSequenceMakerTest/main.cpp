#include <stdio.h>
#include "../../StartingSequenceMaker.h"

#define BOOL2STR ?"True":"False"

#define MAX_NUM_STEPS 100

bool checkStates(int expectedNumStates, int numStates,
					ULONG expectedStartTimes_ms[], ULONG startTimes_ms[],
					bool expectedSpkrStates[], bool spkrStates[],
					bool expectedFpStates[], bool fpStates[])
{
	bool failure = false;
	
	printf("====================\nCheck the number of states:\n-----------\n");
	printf("expectedNumStates = %i\n", expectedNumStates);
	printf("ssm.getNumStates() = %i\n", numStates);
	if(expectedNumStates != numStates)
	{
		printf("*************** Incorrect numStates!\n");
		failure = true;
	}
	
	printf("\n====================\nCheck the times:\n-----------\n");
	for (int i = 0; i < numStates; i++)
	{
		ULONG delta_ms = expectedStartTimes_ms[i] - startTimes_ms[i];
		printf("%lu, %lu %lu\n", expectedStartTimes_ms[i], startTimes_ms[i], delta_ms);
		if(delta_ms != 0)
		{
			printf("*************** Incorrect time!\n");
			failure = true;
		}
	}
	
	printf("\n====================\nCheck the siren states:\n-----------\n");
	for (int i = 0; i < numStates; i++)
	{
		printf("%s, %s\n", expectedSpkrStates[i]BOOL2STR, spkrStates[i]BOOL2STR);
		if(expectedSpkrStates[i] != spkrStates[i])
		{
			printf("*************** Incorrect speaker state!\n");
			failure = true;
		}
	}
	
	printf("\n====================\nCheck the main-LEDs states:\n-----------\n");
	for (int i = 0; i < numStates; i++)
	{
		printf("%s, %s\n", expectedFpStates[i]BOOL2STR, fpStates[i]BOOL2STR);
		if(expectedFpStates[i] != fpStates[i])
		{
			printf("*************** Incorrect main LEDs state!\n");
			failure = true;
		}
	}
	
	if(failure)
	{
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("*****  TEST FAILED  *****\n");
		printf("--------------------------------------------------------\n");
	}
	printf("\n\n");
	
	return failure;
}

void printPassFail(bool failure)
{
	printf("\n\n\n");
	if(failure)
	{
		printf("   FFFFF      A        III   L\n");
		printf("   F        A   A       I    L\n");
		printf("   F       A     A      I    L\n");
		printf("   FFFF    AAAAAAA      I    L\n");
		printf("   F      A       A     I    L\n");
		printf("   F      A       A    III   LLLLL\n");
	}
	else
	{
		printf("   PPPPP       A        SSSSSS    SSSSSS  \n");
		printf("   P    P    A   A     S         S\n");
		printf("   P    P   A     A     SSSSS     SSSSS\n");
		printf("   PPPPP    AAAAAAA          S          S\n");
		printf("   P       A       A         S          S\n");
		printf("   P       A       A   SSSSSS     SSSSSS\n");
	}
}

const ULONG vs = 120ul; // ms
const ULONG s = 250ul; // ms
const ULONG m = 1000ul; // ms
const ULONG l = 2000ul; // ms

bool check_2minDU_XminRace( int raceTime_min)
{
	const int numStatesOld = 28;
	ULONG startTimesOld_ms[] = {   0ul,  0ul + s, 1000ul, 1000ul + s, 2000ul, 2000ul + s, 3000ul, 3000ul + s, 4000ul, 4000ul + l, 64000ul, 64000ul + m, 94000ul, 94000ul + m, 119000ul, 119000ul + vs, 120000ul, 120000ul + vs, 121000ul, 121000ul + vs, 122000ul, 122000ul + vs, 123000ul, 123000ul + vs, 124000ul, 124000ul + l, 124000ul + (raceTime_min * 60000ul), 124000ul + (raceTime_min * 60000ul) + 60000ul};
	bool spkrStatesOld[]     = {true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, false, false};
	bool fpStatesOld[]       = { false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false, true,  false};

	ULONG startTimes_ms[MAX_NUM_STEPS];
	bool spkrStates[MAX_NUM_STEPS];
	bool fpStates[MAX_NUM_STEPS];
	StartingSequenceMaker ssm(startTimes_ms, spkrStates, fpStates, MAX_NUM_STEPS);

	ssm.make_2minDU_XminRace( raceTime_min );

	return checkStates(numStatesOld, ssm.getNumStates(), 
	                   startTimesOld_ms, startTimes_ms,
					   spkrStatesOld, spkrStates,
					   fpStatesOld, fpStates);
}


bool test_2minDU_5minRaceOri()
{
	printf("test_2minDU_5minRaceOri\n");
	ULONG raceTime_min = 5ul;
	const int numStatesOld = 28;
	ULONG startTimesOld_ms[] = {   0ul,  0ul + s, 1000ul, 1000ul + s, 2000ul, 2000ul + s, 3000ul, 3000ul + s, 4000ul, 4000ul + l, 64000ul, 64000ul + m, 94000ul, 94000ul + m, 119000ul, 119000ul + vs, 120000ul, 120000ul + vs, 121000ul, 121000ul + vs, 122000ul, 122000ul + vs, 123000ul, 123000ul + vs, 124000ul, 124000ul + l, 124000ul + (raceTime_min * 60000ul), 124000ul + (raceTime_min * 60000ul) + 60000ul};
	bool spkrStatesOld[]     = {true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, false, false};
	bool fpStatesOld[]       = { false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false, true,  false};

	ULONG startTimes_ms[MAX_NUM_STEPS];
	bool spkrStates[MAX_NUM_STEPS];
	bool fpStates[MAX_NUM_STEPS];
	StartingSequenceMaker ssm(startTimes_ms, spkrStates, fpStates, MAX_NUM_STEPS);

	ssm.make_2minDU_XminRace( 5 );

	return checkStates(numStatesOld, ssm.getNumStates(), 
	                   startTimesOld_ms, startTimes_ms,
					   spkrStatesOld, spkrStates,
					   fpStatesOld, fpStates);
}

bool test_2minDU_5minRace()
{
	printf("test_2minDU_5minRace\n");
	return check_2minDU_XminRace(5);
}

bool test_2minDU_10minRace()
{
	printf("test_2minDU_10minRace\n");
	return check_2minDU_XminRace(10);
}

bool test_2minDU_15minRace()
{
	printf("test_2minDU_10minRace\n");
	return check_2minDU_XminRace(15);
}

bool test_2minDU_NoRace()
{
	printf("test_1minDU_NoRace\n");
	const int numStatesOld = 26;
	ULONG startTimesOld_ms[] = {   0ul,  0ul + s, 1000ul, 1000ul + s, 2000ul, 2000ul + s, 3000ul, 3000ul + s, 4000ul, 4000ul + l, 64000ul, 64000ul + m, 94000ul, 94000ul + m, 119000ul, 119000ul + vs, 120000ul, 120000ul + vs, 121000ul, 121000ul + vs, 122000ul, 122000ul + vs, 123000ul, 123000ul + vs, 124000ul, 124000ul + l};
	bool spkrStatesOld[]     = {true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false};
	bool fpStatesOld[]       = { false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false};

	ULONG startTimes_ms[MAX_NUM_STEPS];
	bool spkrStates[MAX_NUM_STEPS];
	bool fpStates[MAX_NUM_STEPS];
	StartingSequenceMaker ssm(startTimes_ms, spkrStates, fpStates, MAX_NUM_STEPS);

	ssm.make_2minDU_NoRace();

	return checkStates(numStatesOld, ssm.getNumStates(), 
	                   startTimesOld_ms, startTimes_ms,
					   spkrStatesOld, spkrStates,
					   fpStatesOld, fpStates);
}

bool test_1minDU_NoRace()
{
	printf("test_1minDU_NoRace\n");
	const int numStatesOld = 24;
	ULONG startTimesOld_ms[] = {   0ul,  0ul + s, 1000ul, 1000ul + s, 2000ul, 2000ul + s, 3000ul, 3000ul + s, 4000ul, 4000ul + l, 34000ul, 34000ul + m, 59000ul, 59000ul + vs, 60000ul, 60000ul + vs, 61000ul, 61000ul + vs, 62000ul, 62000ul + vs, 63000ul, 63000ul + vs, 64000ul, 64000ul + l};
	bool spkrStatesOld[]     = {true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false};
	bool fpStatesOld[]       = {false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false};

	ULONG startTimes_ms[MAX_NUM_STEPS];
	bool spkrStates[MAX_NUM_STEPS];
	bool fpStates[MAX_NUM_STEPS];
	StartingSequenceMaker ssm(startTimes_ms, spkrStates, fpStates, MAX_NUM_STEPS);

	ssm.make_1minDU_NoRace();

	return checkStates(numStatesOld, ssm.getNumStates(), 
	                   startTimesOld_ms, startTimes_ms,
					   spkrStatesOld, spkrStates,
					   fpStatesOld, fpStates);
}

int main(int argc, char **argv)
{
	bool failure = false;
	
	failure |= test_2minDU_5minRaceOri();
	failure |= test_2minDU_5minRace();
	failure |= test_2minDU_10minRace();
	failure |= test_2minDU_15minRace();
	failure |= test_1minDU_NoRace();
	
	printPassFail(failure);

	return 0;
}

