/***********************************************************************************
DRS - robotics for DRS-Kit
Demo-Code for CommandInterpreter
INPUT ON - LED blinking is on with optional parameter ( ON:50 blinking with interval 50 ms)
INPUT OFF - LED is off

(c) Thomas Dose, DRS-robotics DEC 2024

Arduino IDE 
Board Uno
*************************************************************************************/

#define DEBUG                                             //uncomment for debug mode

#include "Uart.hpp"                                       // UART control

//************************************************************************************

void setup() {
  pinMode(ledPin, OUTPUT);                                // define pin 13 as output (LED)
  Serial.begin(BAUD);                                     // Start Serial Communiation UART: 0 Baud: 9600 Parity: None Data: 8  Stop: 1
  delay(500);                                             // wait for connection
#ifdef DEBUG
  Serial.println("Start LED-Program");                    // Promt serial
#endif
  comInt.RegisterCommandEvent(On, "ON");                  // Register Callback for RIGHT Command
  comInt.RegisterCommandEvent(Off, "OFF");                // Register Callback for LEFT Command
}
//************************************************************************************

void loop() {
  ProcessUartIncoming();                                  // Check UART 0 for incoming Bytes
  if (blinking) {                                         // Wenn wir noch blinken sollen
    unsigned long currentMillis = millis();               // Aktuelle Zeit abrufen                                     
    if (currentMillis - previousMillis >= interval) {     // Prüfen, ob es Zeit ist, den LED-Status zu ändern
      previousMillis = currentMillis;                     // Zeitstempel aktualisieren
      int ledState = digitalRead(ledPin);                 // LED-Status umschalten
      digitalWrite(ledPin, !ledState);                    // LED schalten
    }
  } else {
     digitalWrite(ledPin, LOW);                           // LED ausschalten
  }
}
