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
#include "inventory.h"
#include "init_users_and_sale.h"
#include "weight_scale.h"
#include "fridge_state.h"

static constexpr uint8_t ROOM_COUNT = 18;
static int greenHeight[ROOM_COUNT]   = {200, 0, 23,30,80,30,26,22,20,23,92,29,26,94,23,8,3,0};
static int classicHeight[ROOM_COUNT] = {20,4,238,30,80,30,26,22,20,23,92,29,26,94,23,38,83,90};


static const float CAL_FACTOR = 696.0f;      // <-- Replace with your calibrated value
static const uint16_t START_BEER_QTY = 20;   // Keep <= 255 if current_quantity is uint8_t

// One demo product (single beer type)
product demo_beer;

// Simple helper to read a line/char from serial
static char read_serial_char_nonblocking() {
    while (Serial.available() > 0) {
        char c = (char)Serial.read();
        if (c == '\r' || c == '\n') continue;  // ignore line endings
        return c;
    }
    return '\0';
}

static void print_menu() {
    Serial.println();
    Serial.println("=== SALE TEST MENU ===");
    Serial.println("w  : print current weight (requires scale update running)");
    Serial.println("b  : set/refresh reference weight to current weight (baseline)");
    Serial.println("p  : perform_sale(&fridge) (process removal since reference)");
    Serial.println("i  : print inventory");
    Serial.println("t  : tare scale (zero offset) - optional");
    Serial.println("m  : show this menu");
    Serial.println("======================");
    Serial.println("Procedure for demo:");
    Serial.println("1) Put beers on scale");
    Serial.println("2) Press 'b' to set baseline reference");
    Serial.println("3) Remove 1-2 beers");
    Serial.println("4) Press 'p' to process sale; press 'i' to confirm inventory decreased");
    Serial.println();
}


// // test code:
static uint8_t selectedRoom = 0;   // current index [0 .. ROOM_COUNT-1]

const uint8_t BTN_SELECT_PIN = 4;  // D2
const uint8_t BTN_ADD_PIN    = 5;  // D1

bool lastSelect = HIGH;
bool lastAdd    = HIGH;

unsigned long lastDebounceMs = 0;
const unsigned long debounceMs = 50;


ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);  // Create an instance of the server

void handleNotFound();

