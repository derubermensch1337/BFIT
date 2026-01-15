/**
 * @file index_html.h
 * @author Baldur G. Toftegaard
 * @brief 
 * @version 0.1
 * @date 13-01-2026
 * @par Revision history
 * | Version |    Date    | Description                                                             |
 * |---------|------------|-------------------------------------------------------------------------|
 * |   0.1   | 13-01-2026 | Creaded file,                                                           |
 * |   0.2   | 15-01-2026 | Added base graph for displaying sales                                   |
 * |   0.3   | 15-01-2026 | Exented grap functionality to multiple graphs, fixed placement      |
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
            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar1" class="sale_pole_clasic" style="height: 20px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar2" class="sale_pole_clasic" style="height: 30px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar3" class="sale_pole_clasic" style="height: 40px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar4" class="sale_pole_clasic" style="height: 50px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar5" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar6" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">            
                <div class="sale_pole_green"></div>
                <div id="bar7" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar8" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar9" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar10" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar11" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar12" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar13" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar14" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar15" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar16" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar17" class="sale_pole_clasic" style="height: 60px;"></div>
            </div>

            <div class="sale_room">
                <div class="sale_pole_green"></div>
                <div id="bar18" class="sale_pole_clasic" style="height: 60px;"></div>
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