#include "ComsMasterArd.h"

    String sendData;
    String receivedString;
//    char tempReceive;
//    unsigned int receivedInt;
ComsMasterArd::ComsMasterArd(){
  Wire.begin();
}



void ComsMasterArd::sendSlaveCmd(int WireEventCode){
//  Serial.print(WireEventCode);
//  Serial.println("write");
 sendData = 'a' + String(WireEventCode);

  Wire.beginTransmission(8); // transmit to device #8

  Wire.write(sendData.c_str());

  Wire.endTransmission();    //
}

int ComsMasterArd::getSlaveData(){
//  Serial.println("req");
  receivedString = 0;
  Wire.requestFrom(8,6);
  if ( Wire.available()){
    indicator = Wire.read();
    while (Wire.available()) {
      tempReceive = Wire.read();
      receivedString += tempReceive;
    }
  }
  receivedInt = receivedString.toInt();
  //receivedInt -= 10000;
  return receivedInt;
//  Serial.print(receivedInt);
//  Serial.println("fin");
}
