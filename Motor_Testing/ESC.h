///////////connecting the ESC to the arduino (switch the pin to the one in use)
/*
 * connect three 24 gauge wires to the arduino (can power the arduino)
 * the yellow wire is the signal wire (connect to any pin on the arduino)
 * the red and black wires are power and ground, they can supple the arduino, but are not nessesary
 * now for the three wires connected to the motor
 * any combination works, if the motor turns the wrong way, switch two wires
 * test the direction without the propellers!
 */

//how to make a h file and make this a ccp file

#include <Servo.h>

Servo servo; //the "servo" the pin will be connected to

void setup() 
{
  servo.attach(5); // make the pin act like a servo
  servo.writeMicroseconds(1500); // set the ESC to 0 Amps (1500us +-25us is the center)
  delay(100); // ensure that the signal was recieved
}

////////how to use the motor
// servo.writeMicroseconds(number from 1100 to 1900)
// less than 1500 should be backward (limit 1100)
// more than 1500 should be forward  (limit 1900)

void loop() 
{
  
}

// function that takes input from -400 to 400
void motorspeed(int mspeed)
{
  int mspeed1 = map(mspeed,-400,400,1100,1900);
  servo.writeMicroseconds(mspeed1);
}


