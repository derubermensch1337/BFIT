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
 * | 0.2     | 15-01-2026 | Added base graph for displaying sales                                   |
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
        margin-top: 50px;
      	margin-left: 50px;    
        margin-right: 50px;
        height: 500px;
        background: #ffffff;
        border: 2px solid #000000;
        box-sizing: border-box;
    }

    table {
        width: 100%;
        border-collapse: collapse;
        border: 2px solid #000000;
    }

    th, td {
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
	

    .sale_room {
        display: flex;
        align-items: flex-end;
        gap: 2px;
        height: 200px;
        width: fit-content;
        border: 2px solid #000000;
        box-sizing: border-box;
    }
	
    .sale_pole_green {
        height: 50px;
      	width: 98px;
        background: #4fc908;
    }

    .sale_pole_clasic {
		/* 
      	width: 50px;
        background: #d0c420;
    }
)rawliteral";

#endif