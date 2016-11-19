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
#define STATUS_LEDS_REVERSED
const int clkPin = 13;
const int dataPin = 11;
const int numLEDs = 10;

//Battery test:
#define BATT_TEST
const int battTestPin = A2;
const int battMax_counts = 675; // 8.4V (4.2V/cell)
const int battNom_counts = 590; // 7.4V (3.7V/cell)
const int battMin_counts = 513; // 6.6V (3.3V/cell)
