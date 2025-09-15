/*
Arduino IR Winch Control Demonstration
Written by AB
*/
#include <IRremote.hpp>
#include <Servo.h>

// Define Hardware Constants & Variables
#define SERVO_PIN_1 9
#define SERVO_PIN_2 10
// NOTE: This pin comes from the "datasheet" of my motorshield. If you are using a motorshield check the datasheet and select the appropriate pin.

// LED Setup
#define LED_PIN 13 // Connect an optional LED to output the system state

// Define pins used for the IR Sensor - note we are using the pins exposed on the motor shield.
#define IR_SENSOR_PIN 10

// Define winch object
// Winches are typically controlled using a PWM speed controller. You can interface with this with the servo library.
// Servo's are controlled using a PWM control signal with an integer value
// If you google "servo" motor, you will usually see an little blue motor with an arm that can rotate between 0-180 degrees.
// A winch uses this same principle, except it rotates 6 times. We will use Servo.writeMicroseconds() to map the servo function to a range between 0-1000.
// If you ever want to use a standard servo motor, just use Servo.write() to map the range between 0-180 degrees.
Servo winch;

// IR Codes - we want to note down the "Command" attribute
#define ONE_BTN 0x45
#define TWO_BTN 0x46
#define UP_BTN 0x18
#define DOWN_BTN 0x52
#define OK_BTN 0x1C

// Controls - these are the position controls for the winch
#define INCREMENT 20
#define STOP 90
#define FULL_RELEASE 180
#define FULL_RETRACT 0
int position = 80;

void setup() {
  // Setup Winch
  winch.attach(SERVO_PIN_1);

  // Setup LED
  pinMode(LED_PIN, OUTPUT); // Set LED to output

  // Setup IR Sensor
  IrReceiver.begin(IR_SENSOR_PIN, ENABLE_LED_FEEDBACK); // Start IR the receiver

  // Setup Serial
  Serial.begin(9600);  // Start the serial communication
}

void loop() {
  // IR Data Processsing
  if (IrReceiver.decode()) {
    // Print out the captured IR Packet - this is for debugging
    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
    IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
  
    // Peripheral Control
    if (IrReceiver.decodedIRData.command == UP_BTN) {
      // WINCH Retract
      if (position > 0 && position <= 180) {
        // Update the position
        position = position - INCREMENT;

        // Retract the winch
        winch.write(position); 

        // Turn on the LED
        digitalWrite(LED_PIN, LOW);
      } else {
        // We can't release the winch
        Serial.println("Cannot RETRACT the winch any further!");
      }

      // Print & Update winch Position
      Serial.print("Winch Position: ");
      Serial.println(position);
    } else if (IrReceiver.decodedIRData.command == DOWN_BTN) {
      // WINCH RELEASE
      if (position >= 0 && position < 180) {
        // Update the position
        position = position + INCREMENT;

        // Release the winch
        winch.write(position); 

        // Turn on the LED
        digitalWrite(LED_PIN, HIGH);
      } else {
        // We can't release the winch
        Serial.println("Cannot RELEASE the winch any further!");
      }

      // Print & Update winch Position
      Serial.print("Winch Position: ");
      Serial.println(position);
    } else if (IrReceiver.decodedIRData.command == OK_BTN) {
      // STOP WINCH
      // Update the position
      position = STOP;

      // Stop the winch
      winch.write(position); 

      // Turn off the LED
      digitalWrite(LED_PIN, LOW);

      // Print & Update winch Position
      Serial.print("Winch STOPPED! Position: ");
      Serial.println(position);
    } else {
      // The user has pressed an unmapped button on the remote
      Serial.println("IR Command Unkown!");
    }

    // Restart the IR receiver so the next packet can be received
    IrReceiver.resume();
  }
}
