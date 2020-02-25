#include <Servo.h>

Servo tServo;

void setup() {
  // put your setup code here, to run once:
  tServo.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
  tServo.write(50);
  delay(1);
  tServo.write(10);
  delay(1);
}

//kalmen
//complementary
