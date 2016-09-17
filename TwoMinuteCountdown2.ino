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

const ULONG raceTime_min = 5ul;
const ULONG preDelay_ms = 5000ul;

const int numStates = 28;
ULONG startTimes_ms[] = {   0ul,  0ul + s, 1000ul, 1000ul + s, 2000ul, 2000ul + s, 3000ul, 3000ul + s, 4000ul, 4000ul + l, 64000ul, 64000ul + m, 94000ul, 94000ul + m, 119000ul, 119000ul + vs, 120000ul, 120000ul + vs, 121000ul, 121000ul + vs, 122000ul, 122000ul + vs, 123000ul, 123000ul + vs, 124000ul, 124000ul + l, 124000ul + (raceTime_min * 60000ul), 124000ul + (raceTime_min * 60000ul) + 60000ul};
int spkrStates[]      = {HIGH,  LOW, HIGH,    LOW, HIGH,    LOW, HIGH,    LOW, HIGH,    LOW,  HIGH,     LOW,  HIGH,     LOW,   HIGH,      LOW,   HIGH,      LOW,   HIGH,      LOW,   HIGH,      LOW,   HIGH,      LOW,   HIGH,      LOW,  LOW, LOW};
//int pcpStates[]     = { LOW,  LOW,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW,   LOW,     LOW,   LOW,     LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,  LOW, LOW};
int wpStates[]        = {HIGH, HIGH, HIGH,   HIGH, HIGH,   HIGH, HIGH,   HIGH,  LOW,    LOW,   LOW,     LOW,   LOW,     LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,  LOW, LOW};
int duStates[]        = { LOW,  LOW,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW, HIGH,   HIGH,  HIGH,    HIGH,  HIGH,    HIGH,   HIGH,     HIGH,   HIGH,     HIGH,   HIGH,     HIGH,   HIGH,     HIGH,   HIGH,     HIGH,   HIGH,      LOW,  LOW, LOW};
int rpStates[]        = { LOW,  LOW,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW,   LOW,     LOW,   LOW,     LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,   HIGH,     HIGH,  LOW, LOW};
int fpStates[]        = { HIGH,  HIGH,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW,   LOW,     LOW,   LOW,     LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW, HIGH, LOW};

int currStateCounter = 0;
ULONG zeroTime_ms;

void setup()
{
  //Serial.begin(9600);
  //for (int i = 0; i < numStates; i++)
  //{
  //  Serial.println(startTimes_ms[i]);
  //}
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
  if (digitalRead(RF_D0_PIN) == HIGH) // Button "B"
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
    if (digitalRead(RF_D2_PIN) == HIGH) // Button "A"
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
