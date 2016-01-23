
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
screen = pygame.display.set_mode((400, 300))
pygame.display.set_caption("Cal Poly Control Center")

background = pygame.Surface(screen.get_size())
background = background.convert()
background.fill((250, 250, 250))

ports = serial_finder.serial_ports()
port = serial_finder.find_port(ports, background, screen)

writeonscreen = "Using: " +str(port)
font = pygame.font.Font(None, 25)
text = font.render(writeonscreen, 1, (10, 10, 10))
textpos = text.get_rect()
textpos.centerx = 64
textpos.centery = 30
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

    writeonscreen = "controller connected"
    font = pygame.font.Font(None, 25)
    text = font.render(writeonscreen, 0, (255, 255, 255))
    textpos = text.get_rect()
    textpos.centerx = 98
    textpos.centery = 50
    background.blit(text, textpos)
    screen.blit(background, (0, 0))
    pygame.display.flip()

    writeonscreen = "connect the controller"
    font = pygame.font.Font(None, 25)
    text = font.render(writeonscreen, 0, (255, 10, 10))
    textpos = text.get_rect()
    textpos.centerx = 105
    textpos.centery = 50
    background.blit(text, textpos)
    screen.blit(background, (0, 0))
    pygame.display.flip()

cont.update()
while not cont.isConnected():
    cont.update()
print "controller connected"

writeonscreen = "connect the controller"
font = pygame.font.Font(None, 25)
text = font.render(writeonscreen, 0, (255, 255, 255))
textpos = text.get_rect()
textpos.centerx = 105
textpos.centery = 50
background.blit(text, textpos)
screen.blit(background, (0, 0))
pygame.display.flip()

writeonscreen = "controller connected"
font = pygame.font.Font(None, 25)
text = font.render(writeonscreen, 1, (10, 125, 10))
textpos = text.get_rect()
textpos.centerx = 98
textpos.centery = 50
background.blit(text, textpos)
screen.blit(background, (0, 0))
pygame.display.flip()

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


writeonscreen = "Pressure:"
font = pygame.font.Font(None, 25)
text = font.render(writeonscreen, 1, (10, 10, 10))
textpos = text.get_rect()
textpos.centerx = 45
textpos.centery = 90
background.blit(text, textpos)
screen.blit(background, (0, 0))
pygame.display.flip()

writeonscreen = "Voltage:"
font = pygame.font.Font(None, 25)
text = font.render(writeonscreen, 1, (10, 10, 10))
textpos = text.get_rect()
textpos.centerx = 40
textpos.centery = 110
background.blit(text, textpos)
screen.blit(background, (0, 0))
pygame.display.flip()

writeonscreen = "Temperature:"
font = pygame.font.Font(None, 25)
text = font.render(writeonscreen, 1, (10, 10, 10))
textpos = text.get_rect()
textpos.centerx = 64
textpos.centery = 130
background.blit(text, textpos)
screen.blit(background, (0, 0))
pygame.display.flip()

writeonscreen = "Acceleration:"
font = pygame.font.Font(None, 25)
text = font.render(writeonscreen, 1, (10, 10, 10))
textpos = text.get_rect()
textpos.centerx = 64
textpos.centery = 150
background.blit(text, textpos)
screen.blit(background, (0, 0))
pygame.display.flip()

writeonscreen = "Depth:"
font = pygame.font.Font(None, 25)
text = font.render(writeonscreen, 1, (10, 10, 10))
textpos = text.get_rect()
textpos.centerx = 35
textpos.centery = 170
background.blit(text, textpos)
screen.blit(background, (0, 0))
pygame.display.flip()

def textwrite(Positionx, Positiony, Text):

    writeonscreen = Text
    font = pygame.font.Font(None, 25)
    text = font.render(writeonscreen, 0, (10, 10, 10))
    textpos = text.get_rect()
    textpos.centerx = Positionx
    textpos.centery = Positiony
    background.blit(text, textpos)
    screen.blit(background, (0, 0))
    pygame.display.flip()

def textwrite(Positionx, Positiony, Text, r, g, b):

    writeonscreen = Text
    font = pygame.font.Font(None, 25)
    text = font.render(writeonscreen, 0, (r, g, b))
    textpos = text.get_rect()
    textpos.centerx = Positionx
    textpos.centery = Positiony
    background.blit(text, textpos)
    screen.blit(background, (0, 0))
    pygame.display.flip()

def textdelete(Positionx, Positiony, Text):

    writeonscreen = Text
    font = pygame.font.Font(None, 25)
    text = font.render(writeonscreen, 0, (255, 255, 255))
    textpos = text.get_rect()
    textpos.centerx = Positionx
    textpos.centery = Positiony
    background.blit(text, textpos)
    screen.blit(background, (0, 0))
    pygame.display.flip()

def update(background, screen):
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

    #background.fill((255, 255, 255), Rect(125,80,140,120))
    #screen.blit(background, (0, 0))
    #pygame.display.flip()

    #textdelete(180, 90, str(outbound.readline().rstrip()))

    #textdelete(150 ,90, "None")
    #textdelete(150 ,110, "None")
    #textdelete(150 ,130, "None")
    #textdelete(150 ,150, "None")
    #textdelete(150 ,170, "None")

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
                #pressureOut['text'] = outbound.readline().rstrip()
                pressureOut['bg'] = "green"
                pressureLabel['bg'] = "green"

                textwrite(180, 90, str(outbound.readline().rstrip()), 10, 125, 10)

            elif(label == "VLT"):
                #voltageOut['text'] = outbound.readline().rstrip()
                voltageOut['bg'] = "green"
                voltageLabel['bg'] = "green"

                textwrite(180, 110, str(outbound.readline().rstrip()), 10, 125, 10)

            elif(label == "TMP"):
                #tempOut['text'] = outbound.readline().rstrip()
                tempOut['bg'] = "green"
                tempLabel['bg'] = "green"

                textwrite(180, 130, str(outbound.readline().rstrip()), 10, 125, 10)

            elif(label == "ACL"):
                #accelOut['text'] = outbound.readline().rstrip() + '\n'
                #ccelOut['text'] += outbound.readline().rstrip() + '\n'
                #accelOut['text'] += outbound.readline().rstrip()
                accelOut['bg'] = "green"
                accelLabel['bg'] = "green"

                writeonscreen = str(outbound.readline().rstrip()) + " "
                writeonscreen += str(outbound.readline().rstrip()) + " "
                writeonscreen += str(outbound.readline().rstrip())
                textwrite(180, 150, writeonscreen, 10, 125, 10)

            elif(label == "DPT"):
                #depthOut['text'] = outbound.readline().rstrip()
                depthOut['bg'] = "green"
                depthLabel['bg'] = "green"

                depth = str(outbound.readline().rstrip())

                textwrite(180, 170, depth, 10, 125, 10)

            else:
                print "unknown datatype:", label
                print "data:", outbound.readline().rstrip()

            for event in pygame.event.get():
                if event.type == QUIT:
                    pygame.quit()
                    return

    time.sleep(0.5)

    background.fill((255, 255, 255), Rect(125,80,120,100))
    screen.blit(background, (0, 0))
    pygame.display.flip()

    root.after(1, update(background, screen))

root.after(1000, update(background, screen))
button = tk.Button(root, text='Stop', width=25, command=root.destroy)
button.grid(row=5, column=0, columnspan=2)
root.mainloop()



