import serial
import serial.tools.list_ports

import pygame
from pygame.locals import *
from time import sleep

import controller as cont
import serial_finder

__author__ = 'johna, tina and luca'

pygame.init()
screen = pygame.display.set_mode((1000, 500))
pygame.display.set_caption("Cal Poly Control Center")

background = pygame.Surface(screen.get_size())
background = background.convert()
background.fill((250, 250, 250))

ports = serial_finder.serial_ports()
port = serial_finder.find_port(ports, background, screen)

def textwrite(Positionx, Positiony, Text, r = 10, g = 10 , b = 10):

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

textwrite(64, 30, "Using: " + str(port))

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
yprraw = 0.0

tmp1 = 0
tmp2 = 0
tmp3 = 0

p1 = 0
p2 = 0
p3 = 0

c1 = 0
c2 = 0
c3 = 0

d1 = 0
d2 = 0
d3 = 0

pr = 0
rr =0
yr =0

pchr = 0
yawr = 0
rolr = 0

pchl = [0,0,0,0,0]
yawl = [0,0,0,0,0]
roll = [0,0,0,0,0]

m1 = 5.0
m2 = 4.0
m3 = 3.0
m4 = 2.0
m5 = 1.0
m6 = 0.0

while True:

    if not cont.isConnected():
        textdelete(98, 50, "controller connected")
        textwrite(105, 50, "connect the controller", 255, 10, 10)

    if cont.isConnected():
        textdelete(105, 50, "connect the controller")
        textwrite(98, 50, "controller connected", 10, 125, 10)

    textwrite(45, 90, "Pressure:")
    textwrite(40, 110, "Current:")
    textwrite(64, 130, "Temperature:")
    textwrite(64, 150, "Acceleration:")
    textwrite(34, 170, "Depth:")
    textwrite(25, 190, "YPR:")
    textwrite(40, 210, "YPRraw:")

    textwrite(20, 250, "M1:")
    textwrite(20, 270, "M2:")
    textwrite(20, 290, "M3:")
    textwrite(20, 310, "M4:")
    textwrite(20, 330, "M5:")
    textwrite(20, 350, "M6:")

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

    got = ''
    textwrite(200, 90, (str(pressure) + " mbars"), 255, 10, 10)
    textwrite(200, 110, (str(current) + " amps"), 255, 10, 10)
    textwrite(200, 130, (str(temperature) + " degrees C"), 255, 10, 10)
    textwrite(200, 150, str(accel), 255, 10, 10)
    textwrite(200, 170, (str(depth) + " feet"), 255, 10, 10)
    textwrite(200, 190, str(ypr), 255, 10, 10)
    textwrite(200, 210, str(yprraw), 255, 10, 10)

    textwrite(100, 250, str(m1), 255, 10, 10)
    textwrite(100, 270, str(m2), 255, 10, 10)
    textwrite(100, 290, str(m3), 255, 10, 10)
    textwrite(100, 310, str(m4), 255, 10, 10)
    textwrite(100, 330, str(m5), 255, 10, 10)
    textwrite(100, 350, str(m6), 255, 10, 10)

    pygame.draw.rect(background, (255, 10, 10), (150, 245, (10 * m1), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 265, (10 * m2), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 285, (10 * m3), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 305, (10 * m4), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 325, (10 * m5), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 345, (10 * m6), 10))

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
                    textdelete(200, 90, str(pressure) + " mbars")
                    pr = str(outbound.readline().rstrip())
                    p3 = p2
                    p2 = p1
                    p1 = float(pr[0: (len(pr) - 6)])
                    pressure = round((p1 + p2 + p3)/3.0, 2)
                    textwrite(200, 90, str(pressure) + " mbars", 10, 125, 10)

                elif(label == "VLT"):
                    textdelete(200, 110, str(current) + " amps")
                    cr = str(outbound.readline().rstrip())
                    c3 = c2
                    c2 = c1
                    c1 = float(cr[0: (len(cr) - 5)])
                    current = round((c1 + c2 + c3)/3.0, 2)
                    textwrite(200, 110, str(current) + " amps", 10, 125, 10)

                elif(label == "TMP"):
                    textdelete(200, 130, str(temperature) + " degrees C")
                    tmpr = str(outbound.readline().rstrip())
                    tmp3 = tmp2
                    tmp2 = tmp1
                    tmp1 = float(tmpr[0: (len(tmpr) - 10)])
                    temperature = round((tmp1 + tmp2 + tmp3)/3.0, 2)
                    textwrite(200, 130, str(temperature) + " degrees C", 10, 125, 10)

                elif(label == "ACL"):
                    textdelete(200, 150, str(accel))
                    accel = str(outbound.readline().rstrip()) + " "
                    accel += str(outbound.readline().rstrip()) + " "
                    accel += str(outbound.readline().rstrip())
                    textwrite(200, 150, accel, 10, 125, 10)

                elif(label == "DPT"):
                    textdelete(200,170, str(depth) + " feet")
                    dr = str(outbound.readline().rstrip())
                    d3 = d2
                    d2 = d1
                    d1 = float(dr[0: (len(dr) - 5)])
                    depth = round((d1 + d2 + d3)/3.0, 2)
                    textwrite(200, 170, str(depth) + " feet", 10, 125, 10)

                elif(label == "YAW"):
                    yaw = outbound.readline().rstrip()
                    index = len(yawl) -1
                    while index > 0:
                        yawl[index] = yawl[index - 1]
                        index -= 1
                    yawl[0] = int(yaw) - yr
                    got = 'T'
                elif(label == "PCH"):
                    pch = outbound.readline().rstrip()
                    index = len(pchl) -1
                    while index > 0:
                        pchl[index] = pchl[index - 1]
                        index -= 1
                    pchl[0] = int(pch) - pr
                    got = got + 'T'
                elif(label == "ROL"):
                    rol = outbound.readline().rstrip()
                    index = len(roll) -1
                    while index > 0:
                        roll[index] = roll[index - 1]
                        index -= 1
                    roll[0] = int(rol) -rr
                    got = got + 'T'
                elif(label == "LLL"):
                    textdelete(100, 250, str(m1))
                    pygame.draw.rect(background, (255, 255, 255), (150, 245, (10 * m1), 10))
                    m1 = outbound.readline()
                    textwrite(100, 250, m1, 10, 125, 10)
                    if m1 < 10 and m1 > 0:
                        pygame.draw.rect(background, (10, 125, 10), (150, 245, (10 * m1), 10))
                    elif  m1 >= 10 and m1 <= 13:
                        pygame.draw.rect(background, (125, 125, 10), (150, 245, (10 * m1), 10))
                    elif m1 > 13:
                        pygame.draw.rect(background, (255, 125, 10), (150, 245, (10 * m1), 10))
                else:
                    print "unknown datatype:", label
                    print "data:", outbound.readline().rstrip()

    except:
        pass

    if got == 'TTT':
        textdelete(200,190, str(ypr))
        textdelete(200,210, str(yprraw))
        yprraw = 'Y:' + str(yaw) + ' P:' + str(pch) + ' R:' + str(rol)
        ypr = 'Y:' + str(yawr) + ' P:' + str(pchr) + ' R:' + str(rolr)
        textwrite(200, 190, ypr, 10, 125, 10)
        textwrite(200, 210, yprraw, 10, 125, 10)

    for event in pygame.event.get(pygame.KEYDOWN):
        if event.type == pygame.KEYDOWN:
            if event.key == K_n:
                yr = int(yaw)
                pr = int(pch)
                rr = int(rol)
            elif event.key == K_r:
                yr = 0
                pr = 0
                rr = 0

    try:
        pchr = sum(pchl) / len(pchl)
        yawr = sum(yawl) / len(yawl)
        rolr = sum(roll) / len(roll)

        img1pos = img1.get_rect()
        img1pos.centerx = 750
        img1pos.centery = 250 + ((int(pchr)) * 5)
        background.blit(img1, img1pos)

        img2pos = img2.get_rect()
        img2pos.centerx = 750
        img2pos.centery = 250
        background.blit(img2, img2pos)

        img4 = pygame.transform.rotate(img3, -int(rolr))
        img4pos = img4.get_rect()
        img4pos.centerx = 750
        img4pos.centery = 264
        background.blit(img4, img4pos)

    except:
        pass

    pygame.display.update()
    sleep(0.01)

    for event in pygame.event.get():
        if event.type == QUIT:
            quit()