// We can use this to disable the siren for testing....
#define QUIET true

#include <Button.h>

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

const byte red[]   = {255,   0,   0};
const byte green[] = {  0, 255,   0};
const byte blue[]  = {  0,   0, 255};

#define ULONG unsigned long

const ULONG vs = 120ul; // ms
const ULONG s = 250ul; // ms
const ULONG m = 1000ul; // ms
const ULONG l = 2000ul; // ms

const ULONG pipPulse_ms = 120ul;
const ULONG shortPulse_ms = 250ul;
const ULONG mediumPulse_ms = 1000ul;
const ULONG longPulse_ms = 2000ul;

const ULONG raceTime_min = 5ul;
const ULONG preDelay_ms = 5000ul;
const ULONG SEC_PER_MIN = 60;
const ULONG MSEC_PER_SEC = 1000ul;

#define MAX_NUM_STEPS 30

const int numStatesOld = 28;
ULONG startTimesOld_ms[] = {   0ul,  0ul + s, 1000ul, 1000ul + s, 2000ul, 2000ul + s, 3000ul, 3000ul + s, 4000ul, 4000ul + l, 64000ul, 64000ul + m, 94000ul, 94000ul + m, 119000ul, 119000ul + vs, 120000ul, 120000ul + vs, 121000ul, 121000ul + vs, 122000ul, 122000ul + vs, 123000ul, 123000ul + vs, 124000ul, 124000ul + l, 124000ul + (raceTime_min * 60000ul), 124000ul + (raceTime_min * 60000ul) + 60000ul};
ULONG startTimes_ms[MAX_NUM_STEPS];

//                                                                        Dial-Up      1-Minute     30-Sec      5-Sec       4-Sec       3-Sec       2-Sec       1-Sec      Race         Race
//                          Warn 1      Warn 2      Warn 3      Warn 4     Start        Warning     Warning    Warning     Warning     Warning     Warning     Warning     Start        End
//                                  1s          1s          1s          1s         60s         30s         25s          1s          1s          1s          1s          1s        Race
//                            S           S           S           S          L            M           M           L           P           P           P           P           L
//                        ---------   ---------   ---------   ---------  ----------   ---------   ---------   ---------   ---------   ---------   ---------   ---------  ----------   ---------   ---------   ---------  ----------
//                          0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    25    26    27    28
//bool spkrStates[]   = {SHIH,  LOW, SHIH,  LOW, SHIH,  LOW, SHIH,  LOW, SHIH,  LOW, HIGH,  LOW, HIGH,  LOW, SHIH,  LOW, SHIH,  LOW, SHIH,  LOW, SHIH,  LOW, SHIH,  LOW, SHIH,  LOW,  LOW,  LOW};
bool spkrStates[]     = {true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, false, false};
int wpStates[]        = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW};
int duStates[]        = { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  LOW,  LOW,  LOW};
int rpStates[]        = { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH, HIGH,  LOW,  LOW};
int fpStates[]        = { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH,  LOW};

int numStates;
int stepCounter;
void initStartTimes()
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
  addRaceEnd(60);

  if (stepCounter > MAX_NUM_STEPS)
  {
    numStates = MAX_NUM_STEPS;
  }
  else
  {
    numStates = stepCounter;
  }
}

void initShort(int delayTime_s)
{
  //for(int i=0; i<numSteps; i++) startTimes_ms[i] = 0ul;

  startTimes_ms[0] = 0;
  startTimes_ms[1] = shortPulse_ms;
  startTimes_ms[2] = delayTime_s * MSEC_PER_SEC;
  stepCounter = 2;
}

void addPulse(ULONG pulseDuration_ms, ULONG delayTime_s)
{
  if (stepCounter >= MAX_NUM_STEPS) return;
  startTimes_ms[stepCounter + 1] = startTimes_ms[stepCounter] + pulseDuration_ms;
  startTimes_ms[stepCounter + 2] = startTimes_ms[stepCounter] + (delayTime_s * MSEC_PER_SEC);
  stepCounter += 2;
}

void addShort(int timeToNextPulse_s)
{
  addPulse(shortPulse_ms, timeToNextPulse_s);
}

void addMedium(int timeToNextPulse_s)
{
  addPulse(mediumPulse_ms, timeToNextPulse_s);
}

void addLong(int timeToNextPulse_s)
{
  addPulse(longPulse_ms, timeToNextPulse_s);
}

void addPip(int timeToNextPulse_s)
{
  addPulse(pipPulse_ms, timeToNextPulse_s);
}

void addRaceEnd(int stateDuration_s)
{
  if (stepCounter >= MAX_NUM_STEPS) return;
  startTimes_ms[stepCounter + 1] = startTimes_ms[stepCounter] + (stateDuration_s * MSEC_PER_SEC);
  stepCounter += 2;
}

Button greenBtn = Button(greenBtnPin);
Button whiteBtn = Button(whiteBtnPin);

int currCountDownProgramIndex = 0;
const int numCountDownPrograms = 10;

int currStateCounter = 0;
ULONG zeroTime_ms;

void setup()
{
  Serial.begin(9600);
  initStartTimes();
  Serial.print(numStatesOld);
  Serial.print(", ");
  Serial.println(numStates);
  for (int i = 0; i < numStates; i++)
  {
    Serial.print(startTimesOld_ms[i]);
    Serial.print(", ");
    Serial.print(startTimes_ms[i]);
    Serial.print(", ");
    Serial.println(startTimesOld_ms[i] - startTimes_ms[i]);
  }
  pinMode(remoteAPin, INPUT);
  pinMode(remoteBPin, INPUT);
  pinMode(remoteCPin, INPUT);
  pinMode(remoteDPin, INPUT);

  //pinMode(greenBtnPin, INPUT_PULLUP);
  //pinMode(whiteBtnPin, INPUT_PULLUP);

  pinMode(clkPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(lightsPin, OUTPUT);
  pinMode(sirenPin, OUTPUT);

  digitalWrite(lightsPin, LOW);

  setSiren(false);
  clearAll();
  refreshLEDs(currCountDownProgramIndex, blue);
  zeroTime_ms = millis();
}

bool stopped = true;

void loop()
{
  // Save some states we might be using more than once:
  bool remoteAPinState = digitalRead(remoteAPin) == HIGH;
  bool remoteBPinState = digitalRead(remoteBPin) == HIGH;

  // Check the buttons:
  greenBtn.checkButtonState();
  whiteBtn.checkButtonState();

  // Debug display:
  //remoteAPinState ? refreshLEDs(1) : clearAll();
  //remoteBPinState ? refreshLEDs(2) : clearAll();

  // Process the states:

  if (stopped)
  {
    if(remoteBPinState)
    {
      flashMainLEDs(); // For testing the remote range.
    }
    else if (remoteAPinState || greenBtn.wasClicked()) // Button "A" = Start Sequence
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
    if (remoteBPinState || whiteBtn.wasClicked()) // Button "B" = Reset Sequence
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
