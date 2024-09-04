/*
Arduino IR Motor Control Demonstration
Written by AB
*/

/* There are two main types of motors that you might need to use
1. Servo Motor
  - These are motors which rotate an arm between 0-180 degrees (sometimes 0-360). These can be controlled using the built-in Arduino Servo library.
2. DC Motor
  - These are simple motors. They have 2-3 terminals (depending on the motor). Usually, hobby DC motors have a +ve & -ve terminal, and you change the speed by varying
   "duty cycle" of the +ve pin signal.
In this demo I will show you how to control both a servo and a DC Motor
*/

/*
What goes here?
At the top section of the code you put any 'global' variables - things that you need to access in any of the other functions (i.e. setup & loop)
*/
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
  motor.run(FORWARD); // Run the motor forward
  motor.setSpeed(100);
  digitalWrite(LED_PIN, HIGH); // Turn the LED on
  delay(2000); // Wait for 2 seconds

  motor.setSpeed(0);
  motor.run(RELEASE); // Stop the motor
  digitalWrite(LED_PIN, LOW); // Turn the LED off
  delay(2000); // Wait for 2 seconds
}
