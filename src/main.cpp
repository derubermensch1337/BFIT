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
#include "INDEX_HTML.h"
#include "STYLE_CSS.h"
#include "LOGIN_HTML.h"
#include "ADMIN_HTML.h"
#include "rfid/rfid_unlock.h"
#include "inventory.h"

int salePoleClassicHight = 30;

const int BUTTON_1_PIN = 4;   // D2 (GPIO4)
const int BUTTON_2_PIN = 5;   // D1 (GPIO5)

bool lastB1 = HIGH;
bool lastB2 = HIGH;

unsigned long lastChangeMs = 0;
const unsigned long debounceMs = 50;

ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);  // Create an instance of the server

void handleNotFound();

void setup() {
  Serial.begin(115200);
  delay(200);                             // Delay to alow the board rate to be configure before continuing (stops standard boadloader print from messing up).

  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);

  // Connect to WiFi network
  WiFi.begin("Baldur's A56", "MyPasskeyA56");  // add Wi-Fi networks you want to connect to
  // wifiMulti.addAP("Inteno-66C1", "069B55753B6C9A");  // add Wi-Fi networks you want to connect to
  Serial.print("Connecting ...");
 
  while (wifiMulti.run() != WL_CONNECTED) {
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
    String page = FPSTR(INDEX_HTML);
    page.replace("%SALE_HIGHT%", String(salePoleClassicHight));
    server.send(200, "text/html", page);
  });
  
  server.on("/saleHight", HTTP_GET, []() {
    server.send(200, "text/plain", String(salePoleClassicHight));
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

  product tuborg_clasic = inventory_make_product("Tuborg clasic", beer, 250, 12);
  inventory fridge;
  inventory_init(&fridge);

  inventory_add_product(&fridge, tuborg_clasic, 10);

  inventory_print(&fridge);

  inventory_print(&fridge);
} 

void loop() {
  server.handleClient();
  yield();
  bool b1 = digitalRead(BUTTON_1_PIN);
  bool b2 = digitalRead(BUTTON_2_PIN);

  unsigned long now = millis();

  // debounce window shared (simple + effective)
  if (now - lastChangeMs > debounceMs) {
    // detect falling edge (HIGH -> LOW) == press
    if (lastB1 == HIGH && b1 == LOW) {
      salePoleClassicHight += 30;
       lastChangeMs = now;
    }
    if (lastB2 == HIGH && b2 == LOW) {
      salePoleClassicHight -= 30;
      lastChangeMs = now;
    }
  }
  lastB1 = b1;
  lastB2 = b2;
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

