#include "ComsMasterArd.h"

    String sendData;
    String receivedString;
//    char tempReceive;
//    unsigned int receivedInt;
ComsMasterArd::ComsMasterArd(){
  ComsMasterSetup();
}
void ComsMasterArd::ComsMasterSetup(){
  //Wire.begin();
}


void ComsMasterArd::sendSlaveCmd(int WireEventCode){
//  Serial.print(WireEventCode);
//  Serial.println("write");
  sendData = String(WireEventCode+10000);

  Wire.beginTransmission(8); // transmit to device #8

  Wire.write(sendData.c_str());

  Wire.endTransmission();    //
}

int ComsMasterArd::getSlaveData(){
//  Serial.println("req");
  receivedString = 0;
  Wire.requestFrom(8,5);
  while (Wire.available()) {
    tempReceive = Wire.read();
    receivedString += tempReceive;
    
  }
  receivedInt = receivedString.toInt();
  receivedInt -= 10000;
  
//  Serial.print(receivedInt);
//  Serial.println("fin");
}
