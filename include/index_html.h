/**
 * @file index_html.h
 * @brief HTML for the start page
 * @author Baldur G. Toftegaard
 */

#ifndef INDEX_HTML_H
#define INDEX_HTML_H

#include <pgmspace.h>

const char INDEX_HTML_HEAD[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Beer fridge online services</title>
    <link rel="stylesheet" href="/style.css">
  </head>
  <body>
    <div class="topbar">
      <div class="left">Welcome!</div>
      <div class="right"><a href="/login">Login</a></div>
    </div>
)rawliteral";


        
const char INDEX_HTML_FOOT[] PROGMEM = R"rawliteral(
        <script>
            async function refreshGraphs() {
                try {
                    const res = await fetch('/saleHeights', { cache: 'no-store' });
                    const data = await res.json();

                    for (const room in data) {
                        const green  = document.getElementById(room + "_green");
                        const clasic = document.getElementById(room + "_clasic");

                        if (green)  green.style.height  = data[room].green  + "px";
                        if (clasic) clasic.style.height = data[room].clasic + "px";
                    }
                } catch (e) {
                    console.error(e);
                }
            }
            refreshGraphs();
            setInterval(refreshGraphs, 200);
        </script>
    </body>
</html>
)rawliteral";


#endif