#ifndef MAKESTARTINGSEQUENCE211_H
#define MAKESTARTINGSEQUENCE211_H

#include "StartingSequenceMaker.h"

class StartingSequenceMaker211 : public StartingSequenceMaker
{
  public:
    StartingSequenceMaker211(ULONG startTimesArray[], bool spkrStatesArray[], bool fpStatesArray[], const int maxNumStates);
    ~StartingSequenceMaker211();

    void makeSequence1();
    void makeSequence2();
    void makeSequence3();
    void makeSequence4();
    void makeSequence5();
    void makeSequence6();

  //protected:
  // Public for test...
    void make_2minDU_XminRace( int raceTime_min );
    void make_2minDU_NoRace();
    void make_1minDU_XminRace( int raceTime_min );
    void make_1minDU_NoRace();
    void makeTestRace();
};

#endif // MAKESTARTINGSEQUENCE211_H
