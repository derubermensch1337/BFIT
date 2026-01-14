/**
 * @file admin_html.h
 * @authors Baldur G. Toftegaard
 * @brief 
 * @version 0.1
 * @date 13-01-2026
 * @par Revision history
 * | Version |    Date    | Description                                                             |
 * |---------|------------|-------------------------------------------------------------------------|
 * | 0.1     | 13-01-2026 | Creaded file,                                                           |
 * | 0.1     |            |                                                                         |
 * 
 * @copyright Copyright (c) 2026
 */

#ifndef ADMIN_HTML_H
#define ADMIN_HTML_H

#include <pgmspace.h>

const char ADMIN_HTML[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
            <title>Beer fridge online services</title>
            <link rel="stylesheet" href="/style.css">
        </head>
        <body>
            <div class="topbar">
                <div class="left">
                    Start -> Admin
                </div>
                <div class="right">
                    <a href="/">Log Out</a>
                </div>
            </div>

            <p> Verry inportant stuff goes here! </p>

        </body>
    </html>
)rawliteral";

#endif
