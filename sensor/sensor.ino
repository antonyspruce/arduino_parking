#include <AccelStepper.h>

const int analogPin = 0;
const int aIN1 = 2;
const int aIN2 = 3;
const int aIN3 = 4;
const int aIN4 = 5;
const int aIN5 = 8;
const int aIN6 = 9;
const int aIN7 = 10;
const int aIN8 = 11;
int counter = 0;

// Определение используемых констант - количество шагов, координаты
const int aSpeed = 50000;

AccelStepper stepperAct(8, aIN1, aIN3, aIN2, aIN4);
AccelStepper stepperAct1(8, aIN5, aIN7, aIN6, aIN8);

int check() {
  int analogValue = analogRead(analogPin);
  if (analogValue > 500) {
    return 1;
  } else {
    return 0;
  }
}
void setup() {
  stepperAct.setSpeed(aSpeed);
  stepperAct.setMaxSpeed(aSpeed*5);
  stepperAct.setAcceleration(aSpeed*2);
  stepperAct1.setSpeed(aSpeed);
  stepperAct1.setMaxSpeed(aSpeed*5);
  stepperAct1.setAcceleration(aSpeed*2);
  stepperAct.moveTo(2000);
  stepperAct1.moveTo(2000);
  Serial.begin(9600);
  Serial.println("Z-Line Sensor Test");
  Serial.println();   
}

void loop() {
  while (check()) {
    stepperAct.runSpeed();
    stepperAct1.runSpeed();
  }
  Serial.println(counter++); 
  delay(500);
}
