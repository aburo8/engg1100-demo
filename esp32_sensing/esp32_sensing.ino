/*
LED Control + Sensing Example
Utilises an ambient light sensor to control the state of an LED.
Utilises serial communication to print the state of a temperature sensor to console on button click. 

Written by AB
*/
// Setup Libraries & Definitions
#include <Wire.h>
#include <Adafruit_TMP117.h>
#include <Adafruit_Sensor.h>
#include "SparkFun_VEML6030_Ambient_Light_Sensor.h"
#define AL_ADDR 0x10

// Initialise Sensors
SparkFun_Ambient_Light light(AL_ADDR);
Adafruit_TMP117  tmp117;

// Setup Global Variables to track program state
const int BTN = 2; // Indicates the button connection pin
const int LED = 1; // Indicates the LED pin (you can also use LED_BUILTIN for the ESP32 onboard LED)
bool ledState = LOW; // LED on/off state

// Button Debouncing Variables
int stable = LOW, lastRaw = LOW;
unsigned long tChange = 0;
const unsigned long debounceMs = 30;

// Light Sensor Raw Reading
long luxVal = 0;

void setup() {
  // Setup Serial + I2C Communication
  Serial.begin(115200);
  Wire.setPins(5, 6);
  Wire.begin();

  // Setup Button
  pinMode(BTN, INPUT);   // external 10k pulldown required
  pinMode(LED, OUTPUT);

  // Setup light sensor
  if(light.begin())
    Serial.println("Ready to sense some light!"); 
  else
    Serial.println("Could not communicate with the sensor!");

  // The gain and integration times determine the resolution of the lux
  // value, and give different ranges of possible light readings. Check out
  // hoookup guide for more info. 
  light.setGain(.125);
  light.setIntegTime(100);
  Serial.println("Reading settings..."); 
  Serial.print("Gain: ");
  float gainVal = light.readGain();
  Serial.print(gainVal, 3); 
  Serial.print(" Integration Time: ");
  int timeVal = light.readIntegTime();
  Serial.println(timeVal);

  // Initialise the temp sensor
  if (!tmp117.begin(0x48, &Wire, 117)) {
    Serial.println("Failed to find TMP117 chip");
    while (1) { delay(10); }
  }
  Serial.println("TMP117 Found!");
}

void loop() {
  // Fetch light sensor reading and update LED state
  luxVal = light.readLight();
  if (luxVal < 100) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }

  // Write state to LED
  digitalWrite(LED, ledState);

  // Read button press with debouncing
  int raw = digitalRead(BTN);
  if (raw != lastRaw) {
    tChange = millis(); 
    lastRaw = raw;
  }
  if (millis() - tChange > debounceMs && raw != stable) {
    if (raw == HIGH) {
      // New button press detected, so print sensor data
      printSensors();
    }
    stable = raw; // Save the current button state
  }
}

void printSensors() {
  sensors_event_t temp; // create an empty temp event to be filled
  tmp117.getEvent(&temp); //fill the empty event object with the current measurements
  Serial.print("Ambient Light Reading: ");
  Serial.print(luxVal);
  Serial.print(" Lux"); 
  Serial.print("Temperature  "); 
  Serial.print(temp.temperature);Serial.print(" degrees C");
  Serial.println("");
}
