/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  // prepare GPIO
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(0, HIGH);
  digitalWrite(2, HIGH);
  
  // Connect to WiFi network
//  Serial.println();
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }
//  Serial.println("");
//  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
//  Serial.println("Server started");

  // Print the IP address
//  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
//  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil(' ');
  req = client.readStringUntil(' ');
//  Serial.println(req);
  client.flush();
  
  // Match the request
  if      (req.indexOf("/leds/01/0") != -1)
  {
    digitalWrite(0,HIGH);
  }
  else if (req.indexOf("/leds/01/1") != -1)
  {
    digitalWrite(0,LOW);
  }
  else if (req.indexOf("/leds/02/0") != -1)
  {
    digitalWrite(2,HIGH);
  }
  else if (req.indexOf("/leds/02/1") != -1)
  {
    digitalWrite(2,LOW);
  }
  else if (req.indexOf("/leds/all/1") != -1)
  {
    digitalWrite(0,LOW);
    digitalWrite(2,LOW);
    Serial.println(req);
  }
  else if (req.indexOf("/leds/all/0") != -1)
  {
    digitalWrite(0,HIGH);
    digitalWrite(2,HIGH);
    Serial.println(req);
  }
  else if (req.indexOf("/leds/") != -1)
  {
    Serial.println(req);
  }
  else {
    //Serial.println("invalid request");
    client.stop();
    return;
  }

  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>OK ";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
//  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
