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
pygame.display.set_caption("Cal Poly Control Center")

background = pygame.Surface(screen.get_size())
background = background.convert()
background.fill((250, 250, 250))

ports = serial_finder.serial_ports()
port = serial_finder.find_port(ports, background, screen)

def textWrite(Positionx, Positiony, Text):

    writeonscreen = Text
    font = pygame.font.Font(None, 25)
    text = font.render(writeonscreen, 0, (10, 10, 10))
    textpos = text.get_rect()
    textpos.centerx = Positionx
    textpos.centery = Positiony
    background.blit(text, textpos)
    screen.blit(background, (0, 0))

def textwrite(Positionx, Positiony, Text, r, g, b):

    writeonscreen = Text
    font = pygame.font.Font(None, 25)
    text = font.render(writeonscreen, 0, (r, g, b))
    textpos = text.get_rect()
    textpos.centerx = Positionx
    textpos.centery = Positiony
    background.blit(text, textpos)
    screen.blit(background, (0, 0))

def textdelete(Positionx, Positiony, Text):

    writeonscreen = Text
    font = pygame.font.Font(None, 25)
    text = font.render(writeonscreen, 0, (255, 255, 255))
    textpos = text.get_rect()
    textpos.centerx = Positionx
    textpos.centery = Positiony
    background.blit(text, textpos)
    screen.blit(background, (0, 0))

img1 = pygame.image.load('ArtificialHorizon.png')
img2 = pygame.image.load("ArtificialHorizonOverlay.png")
img3 = pygame.image.load("ArtificialHorizonMarker.png").convert_alpha()

textWrite(64, 30, "Using: " + str(port))

print "Using: ", port
outbound = serial.Serial(
    port=port,
    baudrate=9600,
    parity=serial.PARITY_NONE,   # parity is error checking, odd means the message should have an odd number of 1 bits
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,   # eight bits of information per pulse/packet
    timeout=0.1
)


pygame.display.update()

pressure = 0.0
current = 0.0
temperature = 0.0
accel = 0.0
depth = 0.0
pitchangle = 0
rotateangle = 0
ypr = 0.0
YPR = [0, 0, 0]

while True:

    if not cont.isConnected():
        textdelete(98, 50, "controller connected")
        textwrite(105, 50, "connect the controller", 255, 10, 10)

    if cont.isConnected():
        textdelete(105, 50, "connect the controller")
        textwrite(98, 50, "controller connected", 10, 125, 10)

    textWrite(45, 90, "Pressure:")
    textWrite(40, 110, "Current:")
    textWrite(64, 130, "Temperature:")
    textWrite(64, 150, "Acceleration:")
    textWrite(34, 170, "Depth:")
    textWrite(25, 190, "YPR:")

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
    try:
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

    except:
        pass

    counter = 10
    proceed = False

    textwrite(200, 90, str(pressure), 255, 10, 10)
    textwrite(200, 110, str(current), 255, 10, 10)
    textwrite(200, 130, str(temperature), 255, 10, 10)
    textwrite(200, 150, str(accel), 255, 10, 10)
    textwrite(200, 170, str(depth), 255, 10, 10)
    textwrite(200, 190, str(ypr), 255, 10, 10)

    try:
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
                    textdelete(200, 90, str(pressure))
                    pressure = outbound.readline().rstrip()
                    textwrite(200, 90, str(pressure), 10, 125, 10)

                elif(label == "VLT"):
                    textdelete(200, 110, str(current))
                    current = outbound.readline().rstrip()
                    textwrite(200, 110, str(current), 10, 125, 10)

                elif(label == "TMP"):
                    textdelete(200, 130, str(temperature))
                    temperature = outbound.readline().rstrip()
                    textwrite(200, 130, str(temperature), 10, 125, 10)

                elif(label == "ACL"):
                    textdelete(200, 150, str(accel))
                    accel = str(outbound.readline().rstrip()) + " "
                    accel += str(outbound.readline().rstrip()) + " "
                    accel += str(outbound.readline().rstrip())
                    textwrite(200, 150, accel, 10, 125, 10)

                elif(label == "DPT"):
                    textdelete(200,170, str(depth))
                    depth = str(outbound.readline().rstrip())
                    textwrite(200, 170, depth, 10, 125, 10)

                elif(label == "YPR"):
                    textdelete(200,190, str(ypr))
                    ypr = str(outbound.readline().rstrip())
                    textwrite(200, 190, ypr, 10, 125, 10)

                    pass

                else:
                    print "unknown datatype:", label
                    print "data:", outbound.readline().rstrip()
    except:
        pass

    img1pos = img1.get_rect()
    img1pos.centerx = 750
    img1pos.centery = 250 + (pitchangle * 5)
    background.blit(img1, img1pos)

    img2pos = img2.get_rect()
    img2pos.centerx = 750
    img2pos.centery = 250
    background.blit(img2, img2pos)

    img4 = pygame.transform.rotate(img3, rotateangle)
    img4pos = img4.get_rect()
    img4pos.centerx = 750
    img4pos.centery = 264
    background.blit(img4, img4pos)

    pygame.display.update()
    time.sleep(0.03)

    for event in pygame.event.get():
        if event.type == QUIT:
            quit()