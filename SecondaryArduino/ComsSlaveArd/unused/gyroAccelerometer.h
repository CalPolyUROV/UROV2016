#ifndef GYROACCEL_H
#define GYROACCEL_H

//#include "Arduino.h"

class GyroAccelerometer
{
	public:
		GyroAccelerometer();

                int getAccelX();
                
                int getAccelY();
                
                int getAccelZ();
                
                int getGyroX();
                
                int getGyroY();
                
                int getGyroZ();
                
                int getMagX();
                
                int getMagY();
                
                int getMagZ();
                
               
                  void init_adxl345();
                  void init_hmc5843();
                  void init_itg3200();
                  void read_adxl345();
                  void read_hmc5843();
                  void read_itg3200();
                  void accelSetup();
                  void updateAccelRaw();
                 private:
                 void i2c_read(int address, char reg, int count, char* data);
                 void i2c_write(int address, char reg, char data);
  };
#endif
