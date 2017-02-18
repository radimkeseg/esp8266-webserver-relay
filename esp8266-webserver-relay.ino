/**The MIT License (MIT)

Copyright (c) 2015 by Daniel Eichhorn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

See more at http://blog.squix.ch
*/


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include "nbnsota.h"
#include "embHTML.h"

#define LED_PIN 0

ESP8266WebServer server(80);

void handle_root()
{
  String status = server.arg("led");
  Serial.println(status);
  set_led(status == "on");
   
  String content = FPSTR(PAGE_INDEX);
  server.send(200, "text/html", content);
}

void set_led(boolean status){
  digitalWrite(LED_PIN, status?HIGH:LOW);
  Serial.print("LED = ");
  Serial.println(status);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  //Serial.begin(115200);
  Serial.begin(9600);
  Serial.println("Serial: 9600");

  Serial.println("Set EEPROM offset 1k");
  EEPROM.begin(1024);

  Serial.println("init WS handlers");
  // Obsluzne handlery
  server.on("/", handle_root);
  nbnsotasetup(NULL);
  Serial.print("Our IP: ");
  Serial.println(getOurIP());

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  server.begin();
  Serial.println("HTTP server started");

}

void loop() {
//handle WS clients
  server.handleClient();
  nbnsotaloop();
//delay(1000);
}


