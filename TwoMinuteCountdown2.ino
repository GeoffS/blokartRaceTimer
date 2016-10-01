// We can use this to disable the siren for testing....
#define QUIET true

#include <Button.h>
#include "StartingSequenceMaker.h"

#define TMCD_VERSION "0.1"

/// Remote:
const int remoteAPin = 4;
const int remoteBPin = 2;
const int remoteCPin = 5;
const int remoteDPin = 3;

// 12V Outputs:
const int lightsPin = 6;
const int sirenPin = 7;

// Buttons:
const int greenBtnPin = 8;
const int whiteBtnPin = 9;

//APA102C String:
const int clkPin = 10;
const int dataPin = 11;
const int numLEDs = 10;

const byte zero = 0;
const byte allOnes = 255;

const byte red[]    = {255,   0,   0};
const byte green[]  = {  0, 255,   0};
const byte blue[]   = {  0,   0, 255};
const byte white[]  = {255, 255, 255};

const ULONG raceTime_min = 5ul;
const ULONG preDelay_ms = 5000ul;

#define MAX_NUM_STEPS 200
ULONG startTimes_ms[MAX_NUM_STEPS];

//                                                                        Dial-Up      1-Minute     30-Sec      5-Sec       4-Sec       3-Sec       2-Sec       1-Sec      Race         Race
//                          Warn 1      Warn 2      Warn 3      Warn 4     Start        Warning     Warning    Warning     Warning     Warning     Warning     Warning     Start        End
//                                  1s          1s          1s          1s         60s         30s         25s          1s          1s          1s          1s          1s        Race
//                            S           S           S           S          L            M           M           L           P           P           P           P           L
//                        ---------   ---------   ---------   ---------  ----------   ---------   ---------   ---------   ---------   ---------   ---------   ---------  ----------   ---------   ---------   ---------  ----------
//                          0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    25    26    27    28
bool spkrStates[]     = {true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, false, false};
int wpStates[]        = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW};
int duStates[]        = { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  LOW,  LOW,  LOW};
int rpStates[]        = { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH, HIGH,  LOW,  LOW};
int fpStates[]        = { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH,  LOW};

int numStates;
void initStartTimes()
{
  StartingSequenceMaker ssm = StartingSequenceMaker(startTimes_ms, MAX_NUM_STEPS);

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

  numStates = ssm.getNumStates();
}

Button greenBtn = Button(greenBtnPin);
Button whiteBtn = Button(whiteBtnPin);

Button remoteA = Button(remoteAPin, false);
Button remoteB = Button(remoteBPin, false);
Button remoteC = Button(remoteCPin, false);
Button remoteD = Button(remoteDPin, false);

int currCountDownProgramIndex = 0;
const int numCountDownPrograms = 10;

int currStateCounter = 0;
ULONG zeroTime_ms;

void setup()
{
  pinMode(clkPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(lightsPin, OUTPUT);
  pinMode(sirenPin, OUTPUT);

  digitalWrite(lightsPin, LOW);
  
  setSiren(false);
  playStartupLEDpattern();

  Serial.begin(9600);
  Serial.println("Version: " TMCD_VERSION);
  initStartTimes();
  refreshLEDs(currCountDownProgramIndex, blue);

  zeroTime_ms = millis();
}

bool stopped = true;

void loop()
{
  // Check the remote:
  remoteA.checkButtonState();
  remoteB.checkButtonState();
  remoteC.checkButtonState();
  remoteD.checkButtonState();

  // Check the buttons:
  greenBtn.checkButtonState();
  whiteBtn.checkButtonState();

  // Process the states:
  if (stopped)
  {
    if (remoteB.wasClicked())
    {
      flashMainLEDs(); // For testing the remote range.
    }
    else if (remoteA.wasClicked() || greenBtn.wasClicked()) // Button "A" = Start Sequence
    {
      currStateCounter = 0;
      zeroTime_ms = millis();
      stopped = false;
      flashMainLEDs();
    }
    else if (whiteBtn.wasClicked())
    {
      currCountDownProgramIndex = (currCountDownProgramIndex + 1) % numCountDownPrograms;
      //Serial.print("currCountDownProgramIndex = ");
      //Serial.println(currCountDownProgramIndex);
      refreshLEDs(currCountDownProgramIndex, blue);
    }
  }
  else // Not stopped = Runnning
  {
    if (remoteB.wasClicked() || whiteBtn.wasClicked()) // Button "B" = Reset Sequence
    {
      stopped = true;
      digitalWrite(lightsPin, LOW);
      setSiren(false);
      refreshLEDs(currCountDownProgramIndex, blue);

      // Flash the big LEDs to indicate reset:
      flashMainLEDs();
    }
    else
    {
      if (currStateCounter >= numStates)
      {
        //digitalWrite(POST_COUNT_PIN, HIGH);
      }
      else
      {
        ULONG currTime_ms = millis() - zeroTime_ms;
        if (currTime_ms >= (startTimes_ms[currStateCounter] + preDelay_ms))
        {
          setSiren(spkrStates[currStateCounter]);
          digitalWrite(lightsPin, fpStates[currStateCounter]);
          currStateCounter++;
        }
      }
    }
  }
}

void playStartupLEDpattern()
{
  flashMainLEDs();
  stepThroughAllAPA102LEDs(white);
  stepThroughAllAPA102LEDs(red);
  stepThroughAllAPA102LEDs(green);
  stepThroughAllAPA102LEDs(blue);
  clearAll();
}

void flashMainLEDs()
{
  // Flash the big LEDs to indicate reset:
  digitalWrite(lightsPin, HIGH);
  delay(200);
  digitalWrite(lightsPin, LOW);
}

void setSiren(bool state)
{
  if (!QUIET) digitalWrite(sirenPin, state ? HIGH : LOW);
  setLED0(state);
}

void setLED0(bool state)
{
  if (state)
  {
    refreshLEDs(0, red);
  }
  else
  {
    clearAll();
  }
}

void stepThroughAllAPA102LEDs(const byte color[])
{
  for (int i = 0; i < numLEDs; i++)
  {
    refreshLEDs(i, color);
    delay(50);
  }
}

void refreshLEDs(int onLEDindex, const byte color[])
{
  //Serial.print("onLEDindex = ");
  //Serial.println(onLEDindex);
  startFrame();
  for (int i = 0; i < numLEDs + 1; i++)
  {
    //Serial.print(" ");
    //Serial.print(i);
    if (i == onLEDindex)
    {
      //Serial.print("=onLEDindex");
      ledFrame(color[0], color[1], color[2]);
    }
    else
    {
      ledFrame(zero, zero, zero);
    }
  }
  //Serial.println("!");
}

void startFrame()
{
  shiftOut(dataPin, clkPin, MSBFIRST , zero);
  shiftOut(dataPin, clkPin, MSBFIRST , zero);
  shiftOut(dataPin, clkPin, MSBFIRST , zero);
  shiftOut(dataPin, clkPin, MSBFIRST , zero);
}

void ledFrame(byte red, byte green, byte blue)
{
  shiftOut(dataPin, clkPin, MSBFIRST , allOnes);
  shiftOut(dataPin, clkPin, MSBFIRST , blue);
  shiftOut(dataPin, clkPin, MSBFIRST , green);
  shiftOut(dataPin, clkPin, MSBFIRST , red);
}

void clearAll()
{
  startFrame();
  for (int i = 0; i < numLEDs; i++)
  {
    ledFrame(zero, zero, zero);
  }
}
