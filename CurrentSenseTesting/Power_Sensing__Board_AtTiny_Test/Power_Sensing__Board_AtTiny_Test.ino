/*!
Linear Technology DC682A Demonstration Board.
LTC1859: 16-Bit, 8-Channel 100ksps SAR ADC with SPI Interface.

@verbatim

NOTES
  Setup:
   Set the terminal baud rate to 115200 and select the newline terminator.
   Equipment required is a precision voltage source (null box) and a precision voltmeter (to monitor voltage source).
   No external power supply is required.
   Ensure JP1 is installed in the default position from the factory.

  How to test Single-Ended mode:
   Bipolar Mode:
     The voltage source should be connected to the channel under test. The negative lead of the voltage source
     must be connected to the GND pin in order to provide a ground-referenced voltage. Ensure voltage is within the
     range of -5V to +5V for low range mode, and -10V to +10V for high range mode.

   Unipolar Mode:
     The voltage source should be connected to the channel under test. The negative lead of the voltage source
     must be connected to the GND pin in order to provide a ground-referenced voltage. Ensure voltage is within the
     range of 0 to +5V for low range mode, and 0 to +10V for high range mode.

  How to test Differential Mode:
   Bipolar Mode:
     The voltage source should be connected with positive and negative leads to paired channels. The negative lead of the voltage source
     must also be connected to the GND pin in order to provide a ground-referenced voltage. Ensure the differential voltage is within the
     range of -5V to +5V for low range mode, and -10V to +10V for high range mode. Swapping input voltages results in a reversed polarity reading.

   Unipolar Mode:
     The voltage source should be connected with positive and negative leads to paired channels. The negative lead of the voltage source
     must also be connected to the GND pin in order to provide a ground-referenced voltage. Ensure the differential voltage is within the
     range of 0V to +5V for low range mode, and 0V to +10V for high range mode. Swapping input voltages results in a reversed polarity reading.

USER INPUT DATA FORMAT:
 decimal : 1024
 hex     : 0x400
 octal   : 02000  (leading 0 "zero")
 binary  : B10000000000
 float   : 1024.0

@endverbatim

http://www.linear.com/product/LTC1859

http://www.linear.com/product/LTC1859#demoboards

REVISION HISTORY
$Revision: 1792 $
$Date: 2013-08-9 13:58:53 -0700 (Thu, 25 Jul 2013) $

Copyright (c) 2013, Linear Technology Corp.(LTC)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of Linear Technology Corp.

The Linear Technology Linduino is not affiliated with the official Arduino team.
However, the Linduino is only possible because of the Arduino team's commitment
to the open-source community.  Please, visit http://www.arduino.cc and
http://store.arduino.cc , and consider a purchase that will help fund their
ongoing work.
*/

/*! @file
    @ingroup LTC1859
*/

#include <Arduino.h>
#include <stdint.h>
#include <SoftwareSerial.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Linduino.h"
//#include "LT_SPI.h"
#include "UserInterface.h"
#include "LTC1859.h"
//#include <SPI.h>
#include <Wire.h>


// Function Declaration
void print_title();                                     // Print the title block
void print_prompt();                                    // Prompt the user for an input command
uint8_t print_user_command_differential();             // Display selected differential channels
uint8_t print_user_command_single_ended();             // Display selected single ended channels
void print_channel_selection(uint8_t menu);

void menu_1_read_input();                             // Read channels
void menu_2_select_single_ended_differential();       // Sets LTC1859 to Single-Ended or Differential
void menu_3_select_uni_bipolar();                       // Sets LTC1859 to Bipolar or Unipolar
void menu_4_select_range();                       // Sets LTC1859 to high or low input range
void menu_5_sleep();                                  

