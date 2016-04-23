#include "ComsSlaveDeclares.h"//moving stuff out of the way?

void setup() {
  Wire.begin(8);                // join i2c bus with address #8

  //Gyro.accelSetup();
  //Gyro.updateAccelRaw();
  // Pressure Requests
  Wire.onReceive(receiveEvent); //Info is received
  Wire.onRequest(requestEvent); //Info is Requested
  Serial.begin(9600);
  old001setup();
}

void loop() {
  delay(20);
  Pressure.updatePressureSensor();
  //yprGet();
  //Serial.println(yaw);
  old001loop(); //not sure but this gives the data
}

void receiveEvent(int howMany) {
  receivedString = "";//Clear recieved string
  
  if(Wire.available()){  
    WireMosiType = Wire.read(); //Take 1 char, data type.
      while (Wire.available()) { 
        tempReceive = Wire.read(); //Receive 5 chars, data
        receivedString += tempReceive;
    }
  }
  
  WireEventCode = receivedString.toInt(); //Turn received into an int
  if(WireMosiType = 'c'){                 //treat as command if command type
    WireNextSendData = WireCallEvent(WireEventCode);
  } else if(WireMosiType = 'p') {          //store as parameter if param type
    for(short i=0; i<COMSPARAMSTACKSIZE-1; i++){
      ParameterStack[i] = ParameterStack[i+1];
    }
    ParameterStack[COMSPARAMSTACKSIZE-1] = WireEventCode;
  }
  switch(WireMosiType) {
    case COMMANDCHAR :
      WireNextSendData = WireCallEvent(WireEventCode);
      break;
    case SLAVEPRM0 :
      SlaveParameters[0] = WireEventCode;
      break;
    case SLAVEPRM1 :
      SlaveParameters[1] = WireEventCode;
      break;
    case SLAVEPRM2 :
      SlaveParameters[2] = WireEventCode;
      break;
    case SLAVEPRM3 :
      SlaveParameters[3] = WireEventCode;
      break;
    case SLAVESTACK :
      for(short i=0; i<COMSPARAMSTACKSIZE-1; i++){
        ParameterStack[i] = ParameterStack[i+1];
      }
      ParameterStack[COMSPARAMSTACKSIZE-1] = WireEventCode;
      break;
    default:
      break;
  }
}


int WireCallEvent (int EventCode){
  switch(EventCode) {
    case GET_TEMP:
      WireMisoType = 'i'; //misoType is kinda pointless, its just a buffer so the right number of chars are returned on i2c. 
                          //I can't think of any way to use it either; when master makes a request it already knows what it should be recieving.
      return Pressure.getTempTimesTen();  //Its not temp times ten anymore, its just temp. to be changed.
      break;
    case GET_PRES:
      WireMisoType = 'i';
      return Pressure.getPressure();
      break;
    case GET_DEPT:
      WireMisoType = 'i';
      return Pressure.getDepth();
      break;
    case GET_YAW:
      WireMisoType = 'f';
      return (int)yawDEG;
      break;
    case GET_PCH:
      WireMisoType = 'f';
      return (int)pchDEG;
      break;
    case GET_ROL:
      WireMisoType = 'f';
      return (int)rolDEG;
      break;
    case START_SMCW:
      WireMisoType = 'n';//no return
      startSM(16,SM_CW);//1.8 degrees rotate CW
      return 777;
      break;
    case START_SMCCW:
      WireMisoType = 'n';//no return
      startSM(16,SM_CCW);//1.8 degrees rotate CCW
      return 777;
      break;
    case STOP_SM:
      WireMisoType = 'n';
      stopSM();
      return 777;
      break;
    case ARB_SM:
      WireMisoType = 'n';
      startSM(SlaveParameters[0],SlaveParameters[0]); //top of array is direction, second is number microsteps
      return 777;
      break;
    case STK_SM:
      WireMisoType = 'n';
      startSM(ParameterStack[COMSPARAMSTACKSIZE-2],ParameterStack[COMSPARAMSTACKSIZE-1]); //top of array is direction, second is number microsteps
      return 777;
      break;
    default:
      WireMisoType = 'n';
      return 1337;        //You'll know something is wrong if you see this 1337
    break;
  }
  
}

void requestEvent() {
  WireSendString = WireMisoType + String(WireNextSendData); //padding the string with the misoType
  Wire.write(WireSendString.c_str());

}



//////////////Janky Include//////


