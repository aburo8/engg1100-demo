/*
Arduino Motor & Servo Demonstration
Written by AB
*/
#include <Servo.h>

// Motor control pin definitions
int E1 = 10; //enable 1
int M1 = 12; //direction 1
int E2 = 11; //enable 2
int M2 = 13; //direction 2

// Define Hardware Constants & Variables
// MOTORS
#define MOTOR_1 12 // Pin that corresponds to Motor 1
#define ENABLE_M1 10 // Enable pin for Motor 1
#define MOTOR_2 13 // Pin that corresponds to Motor 2
#define ENABLE_M2 11 // Enable pin for Motor 2

// SERVOS
#define SERVO_PIN_1 8 // Pan Servo
#define SERVO_PIN_2 9 // Tilt Servo
Servo panServo;
Servo tiltServo;
float pan = 1500;
float tilt = 1500;

// Button Controls
bool s_A2; // A Button State
bool s_A3; // C Button State

void setup()
{
  // Set digital pins 2-9 to outputs
  for (int pin = 2; pin <= 13; pin++) {
    pinMode(pin, OUTPUT); // Set pin mode to OUTPUT
  }
  pinMode(A3, INPUT_PULLUP);
  panServo.attach(8);
  tiltServo.attach(9);
  Serial.begin(115200);
}

void loop(){
  // Servo Control
  switch (analogRead(A0)) {
    case 0 ... 1:
      pan = pan + 2;
      break;
    case 2 ... 299:
      pan = pan + 0.2;
      break;
    case 300 ... 480:
      pan = pan + 0.1;
      break;
    case 540 ... 748:
      pan = pan - 0.1;
      break;
    case 749 ... 1021:
      pan = pan - 0.2;
      break;
    case 1022 ... 1024:
      pan = pan - 2;
      break;
    default:
      break;
  }
  
  // Check limits & tilt
  if (pan < 500) {
    pan = 500;
  } else if (pan > 2500) {
    pan = 2500;
  }
  panServo.writeMicroseconds(round(pan));

  // read joystick for tilt value
  switch (analogRead(A1)) {
    case 0 ... 1:
      tilt = tilt + 2;
      break;
    case 2 ... 299:
      tilt = tilt + 0.2;
      //delay(2);
      break;
    case 300 ... 480:
      tilt = tilt + 0.1;
      //delay(10);
      break;
    case 540 ... 748:
      tilt = tilt - 0.1;
      //delay(10);
      break;
    case 749 ... 1021:
      tilt = tilt - 0.2;
      //delay(2);
      break;
    case 1022 ... 1024:
      tilt = tilt - 2;
      break;
    default:
      break;
  }

  // Check limits & tilt
  if (tilt < 1000) {
    tilt = 1000;
  } else if (tilt > 2000) {
    tilt = 2000;
  }
  tiltServo.writeMicroseconds(round(tilt));

  // Assign a digital state to A2 and A3 input pins
  if (analogRead(A2) < 250){
    s_A2 = 0;
  } else {
    s_A2 = 1;
  }
  if (analogRead(A3) < 250){
    s_A3 = 0;
  } else {
    s_A3 = 1;
  }

  // Toggle Motors
  // TODO: add comments here
  if (s_A2 == 0 && s_A3 == 0){
    digitalWrite(E2, 1);
    digitalWrite(M2, 0);
    digitalWrite(E1, 0);
    digitalWrite(M1, 0);
  } else if (s_A2 == 1 && s_A3 == 0) {
    digitalWrite(E1, 1);
    digitalWrite(M1, 1);
    digitalWrite(E2, 0);
    digitalWrite(M2, 0);
    Serial.println("1");
  } else if (s_A2 == 0 && s_A3 == 1) {
    digitalWrite(E1, 1);
    digitalWrite(M1, 0);
    digitalWrite(E2, 0);
    digitalWrite(M2, 0);
    Serial.println("2");
  } else {
    digitalWrite(E1, 0);
    digitalWrite(M1, 0);
    digitalWrite(E2, 0);
    digitalWrite(M2, 0);
  }

  // Print Diagnostics to Console
  Serial.print("A0 (Pan):  ");
  Serial.print(analogRead(A0));
  Serial.print("     A1 (Tilt):  ");
  Serial.print(analogRead(A1));
  Serial.print("     A2 (A Btn):  ");
  Serial.print(analogRead(A2));
  Serial.print("     A3 (C Btn):  ");
  Serial.println(analogRead(A3));
}
