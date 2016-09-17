const int PRE_COUNT_PIN = 8;
const int WARNING_PIN = 9;
const int DIAL_UP_PIN = 10;
const int RACING_PIN = 11;
const int POST_COUNT_PIN = 12;
const int SPKR_PIN = 13;

#define ULONG unsigned long

const ULONG s = 200ul; // ms
const ULONG m = 1000ul; // ms
const ULONG l = 2000ul; // ms

const ULONG raceTime_min = 2ul;
const ULONG preDelay_ms = 5000ul;

const int numStates = 27;
ULONG startTimes_ms[] = {   0ul,  0ul + s, 1000ul, 1000ul + s, 2000ul, 2000ul + s, 3000ul, 3000ul + s, 4000ul, 4000ul + l, 64000ul, 64000ul + m, 94000ul, 94000ul + m, 119000ul, 119000ul + s, 120000ul, 120000ul + s, 121000ul, 121000ul + s, 122000ul, 122000ul + s, 123000ul, 123000ul + s, 124000ul, 124000ul + l, 124000ul + (raceTime_min * 60000ul)};
int spkrStates[]      = {HIGH,  LOW, HIGH,    LOW, HIGH,    LOW, HIGH,    LOW, HIGH,    LOW,  HIGH,     LOW,  HIGH,     LOW,   HIGH,      LOW,   HIGH,      LOW,   HIGH,      LOW,   HIGH,      LOW,   HIGH,      LOW,   HIGH,      LOW,                         LOW};
//int pcpStates[]     = { LOW,  LOW,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW,   LOW,     LOW,   LOW,     LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,                         LOW};
int wpStates[]        = {HIGH, HIGH, HIGH,   HIGH, HIGH,   HIGH, HIGH,   HIGH,  LOW,    LOW,   LOW,     LOW,   LOW,     LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,                         LOW};
int duStates[]        = { LOW,  LOW,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW, HIGH,   HIGH,  HIGH,    HIGH,  HIGH,    HIGH,   HIGH,     HIGH,   HIGH,     HIGH,   HIGH,     HIGH,   HIGH,     HIGH,   HIGH,     HIGH,   HIGH,      LOW,                         LOW};
int rpStates[]        = { LOW,  LOW,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW,  LOW,    LOW,   LOW,     LOW,   LOW,     LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    LOW,      LOW,    HIGH,    HIGH,                         LOW};

int currStateCounter = 0;
ULONG zeroTime_ms;

void setup()
{
  //Serial.begin(9600);
  //for (int i = 0; i < numStates; i++)
  //{
  //  Serial.println(startTimes_ms[i]);
  //}
  pinMode(PRE_COUNT_PIN, OUTPUT);
  pinMode(WARNING_PIN, OUTPUT);
  pinMode(DIAL_UP_PIN, OUTPUT);
  pinMode(RACING_PIN, OUTPUT);
  pinMode(POST_COUNT_PIN, OUTPUT);
  pinMode(SPKR_PIN, OUTPUT);

  digitalWrite(PRE_COUNT_PIN, HIGH);
  digitalWrite(WARNING_PIN, LOW);
  digitalWrite(DIAL_UP_PIN, LOW);
  digitalWrite(RACING_PIN, LOW);
  digitalWrite(POST_COUNT_PIN, LOW);
  digitalWrite(SPKR_PIN, LOW);

  zeroTime_ms = millis();
}

void loop()
{
  if (currStateCounter >= numStates)
  {
    digitalWrite(POST_COUNT_PIN, HIGH);
  }
  else
  {
    ULONG currTime_ms = millis() - zeroTime_ms;
    if (currTime_ms >= (startTimes_ms[currStateCounter]+preDelay_ms))
    {
      digitalWrite(SPKR_PIN, spkrStates[currStateCounter]);

      digitalWrite(PRE_COUNT_PIN, LOW);
      digitalWrite(WARNING_PIN, wpStates[currStateCounter]);
      digitalWrite(DIAL_UP_PIN, duStates[currStateCounter]);
      digitalWrite(RACING_PIN, rpStates[currStateCounter]);
      currStateCounter++;
    }
  }
}
