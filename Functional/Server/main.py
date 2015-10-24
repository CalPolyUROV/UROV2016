import Tkinter as tk

import serial
import serial.tools.list_ports

import controller as cont
import serial_finder

__author__ = 'johna'

ports = serial_finder.serial_ports()
port = serial_finder.find_port(ports)
print "Using: ", port
outbound = serial.Serial(
    port=port,
    baudrate=9600,
    parity=serial.PARITY_NONE,   # parity is error checking, odd means the message should have an odd number of 1 bits
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,   # eight bits of information per pulse/packet
    timeout=0.1
)

cont.update()
if not cont.isConnected():
    print "connect the controller"
cont.update()
while not cont.isConnected():
    cont.update()
print "controller connected"

root = tk.Tk()
root.title("Cal Poly Control Center")
outputLabel = tk.Label(root, fg="black", background='white')

def update():
    global outputLabel
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
    counter = 10
    proceed = False
    while True and counter > 0:
        counter -= 1
        if outbound.readable():
            if 'S' == outbound.read(1):
                if 'T' == outbound.read(1):
                    if 'R' == outbound.read(1):
                        proceed = True
                        break
    if(proceed):

        linesToRead = int(outbound.read(3))                 # allows for up to 999 lines to be read...
        for i in range(0, linesToRead):
            outputLabel['text'] = outbound.readline().rstrip()
    outputLabel.after(100, update)

outputLabel.grid(row=0, column=0)
outputLabel.after(1000, update)
button = tk.Button(root, text='Stop', width=25, command=root.destroy)
button.grid(row=5, column=0, columnspan=2)
root.mainloop()



