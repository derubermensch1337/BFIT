/**
 * @file admin_html.h
 * @brief HTML for the admin page
 * @authors Baldur G. Toftegaard
 */

#ifndef ADMIN_HTML_H
#define ADMIN_HTML_H

#include <pgmspace.h>

/**
 * @brief HTML for the admin page, is handled by the compiler as a string.
*/
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
