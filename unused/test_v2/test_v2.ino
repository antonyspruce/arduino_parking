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
//const int aSpeed = 10;

AccelStepper stepperRight(1, rStep, rDir);
AccelStepper stepperLeft(1, lStep, lDir);
AccelStepper stepperAct(8, aIN1, aIN3, aIN2, aIN4);
MultiStepper vertS;

int lots[12][3] = {
  { 0, 0, 0},
  { 0, 0, 0},
  { 0, 0, 0},
  { 0, 0, 0},
  { 0, 0, 0},
  { 0, 0, 0},
  { 0, 0, 0},
  { 0, 0, 0},
  { 0, 0, 0},
  { 0, 0, 0},
  { 0, 0, 0},
  { 0, 0, 0}
};

void moveVertical(int coord) {
  if (coord != 0) {
    long cor[2] = {coord * 200, coord * -200};
    vertS.moveTo(cor);
  } else {
    long cor[2] = {coord * -200, coord * 200};
    vertS.moveTo(cor);
  }
  vertS.runSpeedToPosition();
}

void moveHorizontal(int coord) {
  long cor[2] = {coord * 200, coord * 200};
  vertS.moveTo(cor);
  vertS.runSpeedToPosition();
}

void useAct(int dir) {
  if (dir == 1) {
    stepperAct.runToNewPosition(6500);
  } else if (dir == -1) {
    stepperAct.runToNewPosition(0);
  }
}

void moveCor(int dir) {
  long cor[2] = {dir * 20, dir * -20};
  vertS.moveTo(cor);
  vertS.runSpeedToPosition();
}

int firstFree() {
  for (int i = 0; i < 12; i++) {
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
  delay(500);
  moveCor(-1);
  delay(500);
  moveHorizontal(x);
  delay(500);
  useAct(1);
  delay(500);
  moveCor(1);
  delay(1000);
  moveCor(1);
  delay(500);
  useAct(-1);
  delay(500);
  moveCor(-1);
  delay(500);
  moveHorizontal(-x);
  delay(500);
  moveVertical(-y);
  delay(5000);

  moveVertical(y);
  delay(500);
  moveCor(1);
  delay(500);
  moveHorizontal(x);
  delay(500);
  useAct(1);
  delay(500);
  moveCor(-1);
  delay(1000);
  moveCor(-1);
  delay(500);
  useAct(-1);
  delay(500);
  moveCor(1);
  delay(500);
  moveHorizontal(-x);
  delay(500);
  moveVertical(-y);
  delay(500);
}

void takeCar(int lot) {
  int x = lots[lot][1], y = lots[lot][2];
  lots[lot][0] = 1;
  moveVertical(y);
  delay(500);
  moveCor(-1);
  delay(500);
  moveHorizontal(x);
  delay(500);
  useAct(1);
  delay(500);
  moveCor(1);
  delay(1000);
  moveCor(1);
  delay(500);
  useAct(-1);
  delay(500);
  moveCor(-1);
  delay(500);
  moveHorizontal(-x);
  delay(500);
  moveVertical(-y);
  delay(5000);

  moveVertical(y);
  delay(500);
  moveCor(-1);
  delay(500);
  moveHorizontal(x);
  delay(500);
  useAct(1);
  delay(500);
  moveCor(1);
  delay(1000);
  moveCor(1);
  delay(500);
  useAct(-1);
  delay(500);
  moveCor(-1);
  delay(500);
  moveVertical(-y);
  delay(500);
  moveHorizontal(-x);
  delay(500);
}

int dir = 1;

void setup() {
  Serial.begin(9600);
  stepperRight.setSpeed(nSpeed);
  stepperRight.setAcceleration(nSpeed * 1.5);
  stepperRight.setMaxSpeed(nSpeed * 2);
  stepperLeft.setSpeed(nSpeed);
  stepperLeft.setAcceleration(nSpeed * 1.5);
  stepperLeft.setMaxSpeed(nSpeed * 2);
  stepperAct.setSpeed(700);
  stepperAct.setAcceleration(700);
  stepperAct.setMaxSpeed(700);
  vertS.addStepper(stepperRight);
  vertS.addStepper(stepperLeft);
}

void loop() {
  if (Serial.available()) {
    int code = Serial.parseInt();
    if (code == 1) {
      long cor[2];
      cor[0] = 0;
      cor[1] = 0;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      cor[0] = -650;
      cor[1] = -650;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      cor[0] = 1400;
      cor[1] = -100;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      cor[0] = 750;
      cor[1] = -750;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      cor[0] = 0;
      cor[1] = 0;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
    } else if (code == 2) {
      long cor[2];
      cor[0] = 0;
      cor[1] = 0;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      cor[0] = 875;
      cor[1] = 875;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      stepperAct.move(-7000);
      stepperAct.runToPosition();
      delay(2000);
      cor[0] = 0;
      cor[1] = 0;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
    } else if (code == 3) {
      long cor[2];
      cor[0] = 0;
      cor[1] = 0;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      cor[0] = 875;
      cor[1] = 875;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      stepperAct.move(7000);
      stepperAct.runToPosition();
      delay(2000);
      cor[0] = 0;
      cor[1] = 0;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
    } else if (code == 4) {
      long cor[2];
      cor[0] = 0;
      cor[1] = 0;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
       cor[0] = -650;
      cor[1] = -650;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      cor[0] = 225;
      cor[1] = -1525;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      stepperAct.move(-7000);
      stepperAct.runToPosition();
      delay(2000);
      cor[0] = -650;
      cor[1] = -650;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      cor[0] = 0;
      cor[1] = 0;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
    } else if (code == 5) {
      long cor[2];
      cor[0] = 0;
      cor[1] = 0;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
       cor[0] = 650;
      cor[1] = 650;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      cor[0] = 1525;
      cor[1] = -225;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      stepperAct.move(7000);
      stepperAct.runToPosition();
      delay(2000);
      cor[0] = 650;
      cor[1] = 650;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
      cor[0] = 0;
      cor[1] = 0;
      vertS.moveTo(cor);
      vertS.runSpeedToPosition();
      delay(2000);
    } else if (code == 6) {
      stepperAct.move(-7000);
      stepperAct.runToPosition();
    }
  }
}
