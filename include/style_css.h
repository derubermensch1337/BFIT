/**
 * @file style_css.h
 * @authors Baldur G. Toftegaard
 * @brief 
 * @version 0.1
 * @date 13-01-2026
 * @par Revision history
 * | Version |    Date    | Description                                                             |
 * |---------|------------|-------------------------------------------------------------------------|
 * | 0.1     | 13-01-2026 | Creaded file, implemented start and admin page, started general design  |
 * | 0.1     |            |                                                                         |
 * 
 * @copyright Copyright (c) 2026
*/

#ifndef STYLE_CSS_H
#define STYLE_CSS_H

#include <pgmspace.h>

const char STYLE_CSS[] PROGMEM = R"rawliteral(
    body {
        background-color: #dbdbdb;
        margin: 0;
        font-family: Arial, sans-serif;
    }

    .login_box {
        width: fit-content;
        margin: 80px auto;
    }
    
    .sale_box {
        margin-top: 50px;     /* distance from top bar */
        margin-left: 50px;    /* left spacing from page edge */
        margin-right: 50px;   /* right spacing from page edge */

        height: 500px;
        background: #ffffff;
        border: 2px solid #000000;
        box-sizing: border-box;
    }

    table {                             // Define the table element. 
        width: 100%;
        border-collapse: collapse;
        border: 2px solid #000000;
    }

    th, td {                            // Define table header and the table row.
        border: 1px solid #000000;
        padding: 6px;
        text-align: left;
    }

    .topbar {
        display: flex;
        justify-content: space-between;
        align-items: center;

        padding: 10px 16px;
        background-color: #ffffff;
        border-bottom: 2px solid #000000;
        box-sizing: border-box;
    }

    .topbar .left {
        font-size: 18px;
        font-weight: bold;
    }

    .topbar .right a {
        text-decoration: none;
        color: #000000;
        font-size: 16px;
    }

    .topbar .right a:hover {
        text-decoration: underline;
    }
    
    .sale {
        background-color: #ffffff;
        width:500px;
        height:100px; 
        font-size:24px;
    }
)rawliteral";

#endif
