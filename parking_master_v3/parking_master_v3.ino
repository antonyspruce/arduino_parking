#include <AccelStepper.h>
#include <MultiStepper.h>

const int rDir = 2;
const int rStep = 3;
const int lDir = 4;
const int lStep = 5;
const int aIN1 = 8;
const int aIN2 = 9;
const int aIN3 = 10;
const int aIN4 = 11;

const int nSpeed = 50;
const int aSpeed = 4096;

const int xC = 650;
const int yC = 875;
const int cC = 10;

int rCurrent = 0;
int lCurrent = 0;

AccelStepper stepperRight(1, rStep, rDir);
AccelStepper stepperLeft(1, lStep, lDir);
AccelStepper stepperAct(8, aIN1, aIN2, aIN3, aIN4);
MultiStepper vertS;

int lots[6][3] = {
  { 0, 0, 0 },
  { 0, 1, 0 },
  { 0, -1, 0 },
  { 0, 0, 1 },
  { 0, 1, 1 },
  { 0, -1, 1 }
};

void moveVertical(int h) {
  rCurrent += h * yC;
  lCurrent -= h * yC;
  long cor[2] = { rCurrent, lCurrent };
  vertS.moveTo(cor);
  vertS.runSpeedToPosition();
  delay(500);
}

void moveHorizontal(int c) {
  rCurrent += c * xC;
  lCurrent += c * xC;
  long cor[2] = { rCurrent, lCurrent };
  vertS.moveTo(cor);
  vertS.runSpeedToPosition();
  delay(500);
}

void useAct(int dir) {
  stepperAct.move(dir * 7000);
  stepperAct.runToPosition();
  delay(2000)
}

void moveCor(int dir) {
  if (dir > 0) {
    rCurrent += cC;
    lCurrent -= cC;
  } else {
    rCurrent -= cC;
    lCurrent += cC;
  }
  long cor[2] = { rCurrent, lCurrent };
  vertS.moveTo(cor);
  vertS.runSpeedToPosition();
  delay(2000)
}

int firstFree() {
  for (int i = 0; i < 6; i++) {
    if (lots[i][1] == 1) {
      return i;
    }
    return -1;
  }
}
void placeCar(int lot) {
  int x = lots[lot][1], y = lots[lot][2];
  lots[lot][0] = 0;
  moveVertical(y);
  moveCor(-1);
  moveHorizontal(x);
  moveCor(1);
  useAct(1);
  moveCor(-1);
  moveHorizontal(-x);
  moveVertical(-y);

  moveVertical(y);
  moveCor(-1);
  moveHorizontal(x);
  moveCor(1);
  useAct(-1);
  moveCor(-1);
  moveHorizontal(-x);
  moveVertical(-y);
}

void takeCar(int lot) {
  int x = lots[lot][1], y = lots[lot][2];
  lots[lot][0] = 1;
  moveVertical(y);
  moveCor(-1);
  moveHorizontal(x);
  moveCor(1);
  useAct(-1);
  moveCor(-1);
  moveHorizontal(-x);
  moveVertical(-y);

  moveVertical(y);
  moveCor(-1);
  moveHorizontal(x);
  moveCor(1);
  useAct(11);
  moveCor(-1);
  moveHorizontal(-x);
  moveVertical(-y);
}

void setup() {
  Serial.begin(9600);
  stepperRight.setSpeed(nSpeed);
  stepperRight.setAcceleration(nSpeed * 1.5);
  stepperRight.setMaxSpeed(nSpeed * 2);
  stepperLeft.setSpeed(nSpeed);
  stepperLeft.setAcceleration(nSpeed * 1.5);
  stepperLeft.setMaxSpeed(nSpeed * 2);
  stepperAct.setSpeed(aSpeed);
  stepperAct.setAcceleration(aSpeed);
  stepperAct.setMaxSpeed(aSpeed);
  vertS.addStepper(stepperRight);
  vertS.addStepper(stepperLeft);
}

void loop() {
  if (Serial.available()) {
    int code = Serial.parseInt();
    if (code == 7) {
      const int lot = firstFree();
      if (lot != -1) {
        placeCar(lot);
      }
    } else if (code >= 1 && code <= 6) {
      if (lots[code - 1][0] == 0) {
        takeCar(code - 1);
      }
    }
  }
}