// Global variables
static uint8_t uni_bipolar = LTC1859_UNIPOLAR_MODE;    //!< Default set for unipolar mode
static uint8_t single_ended_differential = LTC1859_SINGLE_ENDED_MODE;    //!< LTC1859 Unipolar or Bipolar mode selection
static uint8_t range_low_high = LTC1859_HIGH_RANGE_MODE;   //!< Default set for high range mode
static float LTC1859_bits = 16;                      //!< Resolution (16 bits)
static float LTC1859_vref = 10; 

// Constants
//! Lookup table to build the command for single-ended mode, input with respect to GND
const uint8_t BUILD_COMMAND_SINGLE_ENDED[8] = {LTC1859_CH0, LTC1859_CH1, LTC1859_CH2, LTC1859_CH3,
    LTC1859_CH4, LTC1859_CH5, LTC1859_CH6, LTC1859_CH7
                                              }; //!< Builds the command for single-ended mode, input with respect to GND

//! Lookup table to build the command for differential mode with the selected uni/bipolar mode
const uint8_t BUILD_COMMAND_DIFF[8] = {LTC1859_P0_N1, LTC1859_P2_N3, LTC1859_P4_N5, LTC1859_P6_N7,
                                       LTC1859_P1_N0, LTC1859_P3_N2, LTC1859_P5_N4, LTC1859_P7_N6
                                      }; //!< Build the command for differential mode


//! Initialize Linduino
void setup()
{
  SoftwareSerial mySerial(2, 3); // RX, TX
  mySerial.begin(115200);          // Initialize the mySerial port to the PC
  uint16_t adc_code; 
  
//  quikeval_SPI_init();           // Configure the spi port for 4MHz SCK
//  quikeval_SPI_connect();        // Connect SPI to main data port
  mySerial.println("Hello, world?");
  print_title();
  print_prompt();
}

//! Repeats Linduino loop
void loop()
{
  uint16_t user_command;

  if (mySerial.available())             // Check for user input
  {
      user_command = read_int();        // Read the user command
      if (user_command != 'm')
        mySerial.println(user_command);   // Prints the user command to com port
      mySerial.flush();
      switch (user_command)
      {
        case 1:
          menu_1_read_input();
          break;
        case 2:
          menu_2_select_single_ended_differential();
          break;
        case 3:
          menu_3_select_uni_bipolar();
          break;
        case 4:
          menu_4_select_range();
          break;
        case 5:
          menu_5_sleep();
          break;
        default:
          mySerial.println(F("Invalid Option"));
          break;
      }
      mySerial.println();
      mySerial.println(F("*************************"));
      print_prompt();
  }
}


// Function Definitions
//! Prints the title block when program first starts.
void print_title()
{
  mySerial.println();
  mySerial.println(F("*****************************************************************"));
  mySerial.println(F("* DC682A Demonstration Program                                  *"));
  mySerial.println(F("*                                                               *"));
  mySerial.println(F("* This program demonstrates how to send data and receive data   *"));
  mySerial.println(F("* from the LTC1859 16-bit ADC.                                  *"));
  mySerial.println(F("*                                                               *"));
  mySerial.println(F("* Set the baud rate to 115200 and select the newline terminator.*"));
  mySerial.println(F("*                                                               *"));
  mySerial.println(F("*****************************************************************"));
}


//! Prints main menu.
void print_prompt()
{
  mySerial.println(F("1-Read ADC Input "));
  mySerial.println(F("2-Select Single-Ended / Differential measurement (default is Single_Ended)"));
  mySerial.println(F("3-Select Unipolar / Bipolar measurement (default is Unipolar)"));
  mySerial.println(F("4-Set Input Range (default is High Range)"));
  mySerial.println(F("5-Select Sleep Mode"));
  mySerial.println();
  mySerial.print(F("Enter a command:  "));
}


