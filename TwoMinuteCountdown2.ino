// We can use this to disable the siren for testing....
#define QUIET false

#include <Button.h>
#include "StartingSequenceMaker.h"

#define TMCD_VERSION "0.2"

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

const ULONG raceTime_min = 1ul;
const ULONG preDelay_ms = 5000ul;

#define MAX_NUM_STEPS 100
ULONG startTimes_ms[MAX_NUM_STEPS];
bool spkrStates[MAX_NUM_STEPS];
bool fpStates[MAX_NUM_STEPS];
StartingSequenceMaker ssm = StartingSequenceMaker(startTimes_ms, spkrStates, fpStates, MAX_NUM_STEPS);

int currCountDownProgramIndex = 0;
const int numCountDownPrograms = 6;

bool undefinedProgram()
{
  playStartupLEDpattern();
  refreshLEDs(currCountDownProgramIndex + 3, blue);
  return false;
}

bool initStates()
{
  switch (currCountDownProgramIndex)
  {
    case 0:
      ssm.make_1minDU_NoRace();
      break;
    case 1: return undefinedProgram();
    case 2: return undefinedProgram();
    case 3:
      ssm.make_2minDU_5minRace();
      break;
    case 4: return undefinedProgram();
    case 5: return undefinedProgram();
    case 6: return undefinedProgram();
    default: return undefinedProgram();
  }
  return true;
}

void initStates_2minDU_4minRace()
{
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
  ssm.addLong(5 * ssm.SEC_PER_MIN);
  ssm.addRaceEnd(60);
}

Button greenBtn = Button(greenBtnPin);
Button whiteBtn = Button(whiteBtnPin);

Button remoteA = Button(remoteAPin, false);
Button remoteB = Button(remoteBPin, false);
Button remoteC = Button(remoteCPin, false);
Button remoteD = Button(remoteDPin, false);

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
  //initStates();
  refreshLEDs(currCountDownProgramIndex + 3, blue);

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
      if (!initStates()) return;
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
      refreshLEDs(currCountDownProgramIndex + 3, blue);
    }
  }
  else // Not stopped = Runnning
  {
    if (remoteB.wasClicked() || whiteBtn.wasClicked()) // Button "B" = Reset Sequence
    {
      stopped = true;
      digitalWrite(lightsPin, LOW);
      setSiren(false);
      refreshLEDs(currCountDownProgramIndex + 3, blue);

      // Flash the big LEDs to indicate reset:
      flashMainLEDs();
    }
    else
    {
      if (currStateCounter >= ssm.getNumStates())
      {
        //digitalWrite(POST_COUNT_PIN, HIGH);
      }
      else
      {
        ULONG currTime_ms = millis() - zeroTime_ms;
        if (currTime_ms >= (startTimes_ms[currStateCounter] + preDelay_ms))
        {
          setSiren(spkrStates[currStateCounter]);
          digitalWrite(lightsPin, fpStates[currStateCounter] ? HIGH : LOW);
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
