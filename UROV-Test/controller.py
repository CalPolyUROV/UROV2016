__author__ = 'johnathan'

from sfml.window import Joystick

deadZone = 15
minValue = 0
maxValue = 1000

A = 0
B = 1
X = 2
Y = 3
L_TRIGGER = 4
R_TRIGGER = 5
BACK = 6
START = 7
L_JOYSTICK_CLICK = 8
R_JOYSTICK_CLICK = 9
A_HEX = 0x1
B_HEX = 0x2
X_HEX = 0x4
Y_HEX = 0x8
L_TRIGGER_HEX = 0x10
R_TRIGGER_HEX = 0x20
BACK_HEX = 0x40
START_HEX = 0x80
L_JOYSTICK_CLICK_HEX = 0x100
R_JOYSTICK_CLICK_HEX = 0x200


#axis is one of the Joystick.X or Joystick.Y
def getAxis(joyStickNumber, axis):
    size = maxValue - minValue
    return ((applyDeadZone(Joystick.get_axis_position(joyStickNumber, axis))/(100.0-deadZone)) * size) - minValue

def getPrimaryX():
    return getAxis(0,Joystick.X)

def getPrimaryY():
    return getAxis(0,Joystick.Y)

def getSecondaryX():
    return getAxis(0,Joystick.U)

def getSecondaryY():
    return getAxis(0,Joystick.R)

def getTriggers():
    return getAxis(0, Joystick.Z)

def isConnected():
    return Joystick.is_connected(0)

def getButton(button):
    return Joystick.is_button_pressed(0, button)

def getNumButtons():
    return Joystick.get_button_count(0)

def update():
    Joystick.update()

def setDeadZone(value):
    deadZone = value

def applyDeadZone(value):
    negative = False
    if value <= 0:
        negative = True
    temp = abs(value)
    temp -= deadZone
    if temp <= 0:
        temp = 0
    return -temp if negative else temp

