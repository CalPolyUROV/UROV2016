
#include "dataStruc.h"
//#include "QuadMotorShields.h"
#include <SoftwareSerial.h>


//this is temparary because I was working on an arduino UNO with one hardware serial port
//QuadMotorShields md;

SoftwareSerial mySerial(51,50);

int led = 13;
int writingPin = 4; //this is the pin to control whether it is recieving or sending
void setup() {  
    mySerial.begin(9600);   //the number in here is the baud rate, it is the communication speed, this must be matched in the python
    Serial.begin(9600);     //it does not seem to work at lower baud rates 
    pinMode(led, OUTPUT);     //debugging purposes
    digitalWrite(led, LOW);  //debugging purposes
    pinMode(writingPin, OUTPUT);
    digitalWrite(writingPin, LOW);
}

//looks cleaner than the empty while loop being everywhere in the code
void wait(){
  while(!mySerial.available())
    ;
}

//detects the start signal without accidently overshooting it because of short circuting logic
//except for input such as SSTR, that will be skipped. There should be multiple characters to 
//prevent random bytes getting past
void waitForStart(){
  while(true){
    wait();
    if('S' == mySerial.read()){
      wait();
      if('T' == mySerial.read()){
        wait();
        if('R' == mySerial.read()){
          break;
        }
      }
    }
  }
}

Input readBuffer() {  
        Input input;
        wait();//makes sure that a byte of data is not missed 
        input.buttons1 = mySerial.read();
        wait();
        input.buttons2 = mySerial.read();
        wait();
        input.primaryX = mySerial.parseInt();
        mySerial.read();
        wait();
        input.primaryY = mySerial.parseInt();
        mySerial.read();
        wait();
        input.secondaryX = mySerial.parseInt();
        mySerial.read();
        wait();
        input.secondaryY = mySerial.parseInt();
        mySerial.read();
        wait();
        input.triggers = mySerial.parseInt();
        mySerial.read();
        return input;
}
//void processInput(Input i){
//  int forward = i.primaryY;
//  int right = i.primaryX;
//  
//  md.setM1Speed(forward/2 + right/2);
//  md.setM2Speed(forward/2 - right/2);
//  if(i.buttons1 & 0x2){
//    md.setM3Speed(100);
//    md.setM4Speed(100);
//  }
//  else if(i.buttons1 & 0x1){
//    md.setM3Speed(-100);
//    md.setM4Speed(-100);
//  } else {
//    md.setM3Speed(0);
//    md.setM4Speed(0);
//  }
//}

void writeToCommand(Input i){
  mySerial.print("STR");
  mySerial.print("001"); //print the number of lines of input the python program can read in three digits
  mySerial.print(i.buttons1);
  mySerial.print(" ");
  mySerial.println(i.buttons2);
}

void loop() { 
     if (mySerial.available()) {
        waitForStart();
        Input i = readBuffer();

        digitalWrite(writingPin, HIGH);
        writeToCommand(i); //this is where the code to write back to topside goes.
        digitalWrite(writingPin, LOW);
        
        //processInput(i);//gives the inputs to the motors
        
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

