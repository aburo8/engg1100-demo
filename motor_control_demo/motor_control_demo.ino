/*
Arduino IR Motor Control Demonstration
Written by AB
*/
#include <IRremote.hpp>
#include <AFMotor.h>

// Define Hardware Constants & Variables
#define MOTOR_PIN_1 11 // Pin that corresponds to Motor 1
#define MOTOR_PIN_2 3 // Pin that corresponds to Motor 2
#define MOTOR_PIN_3 5 // Pin that corresponds to Motor 3
#define MOTOR_PIN_4 6 // Pin that corresponds to Motor 4
#define SERVO_PIN_1 10
#define SERVO_PIN_2 9
// NOTE: This pin comes from the "datasheet" of my motorshield. If you are using a motorshield check the datasheet and select the appropriate pin.

// Define pins used for the IR Sensor & LED - note we are using the pins exposed on the motor shield.
#define LED_PIN 10
#define IR_SENSOR_PIN 9

// Define the motor object
AF_DCMotor motor(3); // create motor #3, 64KHz pwm (this is handled by the library)

// IR Codes
#define ON_BTN 0x3
#define OFF_BTN 0x2
#define BR_DOWN 0x1
#define BR_UP 0x0

// Speed Controls
int speed = 100; // Speed Variable (max is 255, min 10)
#define SPEED_UP 0
#define SLOW_DOWN 1
#define INCREMENT 10

void setup() {
  // Setup Motor
  motor.setSpeed(0);  // Set the inital motor speed to 0
  motor.run(RELEASE); // Ensure motor is initially released

  // Setup LED
  pinMode(LED_PIN, OUTPUT); // Set LED to output

  // Setup IR Sensor
  IrReceiver.begin(IR_SENSOR_PIN, ENABLE_LED_FEEDBACK); // Start the receiver

  // Setup Serial
  Serial.begin(9600);  // Start the serial communication
}

void loop() {
  // IR Data Processsing
  if (IrReceiver.decode()) {
    // Print out the captured IR Packet
    // IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    // Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
    // IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
  
    // Peripheral Control
    if (IrReceiver.decodedIRData.command == ON_BTN) {
      // Turn on our LED
      digitalWrite(LED_PIN, HIGH);

      // Turn on our motor
      Serial.print("Motor On, Speed: ");
      Serial.println(speed);
      motor.run(FORWARD);
      motor.setSpeed(speed); // 100/255
    } else if (IrReceiver.decodedIRData.command == OFF_BTN) {
      // Turn off our LED
      digitalWrite(LED_PIN, LOW);

      // Turn off our motor
      Serial.println("Motor Off");
      motor.run(RELEASE);
      motor.setSpeed(0);
    } else if (IrReceiver.decodedIRData.command == BR_UP) {
      // Speed up
      Serial.print("Speed Up, Speed: ");
      Serial.println(speed);
      updateMotorSpeed(SPEED_UP);
      motor.run(FORWARD);
      motor.setSpeed(speed);
    } else if (IrReceiver.decodedIRData.command == BR_DOWN) {
      // Slow down
      Serial.print("Slow Down, Speed: ");
      Serial.println(speed);
      updateMotorSpeed(SLOW_DOWN);
      motor.run(FORWARD);
      motor.setSpeed(speed);
    }
    IrReceiver.resume();
  }
}

/*
Updates the motor speed by +/- INCREMENT.
ctrl -> 1 for speeding up, 0 for slowing down.
*/
void updateMotorSpeed(int ctrl) {
  // ctrl is ctrlid
  if (ctrl == SPEED_UP || ctrl == SLOW_DOWN) {
    // Updated the speed variable
    if (ctrl == SPEED_UP && speed >= 10 && speed <= (250 - INCREMENT)) {
      speed = speed + INCREMENT;
    } else if (ctrl == SLOW_DOWN && speed >= (10 + INCREMENT) && speed <= 250) {
      speed = speed - INCREMENT;
    }
  }
}