void setup() {
  pinMode(BTN_SELECT_PIN, INPUT_PULLUP);
  pinMode(BTN_ADD_PIN, INPUT_PULLUP);

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

  server.on("/saleHeights", HTTP_GET, []() {

  // disable caching
  server.sendHeader("Cache-Control", "no-store, no-cache, must-revalidate, max-age=0");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "0");

  String json = "{";

  for (uint8_t i = 0; i < ROOM_COUNT; i++) {
      json += "\"room" + String(i + 1) + "\":{";
      json += "\"green\":"  + String(greenHeight[i]) + ",";
      json += "\"clasic\":" + String(classicHeight[i]) + "}";
      if (i < ROOM_COUNT - 1) json += ",";
    }

    json += "}";

    server.send(200, "application/json", json);
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
  
  Serial.println("Server started");

  Serial.println("Before setup_scale()");
  setup_scale(CAL_FACTOR);
  Serial.println("After setup_scale()");

  Serial.println("init the fridge inventory");
  inventory_init(&fridge);
  
  Serial.println("Define the beverage");
  demo_beer = inventory_make_product("Demo Beer", beer, 350, 10); // weight field used only as metadata here
  inventory_add_product(&fridge, demo_beer, START_BEER_QTY);
  
  Serial.println("Initial inventory:");
  inventory_print(&fridge);
  perform_sale(&fridge);
  print_menu();

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
  server.handleClient();
  yield();

  update_scale();

  static uint32_t lastPrint = 0;
  if (millis() - lastPrint > 1000) {
      lastPrint = millis();
      Serial.print("Weight (raw): ");
      Serial.println(get_weight());
  }

    char cmd = read_serial_char_nonblocking();
    if (cmd == '\0') {
      return; // this is OK but see improvement below
    }

    switch (cmd) {
        case 'w': {
            // Ensure we have a fresh sample: call update a bit
            for (int i = 0; i < 50; i++) {
                update_scale();
                delay(5);
            }
            float w = get_weight();
            Serial.print("Current weight: ");
            Serial.println(w);
            break;
        }

        case 'b': {
            // Baseline reference = current weight
            for (int i = 0; i < 50; i++) {
                update_scale();
                delay(5);
            }
            float w = get_weight();
            set_weight_reference(w);
            Serial.print("Reference weight set to: ");
            Serial.println(get_weight_reference());
            break;
        }

        case 'p': {
            // Process sale and update inventory
            perform_sale(&fridge);
            Serial.println("perform_sale executed.");
            Serial.print("New reference weight: ");
            Serial.println(get_weight_reference());
            break;
        }

        case 'i': {
            Serial.println("Inventory:");
            inventory_print(&fridge);
            break;
        }

        case 't': {
            // Optional: tare the scale. Note this changes weight behavior.
            tare_scale();
            Serial.println("Tare started (non-blocking). Waiting for completion...");
            while (!tare_complete()) {
                update_scale();
                delay(10);
            }
            Serial.println("Tare complete.");

            // After tare, baseline must be reset because readings jump.
            reset_weight_reference();
            Serial.println("Reference reset. Press 'b' to set baseline again.");
            break;
        }

        case 'm':
        default:
            print_menu();
            break;

  //server.handleClient();

  // This fixes issues with opening and closing serial monitor
  // If there is no connection to the RFID scanner, it is initialized
  // Either DTR or RTS should also be unchecked in the serial monitor (can't remember which)
  byte v = rfid.PCD_ReadRegister(rfid.VersionReg);
  if (v == 0x00 || v == 0xFF) { //These values are received if there is no connection
      Serial.println("Communication failure: initializing rfid");
      rfid.PCD_Init();
  }

  // TODO: this should be moved inside a function
  // If no command is active, check for a new one and latch
  if (activeCommand == CMD_NONE) {
    RFIDcommand newCmd = check_command();
    if (newCmd != activeCommand){
      activeCommand = newCmd;
    }
  }

  // For debugging
  // Serial.print("Command before switch: ");
  // Serial.println(activeCommand);

  // Execute active command
  switch (activeCommand) {
    case CMD_ADD_USER:    // Same as CMD_REMOVE_USER
    case CMD_REMOVE_USER:
      user_management(activeCommand, &users[0], rfid);  // The function adds or removes user depending on command
      activeCommand = CMD_NONE;
      display_commands();
      break;
    case CMD_PRINT:
      print_all_users(&users[0]);
      activeCommand = CMD_NONE;
      display_commands();  
      break;
    case CMD_LOCK:
        Serial.println("Door is closed. Locking door.");
        lock_door();
        doorUnlocked = false;
        timer = 0;
        play_lock();
        activeCommand = CMD_NONE;
        display_commands();
      break;

    case CMD_NONE:
    default:

      // If there is no valid command, the RFID scanner is checked

      // Check RFID only if door is locked
      if (!doorUnlocked && validate_rfid(rfid)) {
        Serial.println("Access granted. Unlocking door.");
        unlock_door();
        doorUnlocked = true;
        play_unlock();
        display_commands();  
      }

      // Start timer when door is closed
      if (doorUnlocked && is_box_closed() && timer == 0) {
        Serial.println("Door is closed but not locked, starting timer");
        timer = millis();
      }

      play_warning(timer);

      //Reset timer if door is opened
      if (!is_box_closed() && timer > 0) {
        Serial.println("Door is opened, resetting timer");
        timer = 0;
      }

      //Close the door when 5 seconds has passed since door is closed
      if (doorUnlocked && is_box_closed() && timer != 0 && (millis() - timer > 5000)) {
        Serial.println("Door is closed. Locking door.");
        lock_door();
        doorUnlocked = false;
        timer = 0;
        play_lock();
        display_commands();  
      }
      break;
    }

  bool selectNow = digitalRead(BTN_SELECT_PIN);
  bool addNow    = digitalRead(BTN_ADD_PIN);
  unsigned long now = millis();

  if (now - lastDebounceMs > debounceMs) {

    // Button 1: select next room index
    if (lastSelect == HIGH && selectNow == LOW) {
      selectedRoom++;
      if (selectedRoom >= ROOM_COUNT) {
        selectedRoom = 0;   // wrap back to first
      }

      Serial.print("Selected room: ");
      Serial.println(selectedRoom + 1);

      lastDebounceMs = now;
    }

    // Button 2: add +5 to selected room
    if (lastAdd == HIGH && addNow == LOW) {
      greenHeight[selectedRoom] += 5;

      Serial.print("Room ");
      Serial.print(selectedRoom + 1);
      Serial.print(" greenHeight = ");
      Serial.println(greenHeight[selectedRoom]);

      lastDebounceMs = now;
    }
  }

  lastSelect = selectNow;
  lastAdd    = addNow;
}


void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}