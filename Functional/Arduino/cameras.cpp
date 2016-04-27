#include "arduino.h"
#include <Wire.h>
#include <Servo.h>
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define NUM_CAMERAS 3

//camera pins
uint8_t _c1 = 22;
uint8_t _c2 = 24;
uint8_t _c3 = 26;
uint8_t currentCamera = 0;
bool debounce = 0;

void setCameras(unsigned char buttons)
{
    
    if(CHECK_BIT(buttons, 3)&&debounce){
        debounce = 0;
        //digitalWrite(13, HIGH);
        currentCamera++;
        if(currentCamera==NUM_CAMERAS) {currentCamera = 0;}
        
        //digitalWrite(22,!(CHECK_BIT(currentCamera, 0)));
        digitalWrite(22,(currentcamera==0));
        digitalWrite(24,(currentcamera==1));
        digitalWrite(26,(currentcamera==2));
        digitalWrite(28,(currentcamera==3));
    }
    else {
      debounce = 1;
        //digitalWrite(13, LOW);
    }
    
    
    
}
