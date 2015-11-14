This holds the secondary Arduino Stuff



Two Commands for master:
Master Write: Call a function on Slave and set what Request returns.
    Takes 5 digit int, adds 10000(placeholder 1) converts to string and then array of characters.
    Sends array of characters one at a time.
        Slave receives array of characters, appends to a wiped string. Converts string to int and subtracts 10000.
        Stored as 5 digit int, EventCode.
            Depending on EventCode, Slave calls a function (updatePressure, runMotorMaybe?, callibrateSomething)
Master Request: Slave sends data to Master depending on EventCode
    Sends request to slave for 5 bytes of data.
        Slave decides what to data to send from most EventCode (Most Recent Input). 
            (If most recent = update Pressure, send Pressure)
        Slave takes data to be sent (int), adds 10000(placeholder 1) converts to string and then array of characters.
        Slave sends array of characters one at a time.
    Master Receives 5 characters, appends to a wiped string. Converts string to int and subtracts 10000.
    The int is the final Received Data.
    
Limitations:
    Event Code and Return Data limit is 0 to 20000 or so.
        This can likely be improved by sending data for a long or something.
    Maybe interferes with SPI, not sure.
        will make sure soon.
    




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

