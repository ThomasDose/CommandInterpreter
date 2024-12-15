/***********************************************************************************
DRS - robotics for DRS-Kit
UART 

Reads command from Uart
Command : Parameter

e.g.
ON:50 blink LED with interval of 50 ms

(c) Thomas Dose, DRS-robotics DEC 2024

Arduino IDE 
Board Uno
*************************************************************************************/

#include <Arduino.h>
#include "CommandInterpreter.h"

#define BAUD 9600             // Define Baudrate
#define MAXMESSAGELENGTH 256  // Max Message Lenght. Longer Messages will be ignored
#define STANDARDTIME 10

uint8_t _serialData_idx = 0;                       // index for incoming data to write to serialData Bufffer
char _serialData[MAXMESSAGELENGTH];                // serialdata buffer of size MAXMESSAGELENGTH
CommandInterpreter comInt = CommandInterpreter();  // Initialize Command Interpreter Class

const int ledPin = LED_BUILTIN;    // Interne LED-Pin
unsigned long previousMillis = 0;  // Letzter Zeitstempel
unsigned long interval = 0;        // Blinkintervall in Millisekunden
bool blinking = false;             // Status

void ProcessUartIncoming() {
  while (Serial.available())  // when data avaiable on UART 0
  {
    char c = char(Serial.read());                                    // read one byte
    if (c != '\n' && c != '\r') _serialData[_serialData_idx++] = c;  // when byte is not CR or LF append to serial buffer
    if (c == '\n' || _serialData_idx >= MAXMESSAGELENGTH - 1)        // when byte is CR or MAXMESSAGELENGTH is reached Dispatch Command to Command Interpreter
    {
      _serialData[_serialData_idx] = '\0';          // Add end of String
      char *command = strtok(_serialData, ":");     // get command before :
      char *params = strtok(NULL, ":");             // get params after :
      _serialData_idx = 0;                          // reset index for serial buffer
      comInt.DispathCommandEvent(command, params);  // disptach command with params
    }
  }
}
//****************************************************************************************************
void On(CommandEvent *e)  // Callabck for RIGHT Command
{
  interval = (unsigned long)atoi(e->Params);   // get on time from params
  if (interval == 0) interval = STANDARDTIME;  // No parameter given then frequency is 1 second
  blinking = true;                             // set blinking ON
#ifdef DEBUG
  Serial.print("LED ON : interval [ms]= ");  // DEBUG comment
  Serial.println(interval);
#endif
}
//****************************************************************************************************
void Off(CommandEvent *e)  // Callabck for RIGHT Command
{
#ifdef DEBUG
  Serial.println("LED OFF");  // DEBUG comment
#endif
  blinking = false;  // set blinking off
}
//****************************************************************************************************