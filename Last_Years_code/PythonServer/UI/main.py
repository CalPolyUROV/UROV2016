# -*- coding: utf-8 -*-
#note to sam: sda is port 20 scl is port 21
import socket
import json

import time
from PyQt4.QtCore import QObject, pyqtSignal, pyqtSlot
from sfml.window import Joystick as j
import random

def readAxis(axis):
    """Takes axis as an argument (4 axis- X, Y, Z and R), and returns the value at that instance."""
    #Note: TECHNICALLY 6 axis - there is also a U and V axis
    if isConnected():
        return j.get_axis_position(0, j.__getattribute__(j, axis)) #this is lazy and may not work; TEST!
    else:
        pass
    
def readButton(button):
    """Takes a button value (buttons 1-8) and returns whether or not it is pushed."""
    if isConnected():
        return j.is_button_pressed(0, button)
    else:
        pass
    
def isConnected():
    """Returns True if joystick is connected."""
    return j.is_connected(0)
    

def process2DAxis(l, h):
    """Processes the lateral and horizontal axis of a joystick, to be used as inputs
    for a motor controller."""
    Ellipsis
    
    

def encapsulateData(fp = "write.txt", **kwargs):
    """Encapsulates all kwargs in their key:value pairs, returns a JSON object.
    Objects to be encapsulated: ALL OF THEM (Axis X-V, Buttons 1-10."""
    fp = open(fp, "w")
    json.dump(kwargs, fp, indent = 4, sort_keys = True)
    
    
#    
#BUFSIZE = 4096    #reasonably sized buffer for data
###---Socket/TCP-IP Code occurs here ---**
#def send(data = str):
#    conn.send(data.encode())
#def recieve():
#    recieve.data = conn.recv(BUFSIZE)
#    recieve.data = recieve.data.decode()
#    return recieve.data

##---Socket/TCP-IP Code ends here ---**

class Server(QObject):

    x = pyqtSignal(int)
    count = 0
    def __init__(self):
        #self.host = socket.gethostbyaddr('211.255.132.121')[2][0]
        self.host = socket.gethostbyname(socket.gethostname())
        print "HOST: ", self.host
        #print socket.gethostbyaddr('211.255.132.121') #Make sure the host exists!
        self.port = 1900 #NOTE: PORT MAY LEAD TO socket errno 10048; in which case, switch the sockets being used for the Arduino.
        self.address = (self.host, self.port)
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((self.address))
        self.server.listen(1)
        print "Looking for Client to talk to...."
        self.conn, self.address = self.server.accept()
        output = self.conn.recv(2048)
        print "Message received from client:"
        print output
        self.count = 0

        self.y = pyqtSignal(int)
        self.z = pyqtSignal(int)
        self.u = pyqtSignal(int)
        self.r = pyqtSignal(int)
        self.v = pyqtSignal(int)
        self.count = 0
        super(Server, self).__init__()
        print "FINISHED INITIALIZING"


    def update(self):
        self.count += 1
        try:
            j.update()
            #self.y.emit(readAxis('Y') * -4)

            y = readAxis('Y') * -4
            x = readAxis("X") * -4
            z = readAxis("Z") * -4
            #x_val = random.randint(0, 100)
            #self.x.emit(x_val)
            #self.z.emit(readAxis('Z') * -4)
            #z = readAxis('Z') * -4
            #self.u.emit(readAxis('U') * -4)
            #u = readAxis('U') * -4
            #self.r.emit(readAxis('R') * -4)
            #r = readAxis('R') * -4
            #self.v.emit(readAxis('V') * -4)
            #v = readAxis('Z') * -4
            b0 = readButton(0) #On Rock Candy, corresponds to Button A
            b4 = readButton(4) #On Rock Candy, corresponds to left bumper
            b5 = readButton(5) #On Rock Candy, corresponds to right bumper
            b3 = readButton(3) #on rock candy, Y button
            b8 = readButton(8) #XY-joystick button on Rock Candy Controller

            #Here we doctor the values on the controller
            z = -z  #used to be z = 0, is z = z with xbox controller

            x=-x

            y=-y

            #power budget fix
            #x = x/1.5
            #y = y/1.5
            #z = z/1.5

            sol1 = 0
            sol2 = 0
            if b4: #temporary workaround to the fact Z is retarded on my controller
                z = 100
            elif b5:
                z = -100
            if b8:   # revert to b8
                x = x/2
                y = y/2
            if b0:
                sol1 = 100
            if b3:
                sol2 = 100
            ##
            self.conn.send("{\"X\":%d,\"Y\":%d,\"Z\":%d,\"S1\":%d,\"S2\":%d}~"%(x, y, z, sol1, sol2)) ##HEREIN LIES THE PROBLEM?!
            #self.conn.send("{\X\":0,\"Y\":0,\"Z\":0}~")
            time.sleep(0.1)
            # output = self.conn.recv(204
            # if '#' in output:
            #     raise Exception("LOST MEANINGFUL CONNECTION WITH SERVER.")
        except:
            print "ERROR CAUGHT."
            self.server.listen(1)

            print "RECONNECTING...."
            self.conn, self.address = self.server.accept()
        if self.count % 5 == 0:
            print "PRODUCED VALUES : {\"X\":%d,\"Y\":%d,\"Z\":%d} "%(x, y, z)
            # output = self.conn.recv(2048)
            # print "RECIEVED VALUES: %s" % (output)


if __name__ == '__main__':
    server = Server()
    while True:
        server.update()

