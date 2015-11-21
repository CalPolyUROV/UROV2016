#ifndef COMSMASTER_H
#define COMSMASTER_H


class ComsMasterArd
{
  public:
    ComsMasterArd();

    int masterRequest();
    void masterWrite(int WireEventCode);
   private:
    
    String sendData;
    String receivedString;
    unsigned int receivedInt;
    //int comsIndex;
    char tempReceive;
};


#endif
