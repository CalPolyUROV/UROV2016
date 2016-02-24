#include "arduino.h"
//
#define MOTORACCELERATIONMAX 20
//20 motor speed unit things per interval (maybe change to dv/dt later)

///////////connecting the ESC to the arduino (switch the pin to the one in use)
/*
 * connect three 24 gauge wires to the arduino (can power the arduino)
 * the yellow wire is the signal wire (connect to any pin on the arduino)
 * the red and black wires are power and ground, they can supple the arduino, but are not nessesary
 * now for the three wires connected to the motor
 * any combination works, if the motor turns the wrong way, switch two wires
 * test the direction without the propellers!
 */

/////////////////////////////////////////////////////////////////globals
#include <Servo.h>

//motor pins
int _m1 = 3;
int _m2 = 4;
int _m3 = 5;
int _m4 = 6;
int _m5 = 7;
int _m6 = 8;
//limiting variable
int currentMotor1speed = 0;
int currentMotor2speed = 0;
int currentMotor3speed = 0;
int currentMotor4speed = 0;
int currentZspeed = 0;
//

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
Servo motor5;
Servo motor6;//the "servo" the pin will be connected to

int brownOutPrevent(int currentSpeed, int targetSpeed);

//////////////////////////////////////////////////////////////////////////attach ESCs to pins and set current to 0 Amps

void motorSetup() 
{
  motor1.attach(_m1); // make the pin act like a servo
  motor2.attach(_m2);
  motor3.attach(_m3);
  motor4.attach(_m4);
  motor5.attach(_m5);
  motor6.attach(_m6);
  motor1.writeMicroseconds(1500); // set the ESC to 0 Amps (1500us +-25us is the center)
  motor2.writeMicroseconds(1500);
  motor3.writeMicroseconds(1500);
  motor4.writeMicroseconds(1500);
  motor5.writeMicroseconds(1500);
  motor6.writeMicroseconds(1500);
  delay(100); // ensure that the signal was recieved
}

///////////////////////////////////////////////////////////////////////////how to write motorspeeds
// function that takes input from -400 to 400
////////how to use the motor
// servo.writeMicroseconds(number from 1100 to 1900)
// less than 1500 should be backward (limit 1100)
// more than 1500 should be forward  (limit 1900)
void motor_1(int mspeed) 
{
  int mspeed1 = map(mspeed,-400,400,1100,1900);
  motor1.writeMicroseconds(mspeed1);
}

void motor_2(int mspeed)
{
  int mspeed1 = map(mspeed,-400,400,1100,1900);
  motor2.writeMicroseconds(mspeed1);
}

void motor_3(int mspeed)
{
  int mspeed1 = map(mspeed,-400,400,1100,1900);
  motor3.writeMicroseconds(mspeed1);
}

void motor_4(int mspeed)
{
  int mspeed1 = map(mspeed,-400,400,1100,1900);
  motor4.writeMicroseconds(mspeed1);
}

void motor_5(int mspeed)
{
  int mspeed1 = map(mspeed,-400,400,1100,1900);
  motor5.writeMicroseconds(mspeed1);
}

void motor_6(int mspeed)
{
  int mspeed1 = map(mspeed,-400,400,1100,1900);
  motor6.writeMicroseconds(mspeed1);
}


///////////////////////////////////////////// allow rotation and planar movement simultaniously (takes x y z and r, then sets motorspeeds)
void setMotors(int X,int Y,int Z,int R)
{
  int motor1speedX; // initialize variables (used to calculate final motorspeed)
  int motor2speedX;
  int motor3speedX;
  int motor4speedX;
  
  int motor1speedY;
  int motor2speedY;
  int motor3speedY;
  int motor4speedY;
  
  int motor1speedR;
  int motor2speedR;
  int motor3speedR;
  int motor4speedR;

  int motor1speed; // (final motorspeeds)
  int motor2speed;
  int motor3speed;
  int motor4speed;

  motor1speedY = Y; // get directions forward backward
  motor2speedY = Y;
  motor3speedY = Y;
  motor4speedY = Y;
  
  motor1speedX = X; // get directions right left
  motor2speedX = X * -1;
  motor3speedX = X * -1;
  motor4speedX = X;

  motor1speedR = R * -1; // get directions turning
  motor2speedR = R;
  motor3speedR = R * -1;
  motor4speedR = R;

  motor1speed = Z;//(motor1speedX + motor1speedY) / 2; // add and divide to get motor speeds (no rotation included yet)
  motor2speed = Z;//(motor1speedX + motor1speedY) / 2;
  motor3speed = Z;//(motor1speedX + motor1speedY) / 2;
  motor4speed = Z;//(motor1speedX + motor1speedY) / 2;


  
  currentMotor1speed = brownOutPrevent(currentMotor1speed, motor1speed);
  currentMotor2speed = brownOutPrevent(currentMotor2speed, motor2speed);
  currentMotor3speed = brownOutPrevent(currentMotor3speed, motor3speed);
  currentMotor4speed = brownOutPrevent(currentMotor4speed, motor4speed);
  currentZspeed = brownOutPrevent(currentZspeed, Z);

//limiting code end

  motor_1(currentMotor1speed); // write motorspeeds
  motor_2(currentMotor2speed);
  motor_3(currentMotor3speed);
  motor_4(currentMotor4speed);
  motor_5(currentZspeed);
  motor_6(currentZspeed);
}

int brownOutPrevent(int currentSpeed, int targetSpeed){   //Comments use 20 for MOTORACCELERATIONMAX
  //adding change limiting code here
  if((targetSpeed - currentSpeed)> MOTORACCELERATIONMAX){   //If target is over 20 above, only increase by 20
    return currentSpeed + MOTORACCELERATIONMAX; 
  } else if((currentSpeed - targetSpeed)> MOTORACCELERATIONMAX){ //Else, If target is over 20 below, only decrease by 20
    return currentSpeed - MOTORACCELERATIONMAX;
  } 
  else {
    return targetSpeed; //Else, it is okay to set to target
  }
}



