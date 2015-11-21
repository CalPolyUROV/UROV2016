#include <Servo.h>

//motor pins
int _m1;
int _m2;
int _m3;
int _m4;
int _m5;
int _m6;

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
Servo motor5;
Servo motor6;//the "servo" the pin will be connected to

//////////////////////////////////////////////////////////////////////////attach ESCs to pins and set current to 0 Amps

void motorSetup() 
{
  motor1.attach(_m1); // make the pin act like a servo
  motor2.attach(_m2);
  motor3.attach(_m3);
  motor4.attach(_m4);
  motor5.attach(_m5);
  motor6.attach(_m6);
  motor1.writeMicroseconds(1500); // set the ESCs to 0 Amps (1500us +-25us is the center)
  motor2.writeMicroseconds(1500);
  motor3.writeMicroseconds(1500);
  motor4.writeMicroseconds(1500);
  motor5.writeMicroseconds(1500);
  motor6.writeMicroseconds(1500);
  delay(100); // ensure that the signal was recieved
}