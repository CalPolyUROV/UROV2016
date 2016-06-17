import serial
import serial.tools.list_ports

import pygame
from pygame.locals import *
from time import sleep

import time

import controller as cont
import serial_finder

__author__ = 'johna, tina and luca'

pygame.init()                                           #initializes the UI
screen = pygame.display.set_mode((1000, 500))
pygame.display.set_caption("Cal Poly Control Center")

background = pygame.Surface(screen.get_size())          # Set background to white.
background = background.convert()
background.fill((250, 250, 250))

ports = serial_finder.serial_ports()
port = serial_finder.find_port(ports, background, screen)

def textwrite(Positionx, Positiony, Text, r = 10, g = 10 , b = 10): #Function that write on screen Strings.

    writeonscreen = Text
    font = pygame.font.Font(None, 25)
    text = font.render(writeonscreen, 0, (r, g, b))
    textpos = text.get_rect()
    textpos.centerx = Positionx
    textpos.centery = Positiony
    background.blit(text, textpos)
    screen.blit(background, (0, 0))

def textdelete(Positionx, Positiony, Text):                 #Function that deletes strings

    writeonscreen = Text
    font = pygame.font.Font(None, 25)
    text = font.render(writeonscreen, 0, (255, 255, 255))
    textpos = text.get_rect()
    textpos.centerx = Positionx
    textpos.centery = Positiony
    background.blit(text, textpos)
    screen.blit(background, (0, 0))

img1 = pygame.image.load('ArtificialHorizon.png')                       #Loads the Artificial Horizon images.
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

pressure = 0.0                  #initiates varibles.
current = 0.0
temperature = 0.0
depth = 0.0
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

st = True

d1 = 0
d2 = 0
d3 = 0

pr = 0
rr =0
yr =0

pchr = 0
yawr = 0
rolr = 0

pchl = [0,0,0,0,0,0,0,0,0,0]
yawl = [0,0,0,0,0,0,0,0,0,0]
roll = [0,0,0,0,0,0,0,0,0,0]

mot = [0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]

start = 0

half_m = False

