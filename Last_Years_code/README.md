# UROV
The robot will be controlled through two main processes: A python server that processes input from a joystick, and an Arduino sketch which takes commands from the python server and controls the motors.

##Python Server
Using pySFML we read inputs from a logitech game controller, format this into a JSON string, and send this string over ethernet. 

##Arduino Sketch ("Santiago")
Santiago reads in the string, parses it using the ArduinoJSON library, and assigns appropriate values to each of the motors.
