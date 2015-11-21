#include "arduino.h"
#include "ComsMasterArd.h"

    String sendData;
    String receivedString;
//    char tempReceive;
//    unsigned int receivedInt;
ComsMasterArd::ComsMasterArd(){
  Wire.begin();
}


void ComsMasterArd::sendSlavePrm(int WireParam){
  mosiType = 'p';
  sendInt(WireParam);
}
void ComsMasterArd::sendSlaveCmd(int WireEventCode){
  mosiType = 'c';
  sendInt(WireEventCode);
}

void ComsMasterArd::sendInt(int data){
 sendData = mosiType + String(data);
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(sendData.c_str());
  Wire.endTransmission();    //
}

int ComsMasterArd::getSlaveData(){

  receivedString = "";
  Wire.requestFrom(8,6);
  if ( Wire.available()){
    misoType = Wire.read();
    while (Wire.available()) {
      tempReceive = Wire.read();
      receivedString += tempReceive;
    }
  }
  receivedInt = receivedString.toInt();

  return receivedInt;

}
