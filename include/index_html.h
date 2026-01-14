/**
 * @file index_html.h
 * @author Baldur G. Toftegaard
 * @brief 
 * @version 0.1
 * @date 13-01-2026
 * @par Revision history
 * | Version |    Date    | Description                                                             |
 * |---------|------------|-------------------------------------------------------------------------|
 * | 0.1     | 13-01-2026 | Creaded file,                                                           |
 * | 0.1     |            |                                                                         |
 * @copyright Copyright (c) 2026 
 */

#ifndef INDEX_HTML_H
#define INDEX_HTML_H

#include <pgmspace.h>

const char INDEX_HTML[] PROGMEM = R"rawliteral(
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
                    Welcome!
                </div>
                <div class="right">
                    <a href="/login">Login</a>
                </div>
            </div>

            <div class="sale_box">
                <p>Fancy sale data goes here </p>
            </div>

        </body>
    </html>
)rawliteral";

#endif
