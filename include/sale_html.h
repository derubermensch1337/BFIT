/**
 * @file sale_html.h
 * @brief Headerfile for displaying the graph of sales on the main page
 * @authors Baldur G. Toftegaard
*/

#ifndef SALE_HTML_H
#define SALE_HTML_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <pgmspace.h>

/**
 * @brief 
*/
extern const char SALE_BOX_START[] PROGMEM;

/**
 * @brief 
*/
extern const char SALE_BOX_ROOM_START[] PROGMEM;

/**
 * @brief 
*/
extern const char SALE_BOX_ROOM_ID[] PROGMEM;

/**
 * @brief 
*/
extern const char SALE_BOX_ROOM_CLASS_TYPE[] PROGMEM;

/**
 * @brief 
*/
extern const char SALE_BOX_ROOM_CLASS_HEIGHT[] PROGMEM;

/**
 * @brief 
*/
extern const char SALE_BOX_ROOM_END[] PROGMEM;

/**
 * @brief 
*/
extern const char SALE_BOX_ROOM_STOP[] PROGMEM;

/**
 * @brief 
*/
extern const char SALE_BOX_STOP[] PROGMEM;

void send_sale_html_graph(
    ESP8266WebServer &server,
    uint8_t room_number,
    const char *bar_type,
    int bar_height
);

void send_sale_html_page(
    ESP8266WebServer &server,
    uint8_t room_count,
    const int *greenHeight,
    const int *classicHeights
);

#endif