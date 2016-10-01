#include <stdio.h>
#include "../../StartingSequenceMaker.h"

#define MAX_NUM_STEPS 30

int main(int argc, char **argv)
{
	const ULONG vs = 120ul; // ms
	const ULONG s = 250ul; // ms
	const ULONG m = 1000ul; // ms
	const ULONG l = 2000ul; // ms
	ULONG raceTime_min = 5ul;
	const int numStatesOld = 28;
	ULONG startTimesOld_ms[] = {   0ul,  0ul + s, 1000ul, 1000ul + s, 2000ul, 2000ul + s, 3000ul, 3000ul + s, 4000ul, 4000ul + l, 64000ul, 64000ul + m, 94000ul, 94000ul + m, 119000ul, 119000ul + vs, 120000ul, 120000ul + vs, 121000ul, 121000ul + vs, 122000ul, 122000ul + vs, 123000ul, 123000ul + vs, 124000ul, 124000ul + l, 124000ul + (raceTime_min * 60000ul), 124000ul + (raceTime_min * 60000ul) + 60000ul};

	ULONG startTimes_ms[MAX_NUM_STEPS];
	printf("Hello StartingSequenceMaker\n");
	StartingSequenceMaker ssm(startTimes_ms);

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

	printf("numStatesOld = %i\n", numStatesOld);
	printf("ssm.getNumStates() = %i\n", ssm.getNumStates());
	for (int i = 0; i < ssm.getNumStates(); i++)
	{
		printf("%i, ", startTimesOld_ms[i]);
		printf("%i, ", startTimes_ms[i]);
		printf("%i\n", startTimesOld_ms[i] - startTimes_ms[i]);
	}

	return 0;
}
