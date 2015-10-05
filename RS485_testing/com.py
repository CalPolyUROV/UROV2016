import serial
import time
import controller as cont
import math
__author__ = 'johna'

outbound = serial.Serial(
    # port=X refers to com(X+1) so port 4 is com5
    port=19,
    baudrate=19200,
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
    for i in range(0, 7):
        if cont.getButton(i):
            buttons1 += (1 << i)

    for i in range(7, 10):
        if(cont.getButton(i)):
            buttons2 += (1 << (i - 7))

    #outbound.write("STR")                               # sends a signal to tell that this is the start of data
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
    time.sleep(0.1)                                    # allows for chirps of information rather than a stream



