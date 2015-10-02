
#import "dataStruc.h"

void setup() {  
    Serial.begin(115200);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
}

void wait(){
  while(!Serial.available())
    ;
}
Input readBuffer() {  
        Input input;
        digitalWrite(13, HIGH);
        wait();
        input.buttons = Serial.read();
        wait();
        input.primaryX = Serial.parseFloat();
        Serial.read();
        wait();
        input.primaryY = Serial.parseFloat();
        Serial.read();
        wait();
        input.secondaryX = Serial.parseFloat();
        Serial.read();
        wait();
        input.secondaryY = Serial.parseFloat();
        Serial.read();
        wait();
        input.triggers = Serial.parseFloat();
        Serial.read();
        return input;
}


void loop() {  
    if (Serial.available()) {
        Input i = readBuffer();
        Serial.print("button: ");
        Serial.print(i.buttons);
        Serial.print(" PrimaryX: ");
        Serial.print(i.primaryX);
        Serial.print(" PrimaryY: ");
        Serial.print(i.primaryY);
        Serial.print(" SecondaryX: ");
        Serial.print(i.secondaryX);
        Serial.print(" SecondaryY: ");
        Serial.print(i.secondaryY);
        Serial.print(" Triggers: ");
        Serial.println(i.triggers);
    }
}