//! Display selected differential channels. Displaying single-ended channels is
//! straightforward; not so with differential because the inputs can take either polarity.
uint8_t print_user_command_differential()
{
  uint8_t user_command;

  mySerial.println(F("*************************"));
  mySerial.println(F("  0 = 0P-1N"));
  mySerial.println(F("  1 = 2P-3N"));
  mySerial.println(F("  2 = 4P-5N"));
  mySerial.println(F("  3 = 6P-7N"));
  mySerial.println(F("  4 = 1P-0N"));
  mySerial.println(F("  5 = 3P-2N"));
  mySerial.println(F("  6 = 5P_4N"));
  mySerial.println(F("  7 = 7P = 6N"));
  mySerial.println(F("  8 = ALL Even_P-Odd_N"));
  mySerial.println(F("  m = Main Menu"));
  mySerial.println();
  mySerial.print(F("  Enter a Command: "));
    
  user_command = read_int();  // Read the menu command    
  mySerial.println(user_command);
  if (user_command == 'm')
    return(0);
    
  switch (user_command)  //check for invalid selection
  {
    case 0:
      mySerial.println(F("  0P-1N selected"));
      break;
    case 1:
      mySerial.println(F("  2P-3N selected"));
      break;
    case 2:
      mySerial.println(F("  4P-5N selected"));
      break;
    case 3:
      mySerial.println(F("  6P-7N selected"));
      break;
    case 4:
      mySerial.println(F("  1P-0N selected"));
      break;
    case 5:
      mySerial.println(F("  3P-2N selected"));
      break;
    case 6:
      mySerial.println(F("  5P-4N selected"));
      break;
    case 7:
      mySerial.println(F("  7P-6N selected"));
      break;
    case 8:
      mySerial.println(F("  ALL Even_P-Odd_N selected"));
      break;
    default:
      mySerial.println(F("  Invalid Option"));
      break;
   }
  return(user_command);
}


//! Display selected differential channels. Displaying single-ended channels is
//! straightforward; not so with differential because the inputs can take either polarity.
void print_channel_selection(uint8_t menu)
{
  switch (menu)
  {
    case 0:
      mySerial.print(F(" 0P-1N:"));
      break;
    case 1:
      mySerial.print(F(" 2P-3N:"));
      break;
    case 2:
      mySerial.print(F(" 4P-5N:"));
      break;
    case 3:
      mySerial.print(F(" 6P-7N:"));
      break;
    case 4:
      mySerial.print(F(" 1P-0N:"));
      break;
    case 5:
      mySerial.print(F(" 3P-2N:"));
      break;
    case 6:
      mySerial.print(F(" 5P-4N:"));
      break;
    case 7:
      mySerial.print(F(" 7P-6N:"));
      break;
  }
}


//! Display selected single-ended channel.
uint8_t print_user_command_single_ended()
{
  uint8_t user_command;
  
  mySerial.println(F("*************************"));                         
  mySerial.println(F("  0 = CH0"));
  mySerial.println(F("  1 = CH1"));
  mySerial.println(F("  2 = CH2"));
  mySerial.println(F("  3 = CH3"));
  mySerial.println(F("  4 = CH4"));
  mySerial.println(F("  5 = CH5"));
  mySerial.println(F("  6 = CH6"));
  mySerial.println(F("  7 = CH7"));
  mySerial.println(F("  8 = ALL"));
  mySerial.println(F("  m = Main Menu"));
  mySerial.println();
  mySerial.print(F("  Enter a Command: "));

  user_command = read_int();  // Read the single-ended menu command
  mySerial.println(user_command);
  if (user_command == 'm')
    return(0);
      
  switch (user_command)  //check for invalid selection
  {
    case 0:
      mySerial.println(F("  CH0 selected"));
      break;
    case 1:
      mySerial.println(F("  CH1 selected"));
      break;
    case 2:
      mySerial.println(F("  CH2 selected"));
      break;
    case 3:
      mySerial.println(F("  CH3 selected"));
      break;
    case 4:
      mySerial.println(F("  CH4 selected"));
      break;
    case 5:
      mySerial.println(F("  CH5 selected"));
      break;
    case 6:
      mySerial.println(F("  CH6 selected"));
      break;
    case 7:
      mySerial.println(F("  CH7 selected"));
      break;
    case 8:
      mySerial.println(F("  All selected"));
      break;
    default:
      mySerial.println(F("  Invalid Option"));
      break;
   }

  return(user_command);
}


