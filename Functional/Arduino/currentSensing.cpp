#include "arduino.h"
#include <Wire.h>
#include <Servo.h>
#include <SPI.h>
#include "currentSensing.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define NUM_CAMERAS 2

//intermediate variables
float currentReading = 0;
byte regRead = 0x00;

uint8_t ampReading(uint8_t myRegister)
{
    regRead = myRegister;
    digitalWrite(CURRENTSELECT,LOW);
    SPI.transfer(regRead);
    delayMicroseconds(15);
    currentReading = (float)(((uint16_t)(SPI.transfer(regRead)<<8)| (SPI.transfer(regRead)))/13100);
    digitalWrite(CURRENTSELECT,HIGH);
    //Serial.println(digitalRead(9));
    return currentReading;
    
}


void spi_enable16(void) // Configures SCK frequency. Use constant defined in header file.
{
    pinMode(SCK, OUTPUT);             //! 1) Setup SCK as output
    pinMode(MOSI, OUTPUT);            //! 2) Setup MOSI as output
    pinMode(SS, OUTPUT);     //! 3) Setup CS as output
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);
}
