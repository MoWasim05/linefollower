bool debugMode = false;

//motor pins
#define rFwd 8 //ain2
#define rRev 7 //ain1
#define PWMa 6

#define lFwd 2 //bin1
#define lRev 3 //bin2
#define PWMb 5

// buttons
#define btn1 9  // ir enable
#define btn2 10 // motor enable
#define btn3 11 // debug

// leds
#define ledRed 12   // Debug Mode Indicator
#define ledBlue 4   // Junction Indicator
#define irEnablePin 13

//system states
bool irState = false; 
bool motorState = false;

// debounce Tracking
bool lastBtn3 = HIGH;
bool lastBtn2 = HIGH;
bool lastBtn1 = HIGH;

//sensor initialization
int irPins[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
int irValues[8];
int irValDigital[8];
int threshold = 850;
int sensorSum;
int sensorWeight;
int weightVal[8] = {10, 20, 30, 40, 50, 60, 70, 80};
int sensorBit;
int bitWeight[8] = {1, 2, 4, 8, 16, 32, 64, 128};

//PID variables
float linePosition;
float centerPosition = 45;
float error;
float derivative;
float previousError;
int baseSpeed = 255;
float kp = 9;
float kd = 0;

// motor speed variables
int adjustSpeed = 20;

// Track sequence variables
int junctionCount = 0; // CHANGE TO 0 LATER
bool isTurning = false; // prevent double counting of junction
bool onJunction = false; 

// junction reader buffer
int junctionBuffer = 0; 
int requiredReads = 10; //times requried before it is counted as a buffer

// junction retaining buffer
int offBuffer = 0;
int requiredOffReads = 40; //loops before junction detected as off

// whiteSequence (white space)
unsigned long whiteStartTime = 0; // Remembers the exact millisecond the line vanished
bool whiteTimer = false;
int pushDuration = 300; // 1000 milliseconds = 1 second of pushing distance

void setup() {

  // Control Setup
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(irEnablePin, OUTPUT);

  // Motor Setup
  pinMode(rFwd, OUTPUT); pinMode(rRev, OUTPUT); pinMode(PWMa, OUTPUT);
  pinMode(lFwd, OUTPUT); pinMode(lRev, OUTPUT); pinMode(PWMb, OUTPUT);

  // IR setup
  for (int i = 0; i < 8; i++)
    pinMode(irPins[i], INPUT);

  // starts off
  digitalWrite(ledRed, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(irEnablePin, LOW);
  
  Serial.begin(115200); //
}

void loop() {
  int currentBtn3 = digitalRead(btn3);
  int currentBtn2 = digitalRead(btn2);
  int currentBtn1 = digitalRead(btn1);

  // btn1 is now strictly for IR
  if (lastBtn1 == HIGH && currentBtn1 == LOW) {
    delay(10);
    if (digitalRead(btn1) == LOW) {
      if (irState == false) {
        irState = true; 
        digitalWrite(irEnablePin, HIGH);
      }
      else {
        irState = false;
        digitalWrite(irEnablePin, LOW);
      }
    }
  }
  lastBtn1 = currentBtn1;

  // btn2 is motor enable
  if (lastBtn2 == HIGH && currentBtn2 == LOW) {
    delay (10);
    if(digitalRead(btn2) == LOW){
      if (motorState == false) {
        motorState = true; 
      }
      else {
        motorState = false; 
      }
    }
  }
  lastBtn2 = currentBtn2;

  // btn3 is now strictly for Debug Mode / Serial Prints
  if (lastBtn3 == HIGH && currentBtn3 == LOW) {
    delay (10);
    if(digitalRead(btn3) == LOW){
      if (debugMode == false) {
        debugMode = true; 
        digitalWrite(ledRed, HIGH);
      }
      else {
        debugMode = false; 
        digitalWrite(ledRed, LOW);
      }
    }
  }
  lastBtn3 = currentBtn3;

  //competition mode
  if (irState == true && motorState == true && debugMode == false) {
    readLine();
    PIDControl(baseSpeed, kp, kd);
  }
  else if (irState == true && motorState == false && debugMode == true) {
    // Sensor Test Mode (Motors OFF, Sensors ON)
    readJunction();
    motor(0, 0);
  }
  else if (irState == true && motorState == true && debugMode == true) {
    readLine();
    PIDControl(baseSpeed, kp, kd);
    debugMode = true;
  }
  else if (motorState == true) {
    motor(baseSpeed - adjustSpeed, baseSpeed); // Blind Drive
  }
  else {
    motor(0, 0);
    junctionCount = 0; //change this back to 32
    digitalWrite(ledBlue, LOW); // Everything OFF

  }
}
