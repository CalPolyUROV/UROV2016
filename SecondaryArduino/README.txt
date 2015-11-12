This holds the secondary Arduino Stuff



Stuff:
1) I2C communcations. This arduino uno is slave to the primary mega
    Plan:
      Let me know if there is a better way
      a)Call a measurement / Any function
            Master uses "Wire.write(eventCode)"
            Slave has "Wire.onReceive(receiveEvent)", receiveEvent recieves eventCode and holds a Case statement
          Slave Recieves Event Code. Case statement after recieve decides what function(s) to execute
      b)Read Data
            Master uses "Wire.read()"
            Slave has "Wire.onRequest(requestEvent)", requestEvent holds a Case statement
          Slave Sends data to Master based on MOST RECENT Event Code.
            eg. 
              1) Wire.write(temperatureCode);
              2) Wire.read(); //Slave will send temperature data to Master
2) Pressure      (Nov7)
    Updated to Run On Timer One (Because Timer five  does not exist on Uno, nor does pin 45)
    Pins for Uno
        MOSI:   11
        MISO:   12
        SCK:    13
        MCLK:   10   timer1
    Sets Clock Divisor of Timer One to 1 (mode 1)
      Giving AnalogWrite 10 frequency of 32kHz
3) Accelerometer (Nov7)
    I have not looked to see if any pins need updating yet

