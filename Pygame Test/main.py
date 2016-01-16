
import Tkinter as tk

import serial
import serial.tools.list_ports

import pygame
from pygame.locals import *
import time

import controller as cont
import serial_finder

__author__ = 'johna'

pygame.init()
screen = pygame.display.set_mode((1000, 500))
pygame.display.set_caption('UROV GUI')

background = pygame.Surface(screen.get_size())
background = background.convert()
background.fill((250, 250, 250))

ports = serial_finder.serial_ports()
port = serial_finder.find_port(ports, background, screen)

writeonscreen = "Using: " +str(port)
font = pygame.font.Font(None, 50)
text = font.render(writeonscreen, 1, (10, 10, 10))
textpos = text.get_rect()
textpos.centerx = background.get_rect().centerx + 150
textpos.centery = background.get_rect().centery
background.blit(text, textpos)
screen.blit(background, (0, 0))
pygame.display.flip()

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
pressureLabel = tk.Label(root, fg="black", background='white', text="Pressure: ")

pressureOut = tk.Label(root, fg="black", background="white")
voltageLabel = tk.Label(root, fg="black", background='white', text="Voltage: ")
voltageOut = tk.Label(root, fg="black", background="white")
accelLabel = tk.Label(root, fg="black", background='white', text="Acceleration: ")
accelOut = tk.Label(root, fg="black", background="white")
tempLabel = tk.Label(root, fg="black", background='white', text="Temperature: ")
tempOut = tk.Label(root, fg="black", background="white")
depthLabel = tk.Label(root, fg="black", background='white', text="Depth: ")
depthOut = tk.Label(root, fg="black", background='white')
pressureLabel.grid(row=0, column=0)
voltageLabel.grid(row=1, column=0)
accelLabel.grid(row=2, column=0)
tempLabel.grid(row=3, column=0)
depthLabel.grid(row=4, column=0)
pressureOut.grid(row=0, column=1)
voltageOut.grid(row=1, column=1)
accelOut.grid(row=2, column=1)
tempOut.grid(row=3, column=1)
depthOut.grid(row=4, column=1)
def update():
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
    pressureOut['bg'] = "red"
    voltageOut['bg'] = "red"
    tempOut['bg'] = "red"
    accelOut['bg'] = "red"
    depthOut['bg'] = "red"
    pressureLabel['bg'] = "red"
    voltageLabel['bg'] = "red"
    tempLabel['bg'] = "red"
    accelLabel['bg'] = "red"
    depthLabel['bg'] = "red"
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
        for i in range(0, linesToRead // 2):
            label = outbound.readline().rstrip().lstrip()
            if(label == "PSR"):
                pressureOut['text'] = outbound.readline().rstrip()
                pressureOut['bg'] = "green"
                pressureLabel['bg'] = "green"
            elif(label == "VLT"):
                voltageOut['text'] = outbound.readline().rstrip()
                voltageOut['bg'] = "green"
                voltageLabel['bg'] = "green"
            elif(label == "TMP"):
                tempOut['text'] = outbound.readline().rstrip()
                tempOut['bg'] = "green"
                tempLabel['bg'] = "green"
            elif(label == "ACL"):
                accelOut['text'] = outbound.readline().rstrip() + '\n'
                accelOut['text'] += outbound.readline().rstrip() + '\n'
                accelOut['text'] += outbound.readline().rstrip()
                accelOut['bg'] = "green"
                accelLabel['bg'] = "green"
            elif(label == "DPT"):
                depthOut['text'] = outbound.readline().rstrip()
                depthOut['bg'] = "green"
                depthLabel['bg'] = "green"
            else:
                print "unknown datatype:", label
                print "data:", outbound.readline().rstrip()
    root.after(100, update)

root.after(1000, update)
button = tk.Button(root, text='Stop', width=25, command=root.destroy)
button.grid(row=5, column=0, columnspan=2)
root.mainloop()



