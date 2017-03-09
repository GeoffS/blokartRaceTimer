#ifndef MAKESTARTINGSEQUENCE220_H
#define MAKESTARTINGSEQUENCE220_H

#include "StartingSequenceMaker.h"

class StartingSequenceMaker220 : public StartingSequenceMaker
{
  public:
    StartingSequenceMaker220(ULONG startTimesArray[], bool spkrStatesArray[], bool fpStatesArray[], const int maxNumStates);
    ~StartingSequenceMaker220();

    void makeSequence1();
    void makeSequence2();
    void makeSequence3();
    void makeSequence4();
    void makeSequence5();
    void makeSequence6();

  protected:
    void make_2minDU_XminRace( int raceTime_min );
    void make_2minDU_NoRace();
    void make_1minDU_XminRace( int raceTime_min );
    void make_1minDU_NoRace();
};

#endif // MAKESTARTINGSEQUENCE220_H