while True:

    if not cont.isConnected():                                      # Updates controller and shows whether it is connected.
        textdelete(98, 50, "controller connected")
        textwrite(105, 50, "connect the controller", 255, 10, 10)

    if cont.isConnected():
        textdelete(105, 50, "connect the controller")
        textwrite(98, 50, "controller connected", 10, 125, 10)

    textwrite(45, 90, "Pressure:")                     #Labels in black.
    textwrite(40, 110, "Current:")
    textwrite(64, 130, "Temperature:")
    textwrite(34, 150, "Depth:")
    textwrite(25, 190, "YPR:")
    textwrite(40, 170, "YPRraw:")

    textwrite(20, 250, "M1:")                        #Motor info. Work in progress.
    textwrite(20, 270, "M2:")
    textwrite(20, 290, "M3:")
    textwrite(20, 310, "M4:")
    textwrite(20, 330, "M5:")
    textwrite(20, 350, "M6:")
    textwrite(20, 370, "X1:")
    textwrite(20, 390, "X2:")

    textwrite(56, 450, "Half Power:")

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
                if buttons2 == 1:
                    textdelete(130, 450, str(half_m))
                    if half_m:
                        half_m = False
                    else:
                        half_m = True
    try:
        outbound.write("STR") #  sends a signal to tell that this is the start of data
        outbound.write(chr(buttons1))# writes the buttons first
        outbound.write(chr(buttons2))
        #outbound.write(str(int(cont.getPrimaryX())))# casts the floats to ints, then to strings for simple parsing

        if half_m:
            outbound.write(str(int(cont.getPrimaryX()) / 2))
            outbound.write(" ")
            outbound.write(str(int(cont.getPrimaryY()) / 2))
        else:
            outbound.write(str(int(cont.getPrimaryX())))
            outbound.write(" ")
            outbound.write(str(int(cont.getPrimaryY())))

        #outbound.write(" ")
        #outbound.write(str(int(cont.getPrimaryY())))
        outbound.write(" ")
        outbound.write(str(int(cont.getSecondaryX())))
        outbound.write(" ")
        outbound.write(str(int(cont.getSecondaryY())))
        outbound.write(" ")
        #outbound.write(str(int(cont.getTriggers())))

        if half_m:
            outbound.write(str(int(cont.getTriggers()) / 2))
        else:
            outbound.write(str(int(cont.getTriggers())))

        outbound.write(" ")

    except:
        print "Crashed while reading controller input"
        pass

    counter = 10
    proceed = False

    got = ''                                                            #shows in red the old data in case of lost connection.
    textwrite(200, 90, (str(pressure) + " mbars"), 255, 10, 10)
    textwrite(200, 110, (str(current) + " amps"), 255, 10, 10)
    textwrite(200, 130, (str(temperature) + " degrees C"), 255, 10, 10)
    textwrite(200, 150, (str(depth) + " feet"), 255, 10, 10)
    textwrite(200, 170, str(ypr), 255, 10, 10)
    textwrite(200, 190, str(yprraw), 255, 10, 10)

    textwrite(100, 250, str(mot[0]), 255, 10, 10)                        #motor info.
    textwrite(100, 270, str(mot[1]), 255, 10, 10)
    textwrite(100, 290, str(mot[2]), 255, 10, 10)
    textwrite(100, 310, str(mot[3]), 255, 10, 10)
    textwrite(100, 330, str(mot[4]), 255, 10, 10)
    textwrite(100, 350, str(mot[5]), 255, 10, 10)
    textwrite(100, 370, str(mot[6]), 255, 10, 10)
    textwrite(100, 390, str(mot[7]), 255, 10, 10)

    pygame.draw.rect(background, (255, 10, 10), (150, 245, (10 * mot[0]), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 265, (10 * mot[1]), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 285, (10 * mot[2]), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 305, (10 * mot[3]), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 325, (10 * mot[4]), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 345, (10 * mot[5]), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 365, (10 * mot[6]), 10))
    pygame.draw.rect(background, (255, 10, 10), (150, 385, (10 * mot[7]), 10))

    try:
        while True and counter > 0:
            counter -= 1
            if outbound.readable():
                if 'S' == outbound.read(1):
                    if 'T' == outbound.read(1):
                        if 'R' == outbound.read(1):
                            proceed = True
                            if st:
                                start = time.time()
                                st = False
                            break

        if(proceed):                                            # Reads the serial line.
            linesToRead = int(outbound.read(3))                 # allows for up to 999 lines to be read...
            for i in range(0, linesToRead // 2):
                label = outbound.readline().rstrip().lstrip()
                if(label == "PSR"):                                                    # Pressure Data.
                    textdelete(200, 90, str(pressure) + " mbars")
                    pr = str(outbound.readline().rstrip())
                    p3 = p2
                    p2 = p1
                    p1 = float(pr)
                    #p1 = float(pr[0: (len(pr) - 6)])
                    pressure = round((p1 + p2 + p3)/3.0, 2)
                    textwrite(200, 90, str(pressure) + " mbars", 10, 125, 10)

                elif(label == "VLT"):                                                   # Electric Current data.
                    textdelete(200, 110, str(current) + " amps")
                    cr = str(outbound.readline().rstrip())
                    c3 = c2
                    c2 = c1
                    c1 = float(cr)
                    #c1 = float(cr[0: (len(cr) - 5)])
                    current = round((c1 + c2 + c3)/3.0, 2)
                    textwrite(200, 110, str(current) + " amps", 10, 125, 10)

                elif(label == "TMP"):   # Temperature Data.
                    textdelete(200, 130, str(temperature) + " degrees C")
                    tmpr = str(outbound.readline().rstrip())
                    tmp3 = tmp2
                    tmp2 = tmp1
                    tmp1 = float(tmpr)
                    #tmp1 = float(tmpr[0: (len(tmpr) - 10)])
                    temperature = round((tmp1 + tmp2 + tmp3)/3.0, 2)
                    textwrite(200, 130, str(temperature) + " degrees C", 10, 125, 10)

                elif(label == "DPT"):                                                   #Depth data from the arduino.
                    textdelete(200,150, str(depth) + " feet")
                    dr = str(outbound.readline().rstrip())
                    d3 = d2
                    d2 = d1
                    d1 = float(dr)
                    #d1 = float(dr[0: (len(dr) - 5)])
                    depth = round((d1 + d2 + d3)/3.0, 2)
                    textwrite(200, 150, str(depth) + " feet", 10, 125, 10)

                elif(label == "YAW"):                                                   # Taw data from the Accelerometer
                    yaw = outbound.readline().rstrip()
                    index = len(yawl) -1
                    while index > 0:
                        yawl[index] = yawl[index - 1]
                        index -= 1
                    yawl[0] = float(yaw) - yr
                    got = 'T'

                elif(label == "PCH"):                                                      #Pitch data from the Accelerometer
                    pch = outbound.readline().rstrip()
                    index = len(pchl) -1
                    while index > 0:
                        pchl[index] = pchl[index - 1]
                        index -= 1
                    pchl[0] = float(pch) - pr
                    got = got + 'T'

                elif(label == "ROL"):                                                      # Rol data from the accelerometer
                    rol = outbound.readline().rstrip()
                    index = len(roll) -1
                    while index > 0:
                        roll[index] = roll[index - 1]
                        index -= 1
                    roll[0] = float(rol) -rr
                    got = got + 'T'
                elif(label == "STS"):
                    print outbound.readline().rstrip()
                elif(label == "MOT"):                                                       #Data from the motors.
                    recr = outbound.readline().rstrip()
                    #print recr
                    rec = recr.split(",")
                    #print rec
                    for i in range(8):
                        textdelete(100, 250, str(mot[i]))
                        pygame.draw.rect(background, (255, 255, 255), (150, 245, (10 * mot[i]), 10))
                        mot[i] = float(rec[i])
                        textwrite(100, 250, mot[i], 10, 125, 10)
                        if mot[i] < 10 and mot[i] > 0:
                            pygame.draw.rect(background, (10, 125, 10), (150, 245, (10 * mot[i]), 10))
                        elif  mot[i] >= 10 and mot[i] <= 13:
                            pygame.draw.rect(background, (125, 125, 10), (150, 245, (10 * mot[i]), 10))
                        elif mot[i] > 13:
                            pygame.draw.rect(background, (255, 125, 10), (150, 245, (10 * mot[i]), 10))
                else:                                                       #In case it receives weird data, it prints it out on the terminal
                    print "unknown datatype:", label
                    print "data:", outbound.readline().rstrip()
        else:
            if not st:
                end = time.time()
                st = True
                print "Lost data after" + str(end - start) + "seconds"

    except:
        print "Crashed while reading from arduino"
        pass

    try:
        for event in pygame.event.get(pygame.KEYDOWN):
            if event.type == pygame.KEYDOWN:
                if event.key == K_n:                 #Nomalizes the Artificial Horizon
                    yr = int(yaw)
                    pr = int(pch)
                    rr = int(rol)
                elif event.key == K_r:               #Sets the Artificial Horizon to the Raw data from the accelerometer.
                    yr = 0
                    pr = 0
                    rr = 0

    except:
        print "Crashed while reading keyboard inputs"
        pass

    try:
        if abs(pchl[0] - pchl[9]) <= 5:      #Filters the noise in the pitch data.
            max = 10
        elif abs(pchl[0] - pchl[9]) <= 10:
            max = 5
        else:
            max = 3
        i = 0
        pchr = 0
        while i < max:
            pchr = pchr + pchl[i]
            i += 1
        pchr = pchr / i

        if abs(roll[0] - roll[9]) <= 5:      #Filters the noise in the rol data.
            max = 10
        elif abs(roll[0] - roll[9]) <= 10:
            max = 5
        else:
            max =3
        i = 0
        rolr = 0
        while i < max:
            rolr = rolr + roll[i]
            i += 1
        rolr = rolr / i

        yawr = sum(yawl) / len(yawl)            #Filters the noise in the yaw data.

        if got == 'TTT':                                                       #Prints out the Accelerometer data.
            textdelete(200,170, str(ypr))
            textdelete(200,190, str(yprraw))
            yprraw = 'Y:' + str(round(yawr)) + ' P:' + str(round(pchr)) + ' R:' + str(round(rolr))
            ypr = 'Y:' + str(round(float(yaw))) + ' P:' + str(round(float(pch))) + ' R:' + str(round(float(rol)))
            textwrite(200, 170, ypr, 10, 125, 10)
            textwrite(200, 190, yprraw, 10, 125, 10)

    except:
        print "Crashed while computing YPR data"
        pass

    try:
        img1pos = img1.get_rect()                  #Places down the artificial horizon background
        img1pos.centerx = 750
        img1pos.centery = 250 + (round(pchr * 5))
        background.blit(img1, img1pos)

        img2pos = img2.get_rect()                  #Places down the artificial horizon overlay
        img2pos.centerx = 750
        img2pos.centery = 250
        background.blit(img2, img2pos)

        img4 = pygame.transform.rotate(img3, -round(rolr)) #Places down the artificial horizon marker
        img4pos = img4.get_rect()
        img4pos.centerx = 750
        img4pos.centery = 264
        background.blit(img4, img4pos)

    except:
        print "Crashed while loading AH images"
        pass

    textwrite(130, 450, str(half_m))

    pygame.display.update()                         #Updates display
    sleep(0.01)                                     #Waits for 10ms

    for event in pygame.event.get():                #It makes the UI quit if the X button is pressed
        if event.type == QUIT:
            quit()