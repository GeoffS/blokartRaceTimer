const int RF_D0_PIN = 2;
const int RF_D1_PIN = 3;
const int RF_D2_PIN = 4;
const int RF_D3_PIN = 5;
const int FINISHED_LED_PIN = 6;
const int SPKR_PIN = 7;
const int PRE_COUNT_PIN = 8;
const int WARNING_PIN = 9;
const int DIAL_UP_PIN = 10;
const int RACING_PIN = 11;
const int POST_COUNT_PIN = 12;
const int SPKR_LED_PIN = 13;

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
int spkrStates[]      = {HIGH,  LOW, HIGH,  LOW, HIGH,  LOW, HIGH,  LOW, HIGH,  LOW, HIGH,  LOW, HIGH,  LOW, HIGH,  LOW, HIGH,  LOW, HIGH,  LOW, HIGH,  LOW, HIGH,  LOW, HIGH,  LOW,  LOW,  LOW};
int wpStates[]        = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW};
int duStates[]        = { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  LOW,  LOW,  LOW};
int rpStates[]        = { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH, HIGH,  LOW,  LOW};
int fpStates[]        = {HIGH, HIGH,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW, HIGH,  LOW};

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
  pinMode(RF_D0_PIN, INPUT);
  pinMode(RF_D1_PIN, INPUT);
  pinMode(RF_D2_PIN, INPUT);
  pinMode(RF_D3_PIN, INPUT);

  pinMode(PRE_COUNT_PIN, OUTPUT);
  pinMode(WARNING_PIN, OUTPUT);
  pinMode(DIAL_UP_PIN, OUTPUT);
  pinMode(RACING_PIN, OUTPUT);
  pinMode(POST_COUNT_PIN, OUTPUT);
  pinMode(FINISHED_LED_PIN, OUTPUT);
  pinMode(SPKR_LED_PIN, OUTPUT);
  pinMode(SPKR_PIN, OUTPUT);

  digitalWrite(PRE_COUNT_PIN, LOW);
  digitalWrite(WARNING_PIN, LOW);
  digitalWrite(DIAL_UP_PIN, LOW);
  digitalWrite(RACING_PIN, LOW);
  digitalWrite(POST_COUNT_PIN, LOW);
  digitalWrite(FINISHED_LED_PIN, LOW);
  digitalWrite(SPKR_LED_PIN, LOW);
  digitalWrite(SPKR_PIN, LOW);

  zeroTime_ms = millis();
}

bool stopped = true;

void loop()
{
  if (digitalRead(RF_D0_PIN) == HIGH) // Button "B" = Reset Sequence
  {
    stopped = true;
    digitalWrite(PRE_COUNT_PIN, LOW);
    digitalWrite(WARNING_PIN, LOW);
    digitalWrite(DIAL_UP_PIN, LOW);
    digitalWrite(RACING_PIN, LOW);
    digitalWrite(POST_COUNT_PIN, LOW);
    digitalWrite(FINISHED_LED_PIN, LOW);
    digitalWrite(SPKR_LED_PIN, LOW);
    digitalWrite(SPKR_PIN, LOW);
  }
  if (stopped)
  {
    if (digitalRead(RF_D2_PIN) == HIGH) // Button "A" = Start Sequence
    {
      currStateCounter = 0;
      zeroTime_ms = millis();
      digitalWrite(PRE_COUNT_PIN, HIGH);
      stopped = false;
    }
  }
  else // Not stopped = Runnning
  {
    if (currStateCounter >= numStates)
    {
      digitalWrite(POST_COUNT_PIN, HIGH);
    }
    else
    {
      ULONG currTime_ms = millis() - zeroTime_ms;
      if (currTime_ms >= (startTimes_ms[currStateCounter] + preDelay_ms))
      {
        digitalWrite(SPKR_LED_PIN, spkrStates[currStateCounter]);
        digitalWrite(SPKR_PIN, spkrStates[currStateCounter]);

        digitalWrite(PRE_COUNT_PIN, LOW);
        digitalWrite(WARNING_PIN, wpStates[currStateCounter]);
        digitalWrite(DIAL_UP_PIN, duStates[currStateCounter]);
        digitalWrite(RACING_PIN, rpStates[currStateCounter]);
        digitalWrite(FINISHED_LED_PIN, fpStates[currStateCounter]);
        currStateCounter++;
      }
    }
  }
}
