// We can use this to disable the siren for testing....
#define NO_12V true

#include <Button.h>
#include <Blinker.h>
#include "StartingSequenceMaker.h"

#define TMCD_VERSION "0.2"

#define BOOL2HIGHLOW ?HIGH:LOW

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

byte off[]    = {  0,   0,   0};
byte red[]    = {255,   0,   0};
byte green[]  = {  0, 255,   0};
byte blue[]   = {  0,   0, 255};
byte white[]  = {255, 255, 255};

byte * statusColor;
byte * soundColor;
byte * lightsColor;
byte * currCountDownProgramColor;

const ULONG raceTime_min = 1ul;
const ULONG preDelay_ms = 5000ul;

#define MAX_NUM_STEPS 100
ULONG startTimes_ms[MAX_NUM_STEPS];
bool spkrStates[MAX_NUM_STEPS];
bool fpStates[MAX_NUM_STEPS];
StartingSequenceMaker ssm = StartingSequenceMaker(startTimes_ms, spkrStates, fpStates, MAX_NUM_STEPS);

/*const*/ Blinker mediumBlink(750, 200);
//const Blinker slow(4000, 2000);

int currCountDownProgramIndex = 0;
const int numCountDownPrograms = 6;

bool undefinedProgram()
{
  playStartupLEDpattern();
  refreshLEDs();
  return false;
}

bool initStates()
{
  switch (currCountDownProgramIndex)
  {
    case 0:
      ssm.make_1minDU_NoRace();
      break;
    case 1: return undefinedProgram(); // 1min DU, 5min race
    case 2:
      ssm.make_2minDU_NoRace();
      break;
    case 3:
      ssm.make_2minDU_XminRace(5);
      break;
    case 4:
      ssm.make_2minDU_XminRace(10);
      break;
    case 5:
      ssm.make_2minDU_XminRace(15);
      break;
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
  //refreshLEDs(currCountDownProgramIndex + 3, blue);

  statusColor = red;
  soundColor = off;
  lightsColor = off;
  currCountDownProgramColor = blue;
  refreshLEDs();

  zeroTime_ms = millis();
}

bool stopped = true;

void loop()
{
  // Update the blinker:
  unsigned long now = millis();
  mediumBlink.updateLedOnFlag(&now);

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
    statusColor = red;
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
      //refreshLEDs(currCountDownProgramIndex + 3, blue);
    }
  }
  else // Not stopped = Runnning
  {
    statusColor = mediumBlink.ledOn?green:off;
    if (remoteB.wasClicked() || whiteBtn.wasClicked()) // Button "B" = Reset Sequence
    {
      stopped = true;
      digitalWrite(lightsPin, LOW);
      setSiren(false);

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
          setLights(fpStates[currStateCounter]);
          //digitalWrite(lightsPin, fpStates[currStateCounter] ? HIGH : LOW);
          currStateCounter++;
        }
      }
    }
  }
  refreshLEDs();
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
  setLights(true);
  refreshLEDs();
  delay(200);
  setLights(false);
  refreshLEDs();
}

void setSiren(bool state)
{
  if (!NO_12V) digitalWrite(sirenPin, state ? HIGH : LOW);
  soundColor = state ? white : off;
}

void setLights(bool state)
{
  if (!NO_12V) digitalWrite(lightsPin, state ? HIGH : LOW);
  lightsColor = state ? red : off;
}

void stepThroughAllAPA102LEDs(const byte color[])
{
  for (int i = 0; i < numLEDs; i++)
  {
    lightOneLED(i, color);
    delay(50);
  }
}

void refreshLEDs()
{
  unsigned long start = millis();
  startFrame();
  ledFrame(statusColor);
  ledFrame(soundColor);
  ledFrame(lightsColor);
  for (int i = 3; i < numLEDs + 1; i++)
  {
    if (i == (currCountDownProgramIndex + 3))
    {
      //Serial.print("=onLEDindex");
      ledFrame(currCountDownProgramColor);
    }
    else
    {
      ledFrame(off);
    }
  }
  unsigned long delta_ms = millis() - start;
  Serial.print("refreshLEDs time = ");
  Serial.print(delta_ms);
  Serial.println(" ms");
}

/*
  void refreshLEDs()
  {
  //Serial.print("onLEDindexunsigned long start = ");
  //Serial.println(onLEDindex);millis();
  startFrame();
  ledFrame(statusColor);
  ledFrame(soundColor);
  ledFrame(lightsColor);
  for (int i = 0; i < numLEDs + 1; i++)
  {
    //Serial.print(" ");
    //Serial.print(i);
    if (i == (currCountDownProgramIndex + 3))
    {
      //Serial.print("=onLEDindex");
      ledFrame(color[0], color[1], color[2]); ledFrame(currCountDownProgramColor);
    }
    else
    {
      ledFrame(off);
    }
  }
  //Serial.println("!");unsigned long delta_ms = millis() - start;
  Serial.print("refreshLEDs time = ");
  Serial.print(delta_ms);
  Serial.println(" ms");
  }
*/

void lightOneLED(int onLEDindex, const byte color[])
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
      ledFrame(color);
    }
    else
    {
      ledFrame(off);
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

void ledFrame(const byte color[])
{
  shiftOut(dataPin, clkPin, MSBFIRST , allOnes);
  shiftOut(dataPin, clkPin, MSBFIRST , color[2]);
  shiftOut(dataPin, clkPin, MSBFIRST , color[1]);
  shiftOut(dataPin, clkPin, MSBFIRST , color[0]);
}

void clearAll()
{
  startFrame();
  for (int i = 0; i < numLEDs; i++)
  {
    ledFrame(off);
  }
}
