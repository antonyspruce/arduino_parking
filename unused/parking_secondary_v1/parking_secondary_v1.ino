#include <NewPing.h>

#include <SoftwareSerial.h>

SoftwareSerial softSerial(0, 1);

const int trigPin = 14; 
const int IN1 = 2;
const int IN2 = 4;
const int IN3 = 3;
const int IN4 = 5;
const int IN5 = 6;
const int IN6 = 8;
const int IN7 = 7;
const int IN8 = 9;
const int IN9 = 10;
const int IN10 = 12;
const int IN11 = 11;
const int IN12 = 13;

NewPing sonar0(trigPin, IN1, 200);
NewPing sonar1(trigPin, IN2, 200);  
NewPing sonar2(trigPin, IN3, 200);
NewPing sonar3(trigPin, IN4, 200);  
NewPing sonar4(trigPin, IN5, 200);
NewPing sonar5(trigPin, IN6, 200);  
NewPing sonar6(trigPin, IN7, 200);
NewPing sonar7(trigPin, IN8, 200);  
NewPing sonar8(trigPin, IN9, 200);
NewPing sonar9(trigPin, IN10, 200);  
NewPing sonar10(trigPin, IN11, 200);
NewPing sonar11(trigPin, IN12, 200);   

void setup() {

}

void loop() {
  if (softSerial.read == 1) {
    unsigned int duration[12];
    delay(50);
    duration[0] = sonar0.ping_cm();
    delay(50);
    duration[1] = sonar1.ping_cm();
    delay(50);
    duration[2] = sonar2.ping_cm();
    delay(50);
    duration[3] = sonar3.ping_cm();
    delay(50);
    duration[4] = sonar4.ping_cm();
    delay(50);
    duration[5] = sonar5.ping_cm();
    delay(50);
    duration[6] = sonar6.ping_cm();
    delay(50);
    duration[7] = sonar7.ping_cm();
    delay(50);
    duration[8] = sonar8.ping_cm();
    delay(50);
    duration[9] = sonar9.ping_cm();
    delay(50);
    duration[10] = sonar10.ping_cm();
    delay(50);
    duration[11] = sonar11.ping_cm();
    for (int i=0; i < 12; i++) {
      if (duration > 5) {
        softSerial.print(0);
      } else {
        softSerial.print(1);
      }
    }
  }
}
