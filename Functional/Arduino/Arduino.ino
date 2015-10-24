
#include "dataStruc.h"
#include "QuadMotorShields.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include "pressure.h"

//all pins used must be lised here! either as a variable to change quickly later or as a comment if it is in another file

int serialWritePin = 2; //this is the pin to control whether it is recieving or sending

///// Pins used by Quad Motor Shields //////
//
//31, 33, 29, A0, 25, 27, 23, A1, 
//42, 44, 40, 24, 26, 22
//
//////////////////////////////////

//End of pin listings


QuadMotorShields md;



//SoftwareSerial Serial3(14, 15);
void setup() {  
    Serial3.begin(9600);   //the number in here is the baud rate, it is the communication speed, this must be matched in the python
    Serial.begin(9600);     //it does not seem to work at lower baud rates 
    pinMode(serialWritePin, OUTPUT);
    digitalWrite(serialWritePin, LOW);
    pressureSetup();
}

//looks cleaner than the empty while loop being everywhere in the code
void wait(){
  while(!Serial3.available())
    ;
}

//detects the start signal without accidently overshooting it because of short circuting logic
//except for input such as SSTR, that will be skipped. There should be multiple characters to 
//prevent random bytes getting past
void waitForStart(){
  while(true){
    wait();
    if('S' == Serial3.read()){
      wait();
      if('T' == Serial3.read()){
        wait();
        if('R' == Serial3.read()){
          break;
        }
      }
    }
  }
}

Input readBuffer() {  
        Input input;
        wait();//makes sure that a byte of data is not missed 
        input.buttons1 = Serial3.read();
        wait();
        input.buttons2 = Serial3.read();
        wait();
        input.primaryX = Serial3.parseInt();
        Serial3.read();
        wait();
        input.primaryY = Serial3.parseInt();
        Serial3.read();
        wait();
        input.secondaryX = Serial3.parseInt();
        Serial3.read();
        wait();
        input.secondaryY = Serial3.parseInt();
        Serial3.read();
        wait();
        input.triggers = Serial3.parseInt();
        Serial3.read();
        return input;
}
void processInput(Input i){
  int forward = i.primaryY;
  int right = i.primaryX;
  
  md.setM1Speed(forward/2 + right/2);
  md.setM2Speed(forward/2 - right/2);
  if(i.buttons1 & 0x2){
    md.setM3Speed(100);
    md.setM4Speed(100);
  }
  else if(i.buttons1 & 0x1){
    md.setM3Speed(-100);
    md.setM4Speed(-100);
  } else {
    md.setM3Speed(0);
    md.setM4Speed(0);
  }
}

void writeToCommand(Input i){
  Serial3.print("STR");
  Serial3.print("002"); //print the number of lines of input the python program can read in three digits
  Serial3.println(i.buttons1);
  Serial3.println("Pressure");
  //Serial3.println(updatePressure());
}

void loop() { 
     if (Serial3.available()) {
        waitForStart();
        Input i = readBuffer();

        digitalWrite(serialWritePin, HIGH);
        writeToCommand(i); //this is where the code to write back to topside goes.
        delay(50);         //this delay allows for hardware serial to work with rs485
        digitalWrite(serialWritePin, LOW);
        
        processInput(i);//gives the inputs to the motors
        
        //the following is for debugging, prints all input back out on the serial used for programming the arduino
        
        Serial.print("buttons: ");
        Serial.print(i.buttons2);
        Serial.print(" ");
        Serial.print(i.buttons1);
        Serial.print(" X1: ");
        Serial.print(i.primaryX);
        Serial.print(" Y1: ");
        Serial.print(i.primaryY);
        Serial.print(" X2: ");
        Serial.print(i.secondaryX);
        Serial.print(" Y2: ");
        Serial.print(i.secondaryY);
        Serial.print(" Trig: ");
        Serial.println(i.triggers);
        
        
    }
}

