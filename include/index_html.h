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
 * | 0.2     | 15-01-2026 | Added base graph for displaying sales                                   |
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
                <div id="saleClassic" class="sale_pole_clasic" style="height: %SALE_HIGHT%px;">
            </div>
        </div>

        <script>
            async function refreshHight() {
                try {
                    const res = await fetch('/saleHight', { cache: 'no-store' });
                    const txt = await res.text();
                    const h = parseInt(txt, 10);
                    if (!Number.isNaN(h)) {
                        document.getElementById('saleClassic').style.height = h + 'px';
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