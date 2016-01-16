# UROV_2016 README
#
##################################
#	Useful Links
##################################
#
# Arduino PWM HOW TO
#	https://www.arduino.cc/en/Tutorial/SecretsOfArduinoPWM
#
# Timer Frequency Charts 
#	https://arduino-info.wikispaces.com/Arduino-PWM-Frequency
#
# 9DOF Tutorial
# https://github.com/ptrbrtz/razor-9dof-ahrs/wiki/Tutorial
#
# TimerOne : Looks good for PWM/Periodic-Call/Call-After-Delay stuff/Call-up-to-X-times-Periodically Stuff I think
# It is driven by Interrupt as opposed to delay! (can be modified to work on other timer0/2/3/4/5) 
# https://github.com/PaulStoffregen/TimerOne
#
#
##################################
# UROV_2016 Progress
#	October 3rd- Made working prototype of rs485 communications working on Santiago
#	November 11th- Wiring diagram in Fritzing has all basic parts except DC DC converter.
#		ESCs are represented by servos because they use PWM; 12 V power to them will be implied for now. 	
#
# Vector Drive!!!
#
#Note: calling delay() in a constructor that is before the void setup will freeze the arduino
#
###BrownOut Ideas Jan16/2016 Sat, Two Ideas
#1)Use a Fractional Constant, with largest slope for x y z r
#   Possibly logrithmic
#2)Have CurrentState of Motor and Input
#   Compare, if difference too high
#     Check Time since last change of CurrentState
#       If too time too low, don't change
#       If passed minimum time margin, change CurrentState by a small amount
#         Therefore speed change is limited to SmallAmount/MinimumTimeMargin
#   Send CurrentState to Motor
#
