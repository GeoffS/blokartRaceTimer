#include "StartingSequenceMaker220.h"

StartingSequenceMaker220::StartingSequenceMaker220(
  ULONG startTimesArray[],
  bool spkrStatesArray[],
  bool fpStatesArray[],
  const int maxNumStates)
  : StartingSequenceMaker(
      startTimesArray,
      spkrStatesArray,
      fpStatesArray,
      maxNumStates)
{

}

StartingSequenceMaker220::~StartingSequenceMaker220()
{
}

void StartingSequenceMaker220::makeSequence1()
{
  make_1minDU_NoRace();
}

void StartingSequenceMaker220::makeSequence2()
{
  make_1minDU_XminRace(5);
}

void StartingSequenceMaker220::makeSequence3()
{
  make_2minDU_NoRace();
}

void StartingSequenceMaker220::makeSequence4()
{
  make_2minDU_XminRace(5);
}

void StartingSequenceMaker220::makeSequence5()
{
  make_2minDU_XminRace(10);
}

void StartingSequenceMaker220::makeSequence6()
{
	// Test Sequence:
  initShort(1);
  addRaceEnd(1);
}

void StartingSequenceMaker220::make_2minDU_XminRace( int raceTime_min )
{
  initShort(1, true, true);
  addShort(1, true, true);
  addShort(1, true, true);
  addShort(1, true, true);
  addLong(60, true, true);
  addMedium(30, true, true);
  addMedium(25, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addLong(raceTime_min * SEC_PER_MIN, true, true);
  addRaceEnd(1, true, true);
}

void StartingSequenceMaker220::make_2minDU_NoRace()
{
  initShort(1, true, true);
  addShort(1, true, true);
  addShort(1, true, true);
  addShort(1, true, true);
  addLong(60, true, true);
  addMedium(30, true, true);
  addMedium(25, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addLong(30, true, true);
}

void StartingSequenceMaker220::make_1minDU_NoRace()
{
  initShort(1, true, true);
  addShort(1, true, true);
  addShort(1, true, true);
  addShort(1, true, true);
  addLong(30, true, true);
  addMedium(25, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addLong(30, true, true);
}

void StartingSequenceMaker220::make_1minDU_XminRace( int raceTime_min )
{
  initShort(1, true, true);
  addShort(1, true, true);
  addShort(1, true, true);
  addShort(1, true, true);
  addLong(30, true, true);
  addMedium(25, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addPip(1, true, true);
  addLong(raceTime_min * SEC_PER_MIN, true, true);
  addRaceEnd(1, true, true);
}