//! Read channels
//! @return 1 if successful, 0 if not
void menu_1_read_input()
{
  uint8_t user_command;
  uint16_t adc_command;         // The LTC1859 command byte    
  uint16_t adc_code = 0;    // The LTC1859 code
  uint8_t x, y, startcount, endcount;
  float adc_voltage;
  
  if (uni_bipolar == LTC1859_UNIPOLAR_MODE)
  {
    if (single_ended_differential == LTC1859_SINGLE_ENDED_MODE)
    {
    mySerial.println(F("  Read Input in Single-Ended, Unipolar mode:"));
    mySerial.println(F("  Note that in Unipolar mode, input voltages less than zero are reported as 0.0V"));
    user_command = print_user_command_single_ended();
    }
    else
    {
    mySerial.println(F("  Read Input in Differential, Unipolar mode:"));
    mySerial.println(F("  Note that in Unipolar mode, input voltages less than zero are reported as 0.0V"));
    user_command = print_user_command_differential();
    }    
  }
  else
  {
    if (single_ended_differential == LTC1859_SINGLE_ENDED_MODE)
    {
    mySerial.println(F("  Read Input in Single-Ended, Bipolar mode:"));
    user_command = print_user_command_single_ended();
    }
    else
    {
    mySerial.println(F("  Read Input in Differential, Bipolar mode:"));
    user_command = print_user_command_differential();
    }    
  }

  if (user_command == 8)  //read all channels
  {
    startcount = 0;
    endcount = 7;
  }
  else 
  {
    startcount = user_command;
    endcount = user_command;
  }
   
  if(single_ended_differential == LTC1859_SINGLE_ENDED_MODE)  //read single-ended
  {
      adc_command = BUILD_COMMAND_SINGLE_ENDED[0] | uni_bipolar | range_low_high;
      LTC1859_read(LTC1859_CS, adc_command, &adc_code);     // Throws out last reading and starts CH0 conversion
      for (x = startcount; x <= endcount; x++)
      {
            adc_command = BUILD_COMMAND_SINGLE_ENDED[x % 8] | uni_bipolar | range_low_high; // Send channel config for the NEXT conversion to take place
            LTC1859_read(LTC1859_CS, adc_command, &adc_code);   // Read previous channel conversion (x-1) and start next one (x)
            LTC1859_read(LTC1859_CS, adc_command, &adc_code);   // Read previous channel conversion (x-1) and start next one (x)
            mySerial.print(F("  Received Code: b"));
            mySerial.println(adc_code, BIN);
            
            adc_voltage = LTC1859_code_to_voltage(adc_code, LTC1859_vref, range_low_high, uni_bipolar);
            mySerial.print(F("  Voltage read on "));
            mySerial.print(F("Ch"));
            mySerial.print(x);
            mySerial.print(F(": "));
            mySerial.print(adc_voltage, 4);
            mySerial.println(F("V"));
            mySerial.println();
      }
  }

  else  //read differential
  {
      adc_command = BUILD_COMMAND_DIFF[0] | uni_bipolar | range_low_high;
      LTC1859_read(LTC1859_CS, adc_command, &adc_code);     // Throws out last reading and starts CH0 conversion
      for (x = startcount; x <= endcount; x++)
      {
            adc_command = BUILD_COMMAND_DIFF[x % 8] | uni_bipolar | range_low_high; // Send channel config for the NEXT conversion to take place
            LTC1859_read(LTC1859_CS, adc_command, &adc_code);   // Read previous channel conversion (x-1) and start next one (x)
            LTC1859_read(LTC1859_CS, adc_command, &adc_code);   // Read previous channel conversion (x-1) and start next one (x)
            mySerial.print(F("  Received Code: b"));
            mySerial.println(adc_code,BIN);

            adc_voltage = LTC1859_code_to_voltage(adc_code, LTC1859_vref, range_low_high, uni_bipolar);
            mySerial.print(F("  Voltage read between Chs "));
            print_channel_selection(x + y);
            mySerial.print(adc_voltage, 4);
            mySerial.println(F("V"));
            mySerial.println();
      }
  }
}


