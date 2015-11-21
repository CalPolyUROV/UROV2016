#ifndef COMSMASTERARD_H
#define COMSMASTERARD_H
#define GET_TEMP 1
#define GET_PRES 2
#define GET_DEPT 3


class ComsMasterArd
{
  public:
    ComsMasterArd();
    
    void sendSlaveCmd(int WireEventC);
    int getSlaveData();
   private:
    
    char tempReceive;
    char indicator;
    unsigned int receivedInt;
    
};


#endif
