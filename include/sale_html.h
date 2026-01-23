/**
 * @file sale_html.h
 * @brief Headerfile for displaying the graph of sales on the main page
 * @author Baldur G. Toftegaard
*/

#ifndef SALE_HTML_H
#define SALE_HTML_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <pgmspace.h>

/**
 * @brief Opening container for the sales graph.
*/
extern const char SALE_BOX_START[] PROGMEM;

/**
 * @brief Opening container for a single room graph.
*/
extern const char SALE_BOX_ROOM_START[] PROGMEM;

/**
 * @brief HTML fragment for the room identifier.
*/
extern const char SALE_BOX_ROOM_ID[] PROGMEM;

/**
 * @brief HTML fragment defining the CSS class type for a bar.
*/
extern const char SALE_BOX_ROOM_CLASS_TYPE[] PROGMEM;

/**
 * @brief HTML fragment defining the height style of a bar.
*/
extern const char SALE_BOX_ROOM_CLASS_HEIGHT[] PROGMEM;

/**
 * @brief Closing fragment for a single sales bar.
*/
extern const char SALE_BOX_ROOM_END[] PROGMEM;

/**
 * @brief Closing container for a single room graph.
*/
extern const char SALE_BOX_ROOM_STOP[] PROGMEM;

/**
 * @brief Closing container for the complete sales graph.
*/
extern const char SALE_BOX_STOP[] PROGMEM;

/**
 * @brief Sends a single sales bar element to the client.
 * @param server - The server instance.
 * @param room_number - The room number operated on.
 * @param bar_type - Type of the bar operated on.
 * @param bar_height - Height of the bre operated on.
 */
void send_sale_html_graph(
    ESP8266WebServer &server, /**< test */
    uint8_t room_number,
    const char *bar_type,
    int bar_height
);

/**
 * @brief Sends the complete sales graph page.
 * @param server - The server instance.
 * @param room_count  - Number of registered rooms.
 * @param greenHeight - The height of green bars.
 * @param classicHeights - The height of clasic bars.
*/
void send_sale_html_page(
    ESP8266WebServer &server,
    uint8_t room_count,
    const int *greenHeight,
    const int *classicHeights
);

#endif