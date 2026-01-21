/**
 * @file    main.cpp
 * @brief   Combined: Web server + Graph + Scale + RFID access + Lock control
 * @author  Baldur G. Toftegaard
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>

/* --- Web UI / Graph --- */
#include "index_html.h"
#include "sale_html.h"
#include "STYLE_CSS.h"
#include "LOGIN_HTML.h"
#include "ADMIN_HTML.h"
#include "graph_data.h"

/* --- Inventory / Sale / Scale --- */
#include "inventory.h"
#include "init_users_and_sale.h"
#include "weight_scale.h"
#include "fridge_state.h"

/* --- RFID / Lock / Buzzer --- */
#include "rfid_access.h"
#include "lock_ctrl.h"
#include "buzzer.h"

/* ---------------- Configuration ---------------- */

static const float    CAL_FACTOR     = 696.0f;
static const uint16_t START_BEER_QTY  = 20;

const char* WIFI_SSID = "Baldur's A56";
const char* WIFI_PASS = "MyPasskeyA56";

/* ---------------- Global State ---------------- */

// Graph data (used by sale_html + /saleHeights)
int greenHeight[ROOM_COUNT]   = {200, 0, 23, 30, 80, 30, 26, 22, 20, 23, 92, 29, 26, 94, 23, 8, 3, 0};
int classicHeight[ROOM_COUNT] = {20,  4, 238,30, 80, 30, 26, 22, 20, 23, 92, 29, 26, 94, 23,38,83,90};

// Demo inventory product
product demo_beer;

// Web server
ESP8266WebServer server(80);

// RFID + door control
MFRC522 rfid(SS_PIN, RST_PIN);
RFIDcommand activeCommand = CMD_NONE;

bool doorUnlocked = false;
unsigned long doorCloseTimer = 0; // starts when door is closed but not locked

/* ---------------- Helpers ---------------- */

static void connect_wifi_and_start_mdns()
{
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    yield();
  }

  Serial.println();
  Serial.print("WiFi connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("iot")) {
    Serial.println("mDNS responder started (iot.local)");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }
}

static void setup_web_routes()
{
  server.on("/", HTTP_GET, []() {
    // If you want the graph page as the homepage:
    send_sale_html_page(server, ROOM_COUNT, greenHeight, classicHeight);
    // If you want your old index page instead, swap to:
    // server.send_P(200, "text/html", INDEX_HTML);
  });

  server.on("/saleHeights", HTTP_GET, []() {
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

  server.onNotFound([]() {
    server.send(404, "text/plain", "404: Not found");
  });

  server.begin();
  Serial.println("HTTP server started");
}

static void setup_inventory_and_scale()
{
  Serial.println("Before setup_scale()");
  setup_scale(CAL_FACTOR);
  Serial.println("After setup_scale()");

  Serial.println("Init the fridge inventory");
  inventory_init(&fridge);

  Serial.println("Define the beverage");
  demo_beer = inventory_make_product("Demo Beer", beer, 350, 10);
  inventory_add_product(&fridge, demo_beer, START_BEER_QTY);

  Serial.println("Initial inventory:");
  inventory_print(&fridge);

  // Establish baseline reference (your perform_sale() does this on first call)
  perform_sale(&fridge);
}

static void setup_rfid_and_lock()
{
  setup_RFID_reader(rfid);
  get_users_db(&users[0]);

  lock_ctrl_init();

  display_commands();
}

/* ---------------- setup() ---------------- */
void setup()
{
  Serial.begin(115200);
  delay(200);

  Serial.println("\nBOOT");

  connect_wifi_and_start_mdns();
  Serial.println("WIFI OK");

  setup_web_routes();
  Serial.println("HTTP OK");   // if you never see this, setup_web_routes() never finishes

  // Delay to prove the server is reachable even if later init hangs
  Serial.println("Pause 3s - try opening the webpage now");
  delay(3000);

  setup_inventory_and_scale();
  Serial.println("SCALE+INV OK");

  setup_rfid_and_lock();
  Serial.println("RFID+LOCK OK");
}

/* ---------------- loop() ---------------- */

void loop()
{
  // Keep web server responsive
  server.handleClient();
  MDNS.update();
  yield();

  // Keep scale updated
  update_scale();

  // Print weight once per second (non-blocking)
  static uint32_t lastWeightPrintMs = 0;
  if (millis() - lastWeightPrintMs >= 1000) {
    lastWeightPrintMs = millis();
    Serial.print("Weight: ");
    Serial.println(get_weight());
  }

  // If MFRC522 got disconnected / serial monitor toggled: re-init
  byte v = rfid.PCD_ReadRegister(rfid.VersionReg);
  if (v == 0x00 || v == 0xFF) {
    Serial.println("RFID communication failure: initializing rfid");
    rfid.PCD_Init();
  }

  // If no command active, latch a new command
  if (activeCommand == CMD_NONE) {
    RFIDcommand newCmd = check_command();
    if (newCmd != activeCommand) {
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

    case CMD_LOCK:
      Serial.println("Door is closed. Locking door.");
      lock_door();
      doorUnlocked = false;
      doorCloseTimer = 0;
      play_lock();
      activeCommand = CMD_NONE;
      display_commands();
      break;

    case CMD_NONE:
    default:
      // Normal mode: check RFID only if door is locked
      if (!doorUnlocked && validate_rfid(rfid)) {
        Serial.println("Access granted. Unlocking door.");
        unlock_door();
        doorUnlocked = true;
        play_unlock();
        display_commands();
      }

      // Start timer when door is closed (but not locked)
      if (doorUnlocked && is_box_closed() && doorCloseTimer == 0) {
        Serial.println("Door is closed but not locked, starting timer");
        doorCloseTimer = millis();
      }

      play_warning(doorCloseTimer);

      // Reset timer if door is opened
      if (!is_box_closed() && doorCloseTimer > 0) {
        Serial.println("Door is opened, resetting timer");
        doorCloseTimer = 0;
      }

      // Auto-lock after 5 seconds of being closed
      if (doorUnlocked && is_box_closed() && doorCloseTimer != 0 && (millis() - doorCloseTimer > 5000)) {
        Serial.println("Door is closed. Locking door.");
        lock_door();
        doorUnlocked = false;
        doorCloseTimer = 0;
        play_lock();
        display_commands();
        perform_sale(&fridge);
        Serial.println("[SALE] Running perform_sale() after door close");
      }

      break;
  }

  yield();
}
