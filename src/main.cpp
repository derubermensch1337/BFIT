/**
 * @file    main.cpp
 * @brief   Main, used to establish a webs server.
 * @author  Baldur G. Toftegaard 
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266WebServer.h>   // Include the WebServer library
#include <ESP8266mDNS.h>        // Include the mDNS library

#include <Arduino.h>
#include "index_html.h"
#include "sale_html.h"
#include "STYLE_CSS.h"
#include "LOGIN_HTML.h"
#include "ADMIN_HTML.h"
//#include "rfid/rfid_unlock.h"
#include "inventory.h"
#include "init_users_and_sale.h"

static constexpr uint8_t ROOM_COUNT = 18;
static int greenHeight[ROOM_COUNT]   = {0, 0, 23,30,80,30,26,22,20,23,92,29,26,94,23,8,3,0};
static int classicHeight[ROOM_COUNT] = {200,4,23,30,80,30,26,22,20,23,92,29,26,94,23,38,83,90};


ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);  // Create an instance of the server

void handleNotFound();

void setup() {
  Serial.begin(115200);
  delay(200);                             // Delay to alow the board rate to be configure before continuing (stops standard boadloader print from messing up).

  // Connect to WiFi network
  WiFi.begin("Baldur's A56", "MyPasskeyA56");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected to ");
  Serial.println(WiFi.SSID());
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("iot")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, []() {
    send_sale_html_page(server, ROOM_COUNT, greenHeight, classicHeight);
  });
  
  server.on("/style.css", HTTP_GET, []() {
    server.send_P(200, "text/css", STYLE_CSS);
  });

  server.on("/login", HTTP_GET, []() {
    server.send_P(200, "text/html", LOGIN_HTML);
  });

  server.on("/admin", HTTP_GET, []() {
    server.send_P(200, "text/html", ADMIN_HTML);
  });

  // Start the server
  server.begin();
  Serial.println("Server started"); 
} 

void loop() {
  server.handleClient();
  yield();
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

