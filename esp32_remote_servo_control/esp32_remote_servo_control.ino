/*
Servo & LED Control using an XBOX Controller
Allows you to control the state of an LED and a servo motor using a wireless gamepad controller.

Written by AB - adapted from Bluepad examples
*/
// Include Relevant Librariers
#include <Bluepad32.h> // Install esp32_bluepad with board manager by first opening preferences and adding the following URLs to Additional Board Manager URLs -
// - https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
// - https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json
// For a more in-depth example see Bluepad32_ESP32/Controller example
#include <ESP32Servo.h> // Install using library manager

// Servo & LED Pins
const int LED_PIN = LED_BUILTIN;
const int SERVO_PIN = 4;

// Servo & Controller Objects
ControllerPtr myController = nullptr;
Servo myServo;

// State tracking global variables
int lastServoAngle = 90;
bool lastLedState = false;
int lastAxisX = 0;
unsigned long lastPrintMs = 0;
bool controlOn = false;

// --- Callbacks ---------------------------------------------------------------
// Runs when controller connects
void onConnectedController(ControllerPtr ctl) {
  if (myController == nullptr) {
    myController = ctl;
    Serial.println("Controller connected");
    ControllerProperties properties = ctl->getProperties();
    Serial.printf("BT Addr: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  properties.btaddr[0], properties.btaddr[1], properties.btaddr[2],
                  properties.btaddr[3], properties.btaddr[4], properties.btaddr[5]);
    Serial.printf("VID:PID = %04X:%04X\n",
                  properties.vendor_id, properties.product_id);
  } else {
    Serial.println("Another controller connected, ignoring it");
  }
}

// Runs when controller disconnects
void onDisconnectedController(ControllerPtr ctl) {
  if (myController == ctl) {
    myController = nullptr;
    Serial.println("Controller disconnected");

    digitalWrite(LED_PIN, LOW);
    myServo.write(90);

    lastServoAngle = 90;
    lastLedState = false;
    lastAxisX = 0;
  }
}

// --- Main gamepad processing -------------------------------------------------

void processGamepad(ControllerPtr ctl) {
  // Overall control is operated by the b button
  if (ctl->b()) {
    // One thing to note is we haven't debounced this in this example, see esp32_sensing_and_control example for debouncing
    controlOn = !controlOn;
  }

  // A button controls LED
  bool ledState = ctl->a();

  // Left joystick X axis controls servo
  // Bluepad32 example shows axisX() range is about -511 to 512
  int axisX = ctl->axisX();

  // Small dead zone
  if (abs(axisX) < 25) {
    axisX = 0;
  }

  // we need to map our analog input range to an angle for the servo
  int servoAngle = map(axisX, -511, 512, 0, 180);
  servoAngle = constrain(servoAngle, 0, 180);

  // Write to the servo + toggle LED if control is turned on
  if (controlOn) {
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    myServo.write(servoAngle);
  }

  // Print when values change, or every 200 ms
  unsigned long now = millis();
  if (ledState != lastLedState ||
      servoAngle != lastServoAngle ||
      axisX != lastAxisX ||
      (now - lastPrintMs) > 200) {

    Serial.printf("A=%d, axisX=%d, servo=%d deg\n",
                  ledState ? 1 : 0, axisX, servoAngle);

    lastLedState = ledState;
    lastServoAngle = servoAngle;
    lastAxisX = axisX;
    lastPrintMs = now;
  }
}

// --- Arduino setup / loop ----------------------------------------------------

void setup() {
  // Serial Setup
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("ESP32-C3 Xbox Servo Demo Starting...");

  // LED Setup
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Servo setup
  myServo.setPeriodHertz(50);               // standard servo frequency
  myServo.attach(SERVO_PIN, 500, 2400);     // min/max pulse width
  myServo.write(90);                        // centre position

  // Bluepad32 setup (library for controller interface)
  BP32.setup(&onConnectedController, &onDisconnectedController);
  Serial.println("Put the Xbox controller into pairing mode.");
  Serial.println("Waiting for controller...");
}

void loop() {
  // Must be called repeatedly
  BP32.update();

  if (myController && myController->isConnected() && myController->isGamepad()) {
    processGamepad(myController);
  }

  delay(20);
}