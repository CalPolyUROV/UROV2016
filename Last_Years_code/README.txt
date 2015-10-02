The following are the operational procedures necessary to get the UROV running
in...SHIP shape. MEEEAAAAAAHHHHH.

First and foremost, the following programs must be installed and functional:
-Python 2.7 
-SFML (the .exe for Windows exists on the SFML site) (found: http://www.sfml-dev.org/download.php)
-PySFML (the .exe for Windows exists on the python-sfml site (found: http://www.python-sfml.org/download.html))
-PyQt4 (the .exe for Windows exists on the PyQt4 site) (found: http://www.riverbankcomputing.com/software/pyqt/download)
-Arduino
 -*To configure the Arduino to run the client code, you MUST do the following:
   --Arduino add library: UROV/PoluluMotor
   --Arduino add library: UROV/Santiago/ArduinoJson-master (this step may not work
	for your computer, in which case you must download the .zip file, extract it 
        anywhere on your computer, and add the folder ArduinoJson-master to the Arduino
	 library. (found: https://github.com/bblanchon/ArduinoJson)


CONFIGURE your ethernet IPV4 address to the following: 211-255-132-121

To UPLOAD the Arduino client-side code, navigate to UROV/Santiago and upload Santiago.ino
to the ARduino.

To RUN the Arduino client-side code, simply make sure the Arduino is recieving power and
is connected via ethernet to the server (typically a laptop, you dingus).

To RUN the Python server-side code, navigate to:
 A.) In the case that the GUI is unnecessary or unoperational, navigate to UROV/PythonServer/UI/main
and run main.py
 B.) If you want to run the GUI and the Python server, assuming the GUI is operational, 
 navigate to UROV/PythonServer and run boilerplate.py


IN the event that the server and the client get disconnected, check the connection,
and if the ethernet is still connected and the connection between server and client isn't
resumed restart the Python server until the connection is fixed. The client program will
constantly search for a connection until one is found.