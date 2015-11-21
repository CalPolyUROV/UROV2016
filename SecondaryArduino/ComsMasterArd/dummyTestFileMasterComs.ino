#include "ComsMasterArd.h"
#include <Wire.h>

ComsMasterArd Commies;

void setup() {
  Serial.begin(9600);
 Wire.begin();
}

void loop() {
  Serial.println("blah");
  for(int x = 0; x<5; x++){
   Commies.sendSlaveCmd(x);
   delay(200);
   int tempdata = Commies.getSlaveData();
   delay(200);
   Serial.println(tempdata);
    
  }
}
