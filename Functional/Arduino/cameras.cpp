#include "arduino.h"
#include <Wire.h>
#include <Servo.h>
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define NUM_CAMERAS 2

//camera pins
int _c1 = 22;
int _c2 = 24;
int _c3 = 26;
int currentCamera = 0;

void setCameras(unsigned char buttons)
{
    
    if(CHECK_BIT(buttons, 2)){
        //digitalWrite(13, HIGH);
        currentCamera++;
        if(currentCamera==NUM_CAMERAS) {currentCamera = 0;}
        digitalWrite(22,(CHECK_BIT(buttons, 2)));
        digitalWrite(24,(CHECK_BIT(~(buttons), 2)));
        //digitalWrite(22,CHECK_BIT(currentCamera, 0));
        //digitalWrite(24,CHECK_BIT(currentCamera, 1));
        //digitalWrite(26,CHECK_BIT(currentCamera, 2)); 
       
       /*
        if(currentCamera==0)
        {
            digitalWrite(22,LOW);
            digitalWrite(24,LOW);
            digitalWrite(26,LOW);
        }
        if(currentCamera==1)
        {
            digitalWrite(22,HIGH);
            digitalWrite(24,LOW);
            digitalWrite(26,LOW);
        }
        if(currentCamera==2)
        {
            digitalWrite(22,LOW);
            digitalWrite(24,HIGH);
            digitalWrite(26,LOW);
        }
        if(currentCamera==3)
        {
            digitalWrite(22,HIGH);
            digitalWrite(24,HIGH);
            digitalWrite(26,LOW);
        }
        if(currentCamera==4)
        {
            digitalWrite(22,LOW);
            digitalWrite(24,LOW);
            digitalWrite(26,HIGH);
        }
        if(currentCamera==5)
        {
            digitalWrite(22,HIGH);
            digitalWrite(24,LOW);
            digitalWrite(26,HIGH);
        }
        if(currentCamera==6)
        {
            digitalWrite(22,HIGH);
            digitalWrite(24,HIGH);
            digitalWrite(26,HIGH);
        }
        else
        {
            digitalWrite(22,LOW);
            digitalWrite(24,LOW);
            digitalWrite(26,LOW);
        }
        */
        
    }
    else {
        //digitalWrite(13, LOW);
    }
    
    
    
}