//! Sets LTC1859 to Single-Ended or Differential
void menu_2_select_single_ended_differential()
{
  uint8_t user_command;

  mySerial.println(F("\n  0 = Single-Ended"));
  mySerial.println(F("  1 = Differential"));
  mySerial.print(F("  Enter a Command: "));

  user_command = read_int();    // Read user input for uni_bipolar 
  mySerial.println(user_command);
  switch (user_command)
      {
        case 0:
          mySerial.println(F("  Single-Ended mode selected"));
          single_ended_differential = LTC1859_SINGLE_ENDED_MODE;
        break;
        case 1:
          mySerial.println(F("  Differential mode selected"));
          single_ended_differential = LTC1859_DIFFERENTIAL_MODE;
          break; 
        default:
        {
          mySerial.println("  Invalid Option");
          return;
        }
          break;
      }    
}


//! Select unipolar (0-REFCOMP) or bipolar (+/- 0.5 x REFCOMP) mode
//! @return void
void menu_3_select_uni_bipolar()
{
  uint8_t user_command;
  
  mySerial.println(F("\n  0 = Unipolar"));
  mySerial.println(F("  1 = Bipolar"));
  mySerial.print(F("  Enter a Command: "));

  user_command = read_int();    // Read user input for uni_bipolar 
  mySerial.println(user_command);
  switch (user_command)
      {
        case 0:
          mySerial.println(F("  Unipolar mode selected"));
          uni_bipolar = LTC1859_UNIPOLAR_MODE;
        break;
        case 1:
          mySerial.println(F("  Bipolar mode selected"));
          uni_bipolar = LTC1859_BIPOLAR_MODE;
          break; 
        default:
          mySerial.println("  Invalid Option");
          return;
          break;
      }    
}


//! Select low range or high range mode
//! @return void
void menu_4_select_range()
{
  uint8_t user_command;
  
  mySerial.println(F("\n  0 = High Range"));
  mySerial.println(F("  1 = Low Range"));
  mySerial.print(F("  Enter a Command: "));
  user_command = read_int();    // Read user input for range select
  mySerial.println(user_command);

  switch (user_command)
    {
        case 0:
          mySerial.println(F("  High Range selected"));
          range_low_high = LTC1859_HIGH_RANGE_MODE;
          break;
        case 1:
          mySerial.println(F("  Low Range selected"));
          range_low_high = LTC1859_LOW_RANGE_MODE;
          break;
        default:
        {
          mySerial.println("  Invalid Option");
          return;
        }
          break;
    }
   }


//! Put LTC1859 to sleep (low power)
//! @return void
void menu_5_sleep()
{
  // Sleep Mode
  uint16_t user_command;
  uint16_t adc_code = 0;                                        // The LTC1859 code
  LTC1859_read(LTC1859_CS, LTC1859_SLEEP_MODE, &adc_code);      // Build ADC command for sleep mode
/*  
 *   
  mySerial.println();
  mySerial.print(F("  ADC Command: B"));
  mySerial.println(LTC1859_SLEEP_MODE, BIN);
  mySerial.println(F("  LTC1859 Is Now In Sleep Mode"));
  mySerial.println(F("  Enter RETURN to exit Sleep Mode"));
  */
  user_command = read_int();
  LTC1859_read(LTC1859_CS, LTC1859_NORMAL_MODE, &adc_code); // Exit Sleep Mode
}
