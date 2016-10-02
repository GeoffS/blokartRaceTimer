#include <stdio.h>
#include "../../StartingSequenceMaker.h"

#define MAX_NUM_STEPS 100

int main(int argc, char **argv)
{
	const ULONG vs = 120ul; // ms
	const ULONG s = 250ul; // ms
	const ULONG m = 1000ul; // ms
	const ULONG l = 2000ul; // ms
	ULONG raceTime_min = 5ul;
	const int numStatesOld = 28;
	ULONG startTimesOld_ms[] = {   0ul,  0ul + s, 1000ul, 1000ul + s, 2000ul, 2000ul + s, 3000ul, 3000ul + s, 4000ul, 4000ul + l, 64000ul, 64000ul + m, 94000ul, 94000ul + m, 119000ul, 119000ul + vs, 120000ul, 120000ul + vs, 121000ul, 121000ul + vs, 122000ul, 122000ul + vs, 123000ul, 123000ul + vs, 124000ul, 124000ul + l, 124000ul + (raceTime_min * 60000ul), 124000ul + (raceTime_min * 60000ul) + 60000ul};
	bool fpStatesOld[]       = { false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false,  false, true,  false};

	ULONG startTimes_ms[MAX_NUM_STEPS];
	bool fpStates[MAX_NUM_STEPS];
	printf("Hello StartingSequenceMaker\n");
	StartingSequenceMaker ssm(startTimes_ms, fpStates, MAX_NUM_STEPS);

	ssm.initShort(1);
	ssm.addShort(1);
	ssm.addShort(1);
	ssm.addShort(1);
	ssm.addLong(60);
	ssm.addMedium(30);
	ssm.addMedium(25);
	ssm.addPip(1);
	ssm.addPip(1);
	ssm.addPip(1);
	ssm.addPip(1);
	ssm.addPip(1);
	ssm.addLong(raceTime_min * ssm.SEC_PER_MIN);
	ssm.addRaceEnd(60);

	bool failure = false;
	printf("numStatesOld = %i\n", numStatesOld);
	printf("ssm.getNumStates() = %i\n", ssm.getNumStates());
	if(numStatesOld != ssm.getNumStates())
	{
		printf("*************** Incorrect numStates!\n");
		failure = true;
	}
	for (int i = 0; i < ssm.getNumStates(); i++)
	{
		printf("%i, ", startTimesOld_ms[i]);
		printf("%i, ", startTimes_ms[i]);
		int delta_ms = startTimesOld_ms[i] - startTimes_ms[i];
		printf("%i\n", delta_ms);
		if(delta_ms != 0)
		{
			printf("*************** Incorrect time!\n");
			failure = true;
		}
	}
	
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

	return 0;
}
