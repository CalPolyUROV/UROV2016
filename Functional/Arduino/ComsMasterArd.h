#include <Wire.h>

#ifndef COMSMASTERARD_H
#define COMSMASTERARD_H


#define GET_TEMP 1
#define GET_PRES 2
#define GET_DEPT 3
#define GET_YAW  4
#define GET_PCH 5
#define GET_ROL 6
#define START_SMCW 7
#define START_SMCCW 8
#define STOP_SM 9
#define ARB_SM 10
#define STK_SM 11
#define SM_CW 1
#define SM_CCW 0

#define COMMANDCHAR 'C'
#define SLAVEPRM0 'a'
#define SLAVEPRM1 'b'
#define SLAVEPRM2 'c'
#define SLAVEPRM3 'd'
#define SLAVESTACK 's'

class ComsMasterArd
{
  public:
    ComsMasterArd();
    
    void sendSlaveCmd(int WireEventC);
    void sendSlavePrm(int WireParam, char mosi_type);
    void sendInt(int data);
    int getSlaveData();
   private:
    char mosiType;
    char misoType;
    char tempReceive;
    unsigned int receivedInt;
    
};


#endif
