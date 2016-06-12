#include "arduino.h"
#include <Wire.h>
#include <Servo.h>
#include <SPI.h>
#include "currentSensing.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define NUM_CAMERAS 2
#define PACKET_SIZE 8
#define CVST 48

//intermediate variables
uint16_t currentReading = 0;
byte regRead = 0x00;

uint16_t ampReading(uint8_t myRegister)
{
    regRead = myRegister;
    digitalWrite(CURRENTSELECT,LOW);
    SPI.transfer(regRead);
    delayMicroseconds(15);
    currentReading = (((uint16_t)(SPI.transfer(regRead)<<8)| (SPI.transfer(regRead))));
    
    digitalWrite(CURRENTSELECT,HIGH);
    //Serial.println(digitalRead(9));
    return currentReading;
    
}

uint16_t *arrAmpReading(void) {
    uint8_t ndx = 0;
    uint16_t regNum = 0;
    uint16_t toReturn[PACKET_SIZE];
    SPI.transfer(regNumber(0));
    digitalWrite(CVST, HIGH);
    delayMicroseconds(1);
    digitalWrite(CVST, LOW);
    delayMicroseconds(1);

    
    digitalWrite(CURRENTSELECT,LOW);
    for (ndx = 0; ndx < PACKET_SIZE; ndx++) {
        toReturn[PACKET_SIZE] = ((uint16_t)(SPI.transfer(regNumber(ndx))<<8)| (SPI.transfer(regNumber(ndx + 1))));
        delayMicroseconds(15);
        digitalWrite(CVST, HIGH);
        delayMicroseconds(1);
        digitalWrite(CVST, LOW);
        delayMicroseconds(1);
    }
    digitalWrite(CURRENTSELECT,HIGH);
    
    //toReturn[0] = (((uint16_t)(SPI.transfer( )<<8)| (SPI.transfer(  ))))
    //toReturn[1] = (((uint16_t)(SPI.transfer( )<<8)| (SPI.transfer(  ))))
    
    return toReturn;
}

void spi_enable16(void) // Configures SCK frequency. Use constant defined in header file.
{
    pinMode(SCK, OUTPUT);             //! 1) Setup SCK as output
    pinMode(MOSI, OUTPUT);            //! 2) Setup MOSI as output
    pinMode(SS, OUTPUT);     //! 3) Setup CS as output
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16);
}
                      
uint8_t regNumber(uint8_t regValue) {
   uint8_t returnVal = 0;
   returnVal += (regValue << 3) & 0x30;
   returnVal += (regValue << 6) & 0x40;
   return returnVal;
}
