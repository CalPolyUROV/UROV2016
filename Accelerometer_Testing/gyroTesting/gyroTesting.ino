#include "Math.h"
#include "Accelerometer.h"      //Accel Lower Level functions called by gyroAccelerometer
#include "gyroAccelerometer.h"  //Accel Higher Level functions called in main
#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  delay(1000);
    Serial.println("ACL"); //tell it the next line is Accelerometer
    Serial.print("Accel: X: ");
    Serial.print(getAccelX());
    Serial.print(" Y: ");
    Serial.print(getAccelY());
    Serial.print(" Z: ");
    Serial.print(getAccelZ());
    Serial.print("\nGyroo: X: ");
    Serial.print(getGyroX());
    Serial.print(" Y: "); 
    Serial.print(getGyroY());
    Serial.print(" Z: ");
    Serial.print(getGyroZ());
    Serial.print("\nMaggg: X: ");
    Serial.print(getMagX());
    Serial.print(" Y: ");
    Serial.print(getMagY());
    Serial.print(" Z: ");
    Serial.print(getMagZ());
    Serial.println();

}
