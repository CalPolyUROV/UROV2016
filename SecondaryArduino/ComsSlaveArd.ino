









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
//GyroAccelerometer  GyroAccelerometer();
void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Pressure.pressureSetup();
  Pressure.updatePressureSensor();
  //Gyro.accelSetup();
  //Gyro.updateAccelRaw();
  // Pressure Requests
  Wire.onRequest(requestEventPressure); // register event
  Wire.onRequest(requestEventDepth); // depth
  Wire.onRequest(requestEventTemp); // temp
  
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEventPressure() {
  int currentPressure = Pressure.getPressure();
  Wire.write(currentPressure); // respond with message of 6 bytes
  // as expected by master
}
void requestEventDepth() {
  int currentDepth = Pressure.getDepth();
  Wire.write(currentDepth); // respond with message of 6 bytes
  // as expected by master
}
void requestEventTemp() {
  int currentTemp = Pressure.getTempTimesTen();
  Wire.write(currentTemp); // respond with message of 6 bytes
  // as expected by master
}
