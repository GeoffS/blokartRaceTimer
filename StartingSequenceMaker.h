#ifndef MAKESTARTINGSEQUENCE_H
#define MAKESTARTINGSEQUENCE_H

#define ULONG unsigned long

class StartingSequenceMaker
{
  public:
    StartingSequenceMaker(ULONG startTimesArray[], bool spkrStatesArray[], bool fpStatesArray[], const int maxNumStates);
    ~StartingSequenceMaker();

    virtual void makeSequence1()=0;
    virtual void makeSequence2()=0;
    virtual void makeSequence3()=0;
    virtual void makeSequence4()=0;
    virtual void makeSequence5()=0;
    virtual void makeSequence6()=0;

    int getNumStates();

    const ULONG preDelay_ms = 5000ul;
    const ULONG SEC_PER_MIN = 60;
    const ULONG MSEC_PER_SEC = 1000ul;

  protected:
    void initShort(int delayTime_s, bool spkr=true, bool light=false);
    void addPulse(ULONG pulseDuration_ms, ULONG delayTime_s, bool spkr=true, bool light=false);
    void addShort(int timeToNextPulse_s, bool spkr=true, bool light=false);
    void addMedium(int timeToNextPulse_s, bool spkr=true, bool light=false);
    void addLong(int timeToNextPulse_s, bool spkr=true, bool light=false);
    void addPip(int timeToNextPulse_s, bool spkr=true, bool light=false);
    void addRaceEnd(int stateDuration_s, bool spkr=false, bool light=true);

  private:
    int stepCounter;
    ULONG * startTimes_ms;
    bool * spkrStates;
    bool * fpStates;
    const int startTimesArraySize;
};

#endif // MAKESTARTINGSEQUENCE_H
