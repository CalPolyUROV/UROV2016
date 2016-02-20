#ifndef COMSMASTERARD_H
#define COMSMASTERARD_H
#include <Wire.h>
#define GET_TEMP 1
#define GET_PRES 2
#define GET_DEPT 3
#define GET_YAW  4
#define GET_PCH 5
#define GET_ROL 6


class ComsMasterArd
{
  public:
    ComsMasterArd();
    
    void sendSlaveCmd(int WireEventC);
    void sendSlavePrm(int WireParam);
    void sendInt(int data);
    int getSlaveData();
   private:
    char mosiType;
    char misoType;
    char tempReceive;
    unsigned int receivedInt;
    
};


#endif
