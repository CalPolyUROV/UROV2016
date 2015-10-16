import serial
import time
import controller as cont
from sys import platform
import serial.tools.list_ports
import sys
import math
__author__ = 'johna'
p = 0

if platform == "linux" or platform == "linux2":
    p = "/dev/ttyUSB0"
elif platform == "darwin":
    p = ""
elif platform == "win32":
    p = "3"
outbound = serial.Serial(
    port=p,
    baudrate=9600,
    parity=serial.PARITY_NONE,   # parity is error checking, odd means the message should have an odd number of 1 bits
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS   # eight bits of information per pulse/packet
)

cont.update()
if not cont.isConnected():
    print "connect the controller"
cont.update()
while not cont.isConnected():
    cont.update()
print "controller connected"

# this is the main loop of the program that updates the controller then sends that modified input to the arduino
while 1:
    cont.update()
    buttons1 = 0x0
    buttons2 = 0x0
    # going to eight would include the start button; however, it seems that when 0x80 (only the start button) is sent
    # the arduino lags for a second or two and reports false values for buttons
    for i in range(0, cont.getNumButtons()):
        if(cont.getButton(i)):
            if(cont.getValueForButton(i) <= 0xFF):
                buttons1 += cont.getValueForButton(i)
            else:
                buttons2 += cont.getValueForButton(i) >> 8

    outbound.write("STR")                               #  sends a signal to tell that this is the start of data
    outbound.write(chr(buttons1))                       # writes the buttons first
    outbound.write(chr(buttons2))
    outbound.write(str(int(cont.getPrimaryX())))        # casts the floats to ints, then to strings for simple parsing
    outbound.write(" ")
    outbound.write(str(int(cont.getPrimaryY())))
    outbound.write(" ")
    outbound.write(str(int(cont.getSecondaryX())))
    outbound.write(" ")
    outbound.write(str(int(cont.getSecondaryY())))
    outbound.write(" ")
    outbound.write(str(int(cont.getTriggers())))
    outbound.write(" ")

    while True:
        if 'S' == outbound.read(1):
            if 'T' == outbound.read(1):
                if 'R' == outbound.read(1):
                    break

    linesToRead = int(outbound.read(3))                 # allows for up to 999 bytes to be read
    for i in range(0, linesToRead):
        print outbound.readline(),
    time.sleep(0.1)


