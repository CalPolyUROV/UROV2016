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

  int motor1speed; // final motorspeeds
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

  motor1speed = (motor1speedX + motor1speedY + 0.3 * motor1speedR) / 2.3; // add and divide to get motor speeds (no rotation included yet)
  motor2speed = (motor2speedX + motor2speedY + 0.3 * motor2speedR) / 2.3;
  motor3speed = (motor3speedX + motor3speedY + 0.3 * motor3speedR) / 2.3;
  motor4speed = (motor4speedX + motor4speedY + 0.3 * motor4speedR) / 2.3;

  if (motor1speed >= 400) // make sure roundoff error above doesn't affect the map function in writing the positive motorspeeds
  {
    motor1speed = 400;
  }
  if (motor2speed >= 400)
  {
    motor2speed = 400;
  }
  if (motor3speed >= 400)
  {
    motor3speed = 400;
  }
  if (motor4speed >= 400)
  {
    motor4speed = 400;
  }
  
  if (motor1speed <= -400) // make sure roundoff error above doesn't affect the map function in writing the negative motorspeeds
  {
    motor1speed = -400;
  }
  if (motor2speed <= -400)
  {
    motor2speed = -400;
  }
  if (motor3speed <= -400)
  {
    motor3speed = -400;
  }
  if (motor4speed <= -400)
  {
    motor4speed = -400;
  }

  motor_1(motor1speed); // write motorspeeds
  motor_2(motor2speed);
  motor_3(motor3speed);
  motor_4(motor4speed);
  motor_5(Z);
  motor_6(Z);
}
