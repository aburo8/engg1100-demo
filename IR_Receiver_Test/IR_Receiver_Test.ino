/*
Arduino IR Motor Control Demonstration
Written by AB
Based on the following documentation & examples -
https://github.com/Arduino-IRremote/Arduino-IRremote#converting-your-2x-program-to-the-4x-version
*/

#include <IRremote.hpp> // Include the IR Remote Library

int IR_SENSOR_PIN = 9;

void setup()
{
  Serial.begin(9600); // Start Serial Communication
  IrReceiver.begin(IR_SENSOR_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
    IrReceiver.resume(); // Receive the next value
  }
}