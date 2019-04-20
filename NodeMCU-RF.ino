#include <ESP8266WiFi.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// GitHub Page = https://github.com/Tommrodrigues/homebridge-nodemcu-rf

// D3 = Transmitter Data Pin
// VIN = Transmitter VCC (Power) pin
// GND = Transmitter Ground

/////////////////// CHANGE THESE VALUES //////////////////////
const char* ssid = "SSID"; //Name of your network
const char* password = "PASSWORD"; //Password for your network
//////////////////////////////////////////////////////////////

const int repeatNumber = 7; //Number of "Codesends". (Leave it at 7 for default)

const int redPin = 16;
WiFiServer server(80);

int rfCode;
int rfPulse;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(redPin, OUTPUT);
  digitalWrite(redPin, LOW);

  mySwitch.enableTransmit(0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.println("Connecting to \"" + String(ssid) + "\"");

  WiFi.softAPdisconnect(true);
  WiFi.begin(ssid, password);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(String(++i) + " ");
  }
  Serial.println();
  Serial.println("Connected successfully");

  // Start the server
  server.begin();

  // Print the IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  digitalWrite(redPin, HIGH);

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("New client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");

  // Match the request
  if (request.indexOf("/CODE") != -1) {
    rfCode = request.substring(10, 19).toInt();
    rfPulse = request.substring(25).toInt();

    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(rfPulse);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(rfCode, 24);

    Serial.println("");
    Serial.println("RF transmission succeeded!");
    Serial.print("Code: ");
    Serial.println(rfCode);
    Serial.print("Pulse: ");
    Serial.println(rfPulse);
    Serial.print("Repeats: ");
    Serial.println(repeatNumber);
    Serial.println("");
  }

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
