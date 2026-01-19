/**
 * @file index_html.h
 * @brief HTML for the start page
 * @author Baldur G. Toftegaard
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
            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room1_clasic" class="sale_pole_clasic" style="height: 20px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room2_clasic" class="sale_pole_clasic" style="height: 30px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room3_clasic" class="sale_pole_clasic" style="height: 40px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room4_clasic" class="sale_pole_clasic" style="height: 50px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room5_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room6_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">            
                <div class="sale_pole_green"></div>
                <div id="room7_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room8_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room9_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room10_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room11_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room12_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room13_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room14_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room15_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room16_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="room17_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar18_clasic" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>
        </div>

        <script>
            async function refreshHight() {
                try {
                    const res = await fetch('/saleHight', { cache: 'no-store' });
                    const txt = await res.text();
                    const h = parseInt(txt, 10);
                    const el = document.getElementById('bar1');
                    if (el && !Number.isNaN(h)) {
                        el.style.height = h + 'px';
                    }
                } catch (e) {}
            }
            refreshHight();
            setInterval(refreshHight, 200);
        </script>
    </body>
</html>
)rawliteral";

#endif