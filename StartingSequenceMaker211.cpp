#include "StartingSequenceMaker211.h"

StartingSequenceMaker211::StartingSequenceMaker211(
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

StartingSequenceMaker211::~StartingSequenceMaker211()
{
}

void StartingSequenceMaker211::makeSequence1()
{
  make_1minDU_NoRace();
}

void StartingSequenceMaker211::makeSequence2()
{
  make_1minDU_XminRace(5);
}

void StartingSequenceMaker211::makeSequence3()
{
  make_2minDU_NoRace();
}

void StartingSequenceMaker211::makeSequence4()
{
  make_2minDU_XminRace(5);
}

void StartingSequenceMaker211::makeSequence5()
{
  make_2minDU_XminRace(10);
}

void StartingSequenceMaker211::makeSequence6()
{
  makeTestRace();
}

void StartingSequenceMaker211::make_2minDU_XminRace( int raceTime_min )
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
  addLong(raceTime_min * SEC_PER_MIN);
  addRaceEnd(1);
}

void StartingSequenceMaker211::make_2minDU_NoRace()
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
  addLong(30);
}

void StartingSequenceMaker211::make_1minDU_NoRace()
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

void StartingSequenceMaker211::make_1minDU_XminRace( int raceTime_min )
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
  addLong(raceTime_min * SEC_PER_MIN);
  addRaceEnd(1);
}

void StartingSequenceMaker211::makeTestRace()
{
  initShort(1);
  addRaceEnd(1);
}

