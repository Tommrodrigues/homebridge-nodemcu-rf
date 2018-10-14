#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// GitHub Page = https://github.com/Tommrodrigues/homebridge-nodemcu-rf

// Script Type = NodeMCU 433 Mhz transmitter

// Make sure to add "rc-switch" in the ArduinoIDE "Boards Manager" area
// Will emmit specified code when GET request in this format is made: http://<NodeMCU IP Address>/SWITCH-<number>=<ON/OFF>

// |NodeMCU Pin| = |Transmitter Pin|
// D3 = Transmitter Data Pin
// VIN = Transmitter VCC (Power) pin
// GND = Transmitter Ground

/////////////////////// BASIC VALUES /////////////////////////
const char* ssid = "SSID"; //Name of your network
const char* password = "PASSWORD"; //Password for your network
//////////////////////////////////////////////////////////////

///////////////////////// RF VALUES //////////////////////////
const int pulseLength = 172; //RF Pulse length
const int repeatNumber = 7; //Number of "Codesends". (Leave it at 7 for default)

// Replace the values below with each RF code, ON/OFF respectively
const int oneON = 10176012;
const int oneOFF = 10176004;

const int twoON = 10176010;
const int twoOFF = 10176002;

const int threeON = 10176009;
const int threeOFF = 10176001;

const int fourON = 10176013;
const int fourOFF = 10176005;

const int fiveON = 10176011;
const int fiveOFF = 10176003;
//////////////////////////////////////////////////////////////


const int redPin = 16; //Declaers "redPin" being pin 16 (Red indicator LED)

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(redPin, OUTPUT);
  digitalWrite(redPin, LOW);

  mySwitch.enableTransmit(0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  WiFi.softAPdisconnect(true);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  // Start the mDNS responder for nodemcu.local
  if (!MDNS.begin("nodemcu")) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");

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
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // ONLY CHANGE THE FOLLOWING:
  // Replace your RF code:  mySwitch.send(<CODE>, 24);

  if (request.indexOf("/SWITCH-1=ON") != -1)  {
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(pulseLength);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(oneON, 24);

  }
  if (request.indexOf("/SWITCH-1=OFF") != -1)  {
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(pulseLength);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(oneOFF, 24);

  }

  if (request.indexOf("/SWITCH-2=ON") != -1)  {
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(pulseLength);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(twoON, 24);

  }
  if (request.indexOf("/SWITCH-2=OFF") != -1)  {
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(pulseLength);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(twoOFF, 24);

  }

  if (request.indexOf("/SWITCH-3=ON") != -1)  {
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(pulseLength);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(threeON, 24);

  }
  if (request.indexOf("/SWITCH-3=OFF") != -1)  {
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(pulseLength);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(threeOFF, 24);

  }

  if (request.indexOf("/SWITCH-4=ON") != -1)  {
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(pulseLength);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(fourON, 24);

  }
  if (request.indexOf("/SWITCH-4=OFF") != -1)  {
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(pulseLength);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(fourOFF, 24);

  }

  if (request.indexOf("/SWITCH-5=ON") != -1)  {
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(pulseLength);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(fiveON, 24);

  }
  if (request.indexOf("/SWITCH-5=OFF") != -1)  {
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(pulseLength);
    mySwitch.setRepeatTransmit(repeatNumber);
    mySwitch.send(fiveOFF, 24);

  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  // A response would go here

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
