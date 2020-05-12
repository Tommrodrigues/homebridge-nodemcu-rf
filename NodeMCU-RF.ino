#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <RCSwitch.h>

// GitHub Page = https://github.com/Tommrodrigues/homebridge-nodemcu-rf

// D3 = Transmitter Data Pin
// VIN = Transmitter VCC (Power) pin
// GND = Transmitter Ground

/////////////////// CHANGE THESE VALUES //////////////////////
const char* ssid = "SSID"; //Name of your network
const char* password = "PASSWORD"; //Password for your network
const char* mdns = "rf"; //mDNS name
//////////////////////////////////////////////////////////////

int rfCode, rfPulse;

const int repeatNumber = 7; //Number of "Codesends". (Leave it at 7 for default)

RCSwitch mySwitch = RCSwitch();
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  mySwitch.enableTransmit(0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.println("Connecting to \"" + String(ssid) + "\"");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(String(++i) + " ");
  }
  Serial.println();
  Serial.println("Connected successfully");

  // Print the IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin(mdns)) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS address: " + String(mdns) + ".local");

  server.on("/setState", []() {
    rfCode = server.arg("code").toInt();
    rfPulse = server.arg("pulse").toInt();

    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(rfPulse);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(rfCode, 24);

    server.send(200);
  });

  // Start the server
  server.begin();
}

void loop() {
  server.handleClient();
  MDNS.update();
}
