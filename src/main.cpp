/**
 * @file main.cpp
 * @authors Baldur G. Toftegaard,
 * @brief Main, used to establish a webs server. 
 * @date 13-01-2026
 * @version 0.1
 * @par Revision history
 * | Version |    Date    | Description                       |
 * |---------|------------|-----------------------------------|
 * | 0.1     | 13-01-2026 | Add creating a web server         |
 * | 0.1     |            |                                   |
 * 
 * @copyright Copyright (c) 2026
 * 
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
#include "rfid_access.h"
#include "lock_ctrl.h"

// Global definition
bool doorUnlocked = false;

MFRC522 rfid(SS_PIN, RST_PIN);
RFIDcommand activeCommand = CMD_NONE; // Initial command

ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);  // Create an instance of the server

void handleNotFound();

void setup() {
  Serial.begin(115200);
  delay(200);
  
  /*
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
    server.send_P(200, "text/html", INDEX_HTML);
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
*/
  // Initialize RFID reader
  setup_RFID_reader(rfid);
  
  // Get users from database
  get_users_db(&users[0]);

  
  // Lock servo
  lock_ctrl_init();

  // Display commands
  display_commands(); 
} 

void loop() {
  //server.handleClient();
  // TODO: this should be moved inside a function
  // If no command is active, check for a new one and latch
  if (activeCommand == CMD_NONE) {
    RFIDcommand newCmd = check_command();
    if (newCmd != activeCommand){
      activeCommand = newCmd;
    }
  }

  // Execute active command
  switch (activeCommand) {
    case CMD_ADD_USER:
    case CMD_REMOVE_USER:
      user_management(activeCommand, &users[0], rfid);
      activeCommand = CMD_NONE;
      display_commands();  
      break;
    case CMD_PRINT:
      print_all_users(&users[0]);
      activeCommand = CMD_NONE;
      display_commands();  
      break;
    case CMD_NONE:
    default:
      // Check RFID only if door is locked
      if (!doorUnlocked && validate_rfid(rfid)) {
        Serial.println("Access granted. Unlocking door.");
        unlock_door();
        doorUnlocked = true;
      }

      // Lock when door is closed
      if (doorUnlocked && is_box_closed()) {
        Serial.println("Closed door. Locking door.");
        lock_door();
        doorUnlocked = false;
      }
      break;
    }
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}


// server.on("/LED", HTTP_POST, handleLED);
// server.onNotFound(handleNotFound);

// void handleLED() {                          // If a POST request is made to URI /LED
//   digitalWrite(led,!digitalRead(led));      // Change the state of the LED
//   server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
//   server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
// }



