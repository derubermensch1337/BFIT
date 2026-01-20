/**
 * @file sale_html.cpp
 * @brief 
 * @author Baldur G. Toftegaard
*/

#include "index_html.h"
#include "sale_html.h"

const char SALE_BOX_START[] PROGMEM = R"rawliteral( <div class="sale_box">)rawliteral";

const char SALE_BOX_ROOM_START[] PROGMEM = R"rawliteral( <div class="sale_room">)rawliteral";

const char SALE_BOX_ROOM_ID[] PROGMEM = R"rawliteral(<div id="room)rawliteral"; // room number and type

const char SALE_BOX_ROOM_CLASS_TYPE[] PROGMEM = R"rawliteral(" class="sale_pole_)rawliteral"; // type

const char SALE_BOX_ROOM_CLASS_HEIGHT[] PROGMEM = R"rawliteral(" style="height:)rawliteral"; // height

const char SALE_BOX_ROOM_END[] PROGMEM = R"rawliteral(px;"></div>)rawliteral";

const char SALE_BOX_ROOM_STOP[] PROGMEM = R"rawliteral(</div>)rawliteral";

const char SALE_BOX_STOP[] PROGMEM = R"rawliteral(</div>)rawliteral";

void send_sale_html_graph(
    ESP8266WebServer &server,
    uint8_t room_number,
    const char *bar_type,
    int bar_height
){
    // Generates EXACT IDs:
    // room1_green / room1_clasic
    server.sendContent(F("<div id=\"room"));
    server.sendContent(String(room_number));
    server.sendContent(F("_"));
    server.sendContent(bar_type);
    server.sendContent(F("\" class=\"sale_pole_"));
    server.sendContent(bar_type);
    server.sendContent(F("\" style=\"height:"));
    server.sendContent(String(bar_height));
    server.sendContent(F("px;\"></div>"));
}


void send_sale_html_page(
    ESP8266WebServer &server,
    uint8_t room_count,
    const int *greenHeight,
    const int *classicHeights
){
    server.sendHeader("Cache-Control", "no-store, no-cache, must-revalidate, max-age=0");
    server.sendHeader("Pragma", "no-cache");
    server.sendHeader("Expires", "0");

    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", "");

    server.sendContent_P(INDEX_HTML_HEAD);
    server.sendContent_P(SALE_BOX_START);

    for (uint8_t room = 1; room <= room_count; room++) {
        server.sendContent_P(SALE_BOX_ROOM_START);
        send_sale_html_graph(server, room, "green",  greenHeight[room - 1]);
        send_sale_html_graph(server, room, "clasic", classicHeights[room - 1]);
        server.sendContent_P(SALE_BOX_ROOM_STOP);
    }

    server.sendContent_P(SALE_BOX_STOP);
    server.sendContent_P(INDEX_HTML_FOOT);
}
