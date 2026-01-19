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
    server.sendContent_P(SALE_BOX_ROOM_ID);
    server.sendContent(String(room_number));
    server.sendContent("_");
    server.sendContent(bar_type);

    server.sendContent_P(SALE_BOX_ROOM_CLASS_TYPE);
    server.sendContent(bar_type);

    server.sendContent_P(SALE_BOX_ROOM_CLASS_HEIGHT);
    server.sendContent(String(bar_height));

    server.sendContent_P(SALE_BOX_ROOM_END);
}

void send_sale_html_page(
    ESP8266WebServer &server,
    uint8_t room_count,
    const int *greenHeight,
    const int *classicHeights
){
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", "");
    server.sendContent_P(INDEX_HTML_HEAD);
    server.sendContent_P(SALE_BOX_START);

    for (uint8_t room_number = 1; 
        room_number <= room_count; 
        room_number++
    ){
        server.sendContent_P(SALE_BOX_ROOM_START);
        send_sale_html_graph(server, room_number, "green", greenHeight[room_number-1]);
        send_sale_html_graph(server, room_number, "clasic", classicHeights[room_number-1]);
        server.sendContent_P(SALE_BOX_ROOM_STOP);
    }

    server.sendContent_P(SALE_BOX_STOP);
    server.sendContent_P(INDEX_HTML_FOOT);
    server.client().stop();
}