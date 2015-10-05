
#include "dataStruc.h"
#include "QuadMotorShields.h"

//this is temparary because I was working on an arduino UNO with one hardware serial port
QuadMotorShields md;
int led = 13;
void setup() {  
    Serial3.begin(19200);   //the number in here is the baud rate, it is the communication speed, this must be matched in the python
    Serial.begin(19200);     //it does not seem to work at lower baud rates 
    pinMode(led, OUTPUT);     //debugging purposes
    digitalWrite(led, LOW);  //debugging purposes
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
  while(!('S' == Serial3.read() && 'T' == Serial3.read() && 'R' == Serial3.read()))
    wait();
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

void loop() {  
    if (Serial3.available()) {
        //waitForStart();
        Input i = readBuffer();
        
        // debugging purposses, set the hex value to the matching hex button code in the python code to check for it
        processInput(i);
        
        //the following is for debugging, prints all input back out on serial 1
        /*
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
        */
        
    }
}

