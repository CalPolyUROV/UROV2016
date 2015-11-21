#ifndef PRESSURE_H
#define PRESSURE_H

//#include "Arduino.h"

class Pressure
{
  public:
    Pressure();

    void pressureSetup();
    void updatePressureSensor();
    int getPressure();
    int getDepth();
    int getTempTimesTen();
    
   private:
    void resetsensor();
    
    int _pressure;
    int _temp;
};


#endif
