// We can use this to disable the siren for testing....
#define NO_12V false
//#define HARDWARE HWv1
#define HARDWARE HWv2

// Stringify macro expansion...
#define xstr(s) str(s)
#define str(s) #s

#define HARDWARE_INCLUDE xstr(HARDWARE.h)

#include <Button.h>
#include <Blinker.h>
#include HARDWARE_INCLUDE
#include "StartingSequenceMaker.h"

#define TMCD_VERSION "2.0.0"

#define BOOL2HIGHLOW ?HIGH:LOW

const byte zero = 0;
const byte allOnes = 255;

byte off[]    = {  0,   0,   0};
byte red[]    = {255,   0,   0};
byte green[]  = {  0, 255,   0};
byte blue[]   = {  0,   0, 255};
byte white[]  = {255, 255, 255};

byte voltageBarGraphRed[]    = {255,   0,   0};
byte voltageBarGraphGreen[]  = {  0, 190,   0};
byte voltageBarGraphYellow[] = {190, 100,   0};

byte * statusColor;
byte * soundColor;
byte * lightsColor;
byte * currCountDownProgramColor;
byte * battLowWarningColor = off;

byte * statusLEDcolors[numLEDs];

const ULONG raceTime_min = 1ul;
const ULONG preDelay_ms = 5000ul;

#define MAX_NUM_STEPS 100
ULONG startTimes_ms[MAX_NUM_STEPS];
bool spkrStates[MAX_NUM_STEPS];
bool fpStates[MAX_NUM_STEPS];
StartingSequenceMaker ssm = StartingSequenceMaker(startTimes_ms, spkrStates, fpStates, MAX_NUM_STEPS);

Blinker mediumBlink(750, 200);

int currCountDownProgramIndex = 0;
const int numCountDownPrograms = 6;

bool battTest = false;

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
    case 1:
      ssm.make_1minDU_XminRace(5);
      break;
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

#ifdef BATT_TEST
  analogReference(INTERNAL);
#endif

  digitalWrite(lightsPin, LOW);

  setSiren(false);
  playStartupLEDpattern();

  Serial.begin(9600);
  Serial.println("Software Version: " TMCD_VERSION);
  Serial.println("Hardware Version: " xstr(HARDWARE));
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
#ifdef BATT_TEST
  int battVoltage_counts = analogRead(battTestPin);
  if (battVoltage_counts <= battMin_counts) battLowWarningColor = mediumBlink.ledOn ? red : off;
  else                                      battLowWarningColor = off;
