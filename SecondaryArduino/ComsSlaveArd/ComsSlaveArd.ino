



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
unsigned int WireEventCode;
unsigned int WireNextSendData;
String WireSendString;
int ParameterStack;

//I2c only sends char arrays. Therefore a data type char is included in index 0 of the array.
//It tells what kind of data was sent.
//It also serves as a buffer. 
char WireMosiType; //Holds Mosi Data Type: c_ommand or p_arameter
char WireMisoType; //Holds Miso Data Type: n_ull or i_nt or s_tring

void setup() {
  Wire.begin(8);                // join i2c bus with address #8

  //Gyro.accelSetup();
  //Gyro.updateAccelRaw();
  // Pressure Requests
  Wire.onReceive(receiveEvent); //Info is received
  Wire.onRequest(requestEvent); //Info is Requested
  
}

void loop() {
  delay(500);
  Pressure.updatePressureSensor();
}

void receiveEvent(int howMany) {
  receivedString = "";//Clear recieved string
  
  if(Wire.available()){  
    WireMosiType = Wire.read(); //Take 1 char, data type.
      while (Wire.available()) { 
        tempReceive = Wire.read(); //Receive 5 chars, data
        receivedString += tempReceive;
    }
  }
  
  WireEventCode = receivedString.toInt(); //Turn received into an int
  if(WireMosiType = 'c'){                 //treat as command if command type
    WireNextSendData = WireCallEvent(WireEventCode);
  } else if(WireMosiType = 'p' {          //store as parameter if param type
    ParameterStack = WireEventCode;
  }
}


int WireCallEvent (int EventCode){
  switch(EventCode) {
    case 1:
      WireMisoType = 'i'; //misoType is kinda pointless, its just a buffer so the right number of chars are returned on i2c. 
                          //I can't think of any way to use it either; when master makes a request it already knows what it should be recieving.
      return Pressure.getTempTimesTen();  //Its not temp times ten anymore, its just temp. to be changed.
      break;
    case 2:
      WireMisoType = 'i';
      return Pressure.getPressure();
      break;
    case 3:
      WireMisoType = 'i';
      return Pressure.getDepth();
    default:
      WireMisoType = 'n';
      return 1337;        //You'll know something is wrong if you see this 1337
    break;
  }
  
}

void requestEvent() {
  WireSendString = WireMisoType + String(WireNextSendData); //padding the string with the misoType
  Wire.write(WireSendString.c_str());

}


