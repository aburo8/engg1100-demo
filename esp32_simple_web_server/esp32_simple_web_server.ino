/*
Simple Web Server program running on ESP32 
Configures a simple route and responds with content

Written by AB - Based on ESP32 Examples
*/
// Include relevant libraries
#include <WiFi.h>
#include <NetworkClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>


// Configure your WiFi credentials so the ESP32 can connect
const char *ssid = "MY_NETWORK";
const char *password = "MY_NETWORK_PASSWORD";
char sendBuffer[100]; // A 100 character buffer for sending responses

// Web Server Object
WebServer server(80);

// OPTIONAL - LED pin (flashes to show processing state)
const int led = 10;

// A handler for the '/' root route. Toggles LED and returns some text content.
void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}

// An example handler which returns text based content
void handleNumber() {
  long myNumber = 312;
  digitalWrite(led, 1);
  server.send(200, "text/plain", String(myNumber));
  digitalWrite(led, 0);
}

// A handler for unknown requests
void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  // Configure LED
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  
  // Configure serial
  Serial.begin(115200);

  // Attempt to connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to network");

  // Wait for connection + Print loading indicator/connection status to serial
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup webserver
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);

  // Start webserver
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  // Hanlde webserver requests
  server.handleClient();
  delay(2);  // allow the cpu to switch to other tasks
}
