/**
 * @file style_css.h
 * @brief CSS served at /style.css used for setting the style for the web server.
 * The css is handled as a string by the compiler.
 */

#ifndef STYLE_CSS_H
#define STYLE_CSS_H
#include <pgmspace.h>

/**
 * @brief String containing the CSS styling of the webserver.
 */
const char STYLE_CSS[] PROGMEM = R"rawliteral(
/* ---------- Global page styling ---------- */
body {
  margin: 0;
  padding: 0;
  font-family: Arial, Helvetica, sans-serif;
  background-color: #f0f0f0;
}

/* Bar on top of page for displaying message/path and log in */
.topbar {
  display: flex;
  justify-content: space-between;
  align-items: center;
  background-color: #2c3e50;
  color: #fff;
  padding: 12px 16px;
  box-sizing: border-box;
}

/* message/path display box */
.topbar .right a {
  color: #fff;
  text-decoration: none;
  border: 1px solid rgba(255,255,255,0.5);
  padding: 6px 10px;
  border-radius: 6px;
}

/* login button */
.topbar .right a:hover {
  background: rgba(255,255,255,0.15);
}

/* box for the graph to be placed inside */
.sale_box {
  margin: 40px auto;
  width: calc(100% - 100px);
  height: 500px;

  background-color: #ffffff;
  border: 2px solid #000000;
  box-sizing: border-box;

  display: flex;
  justify-content: space-evenly;
  align-items: flex-end;
  padding: 15px;
  gap: 0;
}

/* graph box for eatch room */
.sale_room {
  display: flex;
  align-items: flex-end;
  gap: 4px;
  height: 100%;
}

/* Bars */
.sale_pole_green {
  width: 22px;
  border: 1px solid #000000;
  box-sizing: border-box;
}

.sale_pole_clasic {
  width: 22px;
  border: 1px solid #ffffff;
  box-sizing: border-box;
}

.sale_pole_green { background-color: #2e7d32; }
.sale_pole_clasic { background-color: #ffffff; }
)rawliteral";

#endif
