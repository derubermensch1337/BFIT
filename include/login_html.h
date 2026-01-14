#ifndef LOGIN_HTML_H
#define LOGIN_HTML_H

#include <pgmspace.h>

const char LOGIN_HTML[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8">
            <title>Login</title>
            <link rel="stylesheet" href="/style.css">
        </head>
        <body>
            <div class="login_box">
                <h2>
                    Login
                </h2>
                <form action="/login" method="POST">
                    <label>
                        Username
                    </label>
                    <br>
                        <input type="text" name="user">
                    <br>
                    <br>
                        <label>
                            Password
                        </label>
                        <br>
                            <input type="password" name="pass">
                        <br>
                    <br>
                    <a href="/"><input type="button" value="Back"></a>
                    <a href="/admin"><input type="button" value="Login"></a>
                </form>
            </div>
        </body>
    </html>
)rawliteral";

#endif