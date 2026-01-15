/**
 * @file index_html.h
 * @author Baldur G. Toftegaard
 * @brief 
 * @version 0.2
 * @date 15-01-2026
 * @par Revision history
 * | Version |    Date    | Description                                                             |
 * |---------|------------|-------------------------------------------------------------------------|
 * | 0.1     | 13-01-2026 | Creaded file,                                                           |
 * | 0.1     |            |        
 * | 0.2     | 15-01-2026 | Saar Attempts dynamic configuration of html file!!1!1!                  |
 * @copyright Copyright (c) 2026 
 */

#ifndef INDEX_HTML_H
#define INDEX_HTML_H

#include <sale_html.h>
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

        	<h1>Hot damn y'all be drinkin</h1>
        	<table class="graph">
          	<caption>How you drink this much?</caption>
          	<thead>
          		<tr>
          			<th scope="col">Person</th>
          			<th scope="col">Beers Consumed</th>
          		</tr>
          	</thead><tbody class="horizontal">
          		<tr style="height:%1_BEEERS%">
          			<th scope="row">Joseph von Humperdink</th>
          			<td><span>%1_BEERS%</span></td>
          		</tr>
          		<tr style="height:%2_BEEERS%">
          			<th scope="row">Goolash McGunderson</th>
          			<td><span>%2_BEEERS%</span></td>
          		</tr>
          		<tr style="height:%3_BEEERS%">
          			<th scope="row">Gulash the Splendiferous</th>
          			<td><span>%3_BEEERS%</span></td>
          		</tr>
          		<tr style="height:%4_BEEERS%">
          			<th scope="row">Flblthp, the Fool</th>
          			<td><span>%4_BEEERS%</span></td>
          		</tr>
          		<tr style="height:5_BEEERS%">
          			<th scope="row">James David Vance</th>
          			<td><span>%5_BEEERS%</span></td>
          		</tr>
          		<tr style="height:%6_BEEERS%">
          			<th scope="row">Ben Shapiro</th>
          			<td><span>%6_BEEERS%</span></td>
          		</tr>
          		<tr style="height:%7_BEEERS">
          			<th scope="row">Alexandra Ocasio Cortez</th>
          			<td><span>%7_BEEERS%</span></td>
          		</tr>
          		<tr style="height:%8_BEEERS">
          			<th scope="row">Cloop</th>
          			<td><span>%8_BEEERS%</span></td>
          		</tr>
          		</tr>
          	</tbody>
          </table>

        </body>
    </html>
rawliteral";

#endif
