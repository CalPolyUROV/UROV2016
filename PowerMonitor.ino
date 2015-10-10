float supply = 0;
float Arduino_in = 0;
int Analog_read  = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
Analog_read = analogRead(A0);
Arduino_in = (Analog_read * 5.0)/1024;

supply = 6.620 * Arduino_in; // Multiplying Arduinoin by conversion factor to get Supply Voltage
Serial.print("Supply Voltage=");
Serial.println(supply);
delay(1000);
}
