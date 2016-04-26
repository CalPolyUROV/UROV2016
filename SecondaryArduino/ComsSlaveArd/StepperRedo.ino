
//#define SMPIN_DIR 13
////Connect to driver DIR pin
//
//#define SMPIN_MICRO 12
////To driver MS1 MS2 MS3 pins (all of them!)
//
//#define SMPIN_STEP 11
////To driver DIR pin
////uses Timer 2
//
////Timer 2 has default 30Hz; 30/16 steps/second; 200 steps/rotation; = 3.375 degrees/second
//
////Use with this driver http://howtomechatronics.com/tutorials/arduino/how-to-control-stepper-motor-with-a4988-driver-and-arduino/
//
//#define SM_CW 1
//#define SM_CCW 0

int SM_segmentsToGo = 0;

void setupSM(){
  setupSMmisc();
  setupSMinterrupt();
}

void setupSMmisc(){
  pinMode(SMPIN_MICRO, OUTPUT);
  pinMode(SMPIN_DIR, OUTPUT);
}

void setupSMinterrupt(){
  cli();                  //stop interrupts
  TCCR2A = 0;             // set entire TCCR1A register to 0
             //I have no idea what this bit does yet
  TCCR2B = 0;             // same for TCCR1B
             //I have no idea what this bit does yet, but it is similar to TCCR1A

  TCNT2 = 0; //This is the counter register. clearing it now

  OCR2A = 255; //This is what the timer counts to. When reach, sets interrupt flag and resets TCNT1 to 0
    //At counter 8192 Hz counter, interrupt is 30Hz

  TCCR2B |= (1 << WGM12); //CTC mode. means when reach, set flag.

  TCCR2B = TCCR2B & B11111000 | B00000111; // set timer 2 freq 
                                           // counter of 8MHZ/1024 = 8192
                                            //PWM of 30.64 (prescaler 1024)
  TIMSK2 &= 0b11111101;// disable timer compare interrupt

}

void startSM(int segtogo, int dir){
  analogWrite(SMPIN_STEP, 127); //30Hz, 50% to step pin
  setSMDIR(dir); //Set direction
  SM_segmentsToGo = segtogo;
  
  TIMSK2 |= (1 << OCIE1A);// enable timer compare interrupt
       //|=  0b00000010;
       // Set Interrupt when Compare A flag set
}

void stopSM(){
  TIMSK2 &= 0b11111101;// disable timer compare interrupt
       //|=  0b00000010;
  SM_segmentsToGo = 0;
  digitalWrite(SMPIN_STEP, LOW);
}

//
//Set the direction
void setSMDIR(int direction){
  if(direction == SM_CW){
    digitalWrite(SMPIN_DIR, HIGH);
  } else {
    digitalWrite(SMPIN_DIR, LOW);
  }
}

ISR(TIMER2_COMPA_vect){ 
  SM_segmentsToGo -= 1;
  if(SM_segmentsToGo <=0){
    stopSM();
  } 
  
}