#endif
  // Battery Voltage Monitoring:
  //int counts = analogRead(battTestPin);
  //Serial.println(counts);

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

  bool longPressWhiteBtn = whiteBtn.isPressed() && whiteBtn.pressedTime_ms() > 1000;

  // Process the states:
  if (stopped)
  {
    statusColor = red;
    if (remoteB.wasClicked())
    {
      flashMainLEDs(); // For testing the remote range.
    }
#ifdef BATT_TEST
    if (battTest)
    {
      if (longPressWhiteBtn)
      {
        //set12Vpin(lightsPin, true);
        Serial.println(battVoltage_counts);
        loadVoltageBarGraphIntostatusLEDcolorsArray(battVoltage_counts);
        copyStatusLEDsArrayToAPA102();
      }
      else
      {
        //set12Vpin(lightsPin, false);
        battTest = false;
      }
      //whiteBtn.resetClicked();
      return;
    }
    else if (longPressWhiteBtn)
    {
      battTest = true;
      incrementCurrCountDownProgramIndex(-1);
    }
#endif
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
      incrementCurrCountDownProgramIndex(1);
    }
  }
  else // Not stopped = Runnning
  {
    statusColor = mediumBlink.ledOn ? green : off;
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

void incrementCurrCountDownProgramIndex(int increment)
{
  currCountDownProgramIndex = (currCountDownProgramIndex + increment) % numCountDownPrograms;
  if (currCountDownProgramIndex < 0) currCountDownProgramIndex = 0;
}

void loadVoltageBarGraphIntostatusLEDcolorsArray(int battVoltage_counts)
{
  int voltageBarGraphMaxIndex = round((float)(battVoltage_counts - battMin_counts) / ((float)(battMax_counts - battMin_counts)) * numLEDs);
  if (voltageBarGraphMaxIndex > numLEDs) voltageBarGraphMaxIndex = numLEDs;
  if (voltageBarGraphMaxIndex < 0      ) voltageBarGraphMaxIndex = 0;
  Serial.println(voltageBarGraphMaxIndex);
  for (int i = 0; i < numLEDs; i++) statusLEDcolors[i] = off;
  if (voltageBarGraphMaxIndex == 0)
  {
    statusLEDcolors[numLEDs - 1] = mediumBlink.ledOn ? red : off;
  }
  else
  {
    for (int i = 0; i < voltageBarGraphMaxIndex; i++)
    {
      int index = numLEDs - i - 1;
      if      (i < 3) statusLEDcolors[index] = voltageBarGraphRed;
      else if (i < 6) statusLEDcolors[index] = voltageBarGraphYellow;
      else            statusLEDcolors[index] = voltageBarGraphGreen;
    }
    if (battVoltage_counts > battMax_counts)
    {
      statusLEDcolors[0] = mediumBlink.ledOn ? green : off;
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

void setStoppedState()
{
  stopped = true;
  setLights(false);
  setSiren(false);
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

void set12Vpin(int pin, bool state)
{
  if (state)
  {
    if (!NO_12V) digitalWrite(pin, HIGH);
  }
  else
  {
    digitalWrite(pin, LOW); // Always set the pin LOW, "just in case"...
  }
}

void setSiren(bool state)
{
  set12Vpin(sirenPin, state);
  soundColor = state ? white : off;
}

void setLights(bool state)
{
  set12Vpin(lightsPin, state);
  lightsColor = state ? red : off;
}

void stepThroughAllAPA102LEDs(byte color[])
{
  for (int i = 0; i < numLEDs; i++)
  {
#ifdef STATUS_LEDS_REVERSED
    lightOneLED(numLEDs - i - 1, color);
#else
    lightOneLED(i, color);
#endif
    //lightOneLED(i, color);
    delay(50);
  }
}

void refreshLEDs()
{
  updateStatusLEDPattern();
  copyStatusLEDsArrayToAPA102();
}

void updateStatusLEDPattern()
{
  statusLEDcolors[0] = statusColor;
  statusLEDcolors[1] = soundColor;
  statusLEDcolors[2] = lightsColor;
  statusLEDcolors[numLEDs - 1] = battLowWarningColor;

  for (int i = 3; i < numLEDs - 1; i++)
  {
    if (i == (currCountDownProgramIndex + 3))
    {
      statusLEDcolors[i] = currCountDownProgramColor;
    }
    else
    {
      statusLEDcolors[i] = off;
    }
  }
}

void copyStatusLEDsArrayToAPA102()
{
  startFrame();
  for (int i = 0; i < numLEDs; i++)
  {
#ifdef STATUS_LEDS_REVERSED
    ledFrame(statusLEDcolors[numLEDs - i - 1]);
#else
    ledFrame(statusLEDcolors[i]);
#endif
  }
  endFrame();
}

void lightOneLED(int onLEDindex, byte color[])
{
  //Serial.print("onLEDindex = ");
  //Serial.println(onLEDindex);
  startFrame();
  for (int i = 0; i < numLEDs; i++)
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
  endFrame();
  //Serial.println("!");
}

void startFrame()
{
  shiftOut(dataPin, clkPin, MSBFIRST , zero);
  shiftOut(dataPin, clkPin, MSBFIRST , zero);
  shiftOut(dataPin, clkPin, MSBFIRST , zero);
  shiftOut(dataPin, clkPin, MSBFIRST , zero);
}

void endFrame()
{
  shiftOut(dataPin, clkPin, MSBFIRST , allOnes);
  shiftOut(dataPin, clkPin, MSBFIRST , zero);
  shiftOut(dataPin, clkPin, MSBFIRST , zero);
  shiftOut(dataPin, clkPin, MSBFIRST , zero);
}

void ledFrame(byte color[])
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
  endFrame();
}
