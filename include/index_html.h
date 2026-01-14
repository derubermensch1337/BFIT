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