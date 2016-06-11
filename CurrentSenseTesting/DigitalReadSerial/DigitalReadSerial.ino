#include <SPI.h>

/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

#define LTC1859_CH0             0x80
#define LTC1859_CH1             0xC0
#define LTC1859_CH2             0x90
#define LTC1859_CH3             0xD0
#define LTC1859_CH4             0xA0
#define LTC1859_CH5             0xE0
#define LTC1859_CH6             0xB0
#define LTC1859_CH7             0xF0

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  spi_enable16();
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(11,OUTPUT);
  pinMode(9,INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  digitalWrite(10,LOW);
  SPI.transfer(LTC1859_CH0);
  delay(10);
  Serial.println(   (float)((uint16_t)(SPI.transfer(LTC1859_CH0)<<8)|(SPI.transfer(LTC1859_CH0)))/13100   );
  digitalWrite(10,HIGH);
  delay(500);
  Serial.print("A busy:");
  Serial.println(digitalRead(9));

digitalWrite(10,LOW);
  SPI.transfer(LTC1859_CH1);
  delay(10);
  Serial.println(   (float)((uint16_t)(SPI.transfer(LTC1859_CH1)<<8)|(SPI.transfer(LTC1859_CH1)))/13100   );
  digitalWrite(10,HIGH);
  delay(500);
  Serial.print("B busy:");
  Serial.println(digitalRead(9));
  
  
  delay(10);        // delay in between reads for stability
}

void spi_enable16(void) // Configures SCK frequency. Use constant defined in header file.
{
  pinMode(SCK, OUTPUT);             //! 1) Setup SCK as output
  pinMode(MOSI, OUTPUT);            //! 2) Setup MOSI as output
  pinMode(SS, OUTPUT);     //! 3) Setup CS as output
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

