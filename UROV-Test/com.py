import serial
import time
import controller as cont
import math
__author__ = 'johna'

ser = serial.Serial(
    port=4,
    baudrate=115200,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)
print "connect the controller"
cont.update()
while not cont.isConnected():
    cont.update()
print "controller connected"
while(1):
    cont.update()
    buttons = 0x0
    for i in range(0, 8):
        if cont.getButton(i):
            buttons += (1 << i)
    #ser.print("STR")#should I send an ok signal to start the communication? how long does that take?
    ser.write(chr(buttons))
    ser.write(str(int(cont.getPrimaryX())))
    ser.write(" ")
    ser.write(str(int(cont.getPrimaryY())))
    ser.write(" ")
    ser.write(str(int(cont.getSecondaryX())))
    ser.write(" ")
    ser.write(str(int(cont.getSecondaryY())))
    ser.write(" ")
    ser.write(str(int(cont.getTriggers())))
    ser.write(" ")
    time.sleep(0.1)
    #ser.write("END")#should tis be replied to? or just not sent?



