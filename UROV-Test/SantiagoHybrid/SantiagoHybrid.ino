#include <QuadMotorShields.h> //Found at PoluluMotor
#include <ArduinoJson.h> //Found at PoluluMotor
#include <avr/wdt.h>

#include <SPI.h>

QuadMotorShields md;


int x,y,z,s1,s2, reset = 0;
int count = 0;
long timer = 0;
int receivedCommand = 1;


void setup() {
   //ASSIGN DIGITAL PINS
   x = 0;
   y = 0;
   z = 0;   
   
   
   pinMode(2,OUTPUT);
   pinMode(3,OUTPUT);
   delay(1000);

}


void loop()
{
   if (receivedCommand) {
         
         x = (int)root["X"];
         y = (int)root["Y"];
         //r = root["R"];
         z = (int)root["Z"];
         //write to the solenoids here
         s1 = (int)root["S1"];
         s2 = (int)root["S2"];
         
         if(s1>0 or s1<0){
           digitalWrite(2, HIGH); //write to pin(s) controlling s1
         }
         else{
             digitalWrite(2, LOW); 
         }
         if(s2>0 or s2<0){
           digitalWrite(3, LOW); //write to pin(s) controlling s2
           setup();
           
          
          }
         else{
             digitalWrite(3, HIGH);
         }
         //
         
         //competition median code
//         oldx = (oldx + x)/2;
//         oldy = (oldy + y)/2;
//         oldz = (oldz + z)/2;
//         delay(500);
         //competition median changes below
         md.setM1Speed(x);
         md.setM2Speed(y);
         md.setM3Speed(-z); //The pins assigned to this function may cause the ethernet shield to fail
         md.setM4Speed(z);
         if(x >= 395 || y >= 395 || z >= 400){
           md.setM1Brake(400);
           md.setM2Brake(400);
           md.setM3Brake(400);
           md.setM4Brake(400);
         }
      
      

   }
}

void hdReset()
{
  int pin=3;
  pinMode(pin, OUTPUT);
  digitalWrite(3, LOW);
}

void software_Reboot()
{
  wdt_enable(WDTO_30MS);
  
  while(1)
  {
    break;
  }
}

long startTimer(){ //returns starting time in millis
   return millis();
}
int endTimer(long start){ //returns time elapsed in seconds
   return (int)(millis() - start);
}

void(* resetFunc) (void) = 0;//declare reset function at address 0

void resetIfNotConnected(int lastCommunication){ //to keep us from manually resetting arduino
   if (lastCommunication >= 1000000){
      Serial.println("RESETTING");
      resetFunc(); //call reset function
   }
}

void printDebugInfo(int x, int y, int z, String s) {    
   Serial.println(s);
   Serial.print("X:");
   Serial.println(x);
   Serial.print("Y:");
   Serial.println(y);
   Serial.print("Z:");
   Serial.println(z);
}

