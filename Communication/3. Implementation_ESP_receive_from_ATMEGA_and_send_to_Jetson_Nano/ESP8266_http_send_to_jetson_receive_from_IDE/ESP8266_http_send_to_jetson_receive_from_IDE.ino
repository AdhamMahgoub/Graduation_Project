#include <ESP8266WiFi.h>
#include "ESPAsyncWebSrv.h"

//credentials for access point 
const char* ssid = "dooma";
const char* password = "123456789";

AsyncWebServer server(80);

// Define a global variable to store the message
String message = "Initial message"; 
//This Global Variable is updated inside the loop and is taken as argument when the request is called

void setup(){
  Serial.begin(2400);
  Serial.println();
  
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Set up the server to handle requests on the "/temperature" path
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", message.c_str());
  });

  server.begin();
}

void loop(){
  /*
  // Update the message with the current time
  unsigned long currentMillis = millis();
  unsigned long hours = (currentMillis / (1000 * 60 * 60)) % 24;
  unsigned long minutes = (currentMillis / (1000 * 60)) % 60;
  unsigned long seconds = (currentMillis / 1000) % 60;

  // Update the message with the current time
  message = "Current time: " + String(hours) + ":" + String(minutes) + ":" + String(seconds);
  */

  // listen for communication from the Arduino IDE (UART) and send it to Jetson Nano 
    if (Serial.available())
    {
        message = Serial.readString(); // this will be sent to the http when http request is sent 
    }

}
