



// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

//#include "gyroAccelerometer.h"

#include <Wire.h>
#include "pressure.h"
#include "gyroAccelerometer.h"
//
Pressure Pressure;
GyroAccelerometer Gyro;
String receivedString;
char tempReceive;
unsigned int WireEventCode = 2;
unsigned int WireNextSendData;
String WireSendString;
char sendArray[6];
char WireDataType;


void setup() {
  Serial.begin(9600);
  Wire.begin(8);                // join i2c bus with address #8

  //Gyro.accelSetup();
  //Gyro.updateAccelRaw();
  // Pressure Requests
  Wire.onReceive(receiveEvent); //Info is received
  Wire.onRequest(requestEvent); //Info is Requested
  
  //Pressure.pressureSetup();
  //Pressure.updatePressureSensor();
  
}

void loop() {
  delay(500);
  Pressure.updatePressureSensor();
  Serial.println(".");
}

void receiveEvent(int howMany) {
  receivedString = 0;//Clear recieved string
    
  WireDataType = Wire.read(); //Take 1 char, data type.
  while (Wire.available()) { 
    tempReceive = Wire.read(); //Receive 5 chars, data
    receivedString += tempReceive;
  }
  WireEventCode = receivedString.toInt();
  //Serial.print(receivedString);
  //Serial.println("rawI");
  //WireEventCode -= 10000;
  Serial.print(WireDataType);//debug print
  Serial.print(WireEventCode);
  Serial.println("Instruction");
  WireNextSendData = WireEventCode * 2;
  
  WireNextSendData = WireCallEvent(WireEventCode);
}

int WireCallEvent (int EventCode){
  switch(EventCode) {
    case 1:
      //Pressure.updatePressureSensor();
      return Pressure.getPressure();
      break;
    case 2:
      //Pressure.updatePressureSensor();
      return Pressure.getTempTimesTen();
      break;
    case 3:
      //Pressure.updatePressureSensor();
      return Pressure.getDepth();
    default:
      return 1030;
    break;
  }
  
}

void requestEvent() {
  Serial.print(WireNextSendData);
  Serial.println("return");
  WireSendString = 'g' + String(WireNextSendData);
  //Serial.print(WireSendString);
  //Serial.println("rawRet");
  Wire.write(WireSendString.c_str());

}


