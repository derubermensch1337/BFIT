/**
 * @file lock_ctrl.cpp
 * @authors Amal Araweelo Almis
 * @brief 
 * @version 0.1
 * @date 16-01-2026
 * @par Revision history
 * | Version |    Date    | Description                                                             |
 * |---------|------------|-------------------------------------------------------------------------|
 * | 0.1     | 16-01-2026 | Created file.                                                           |
 * |         |            |                                                                         |
 * 
 * @copyright Copyright (c) 2026
 */

#include "lock_ctrl.h"

static Servo lockServo;

// Fixed 0 mechanically
static const int UNLOCK_POS = 0;
static const int LOCK_POS   = 15;

// Internal latched state
static bool boxClosed = false;


void lock_ctrl_init() {
    // EXACTLY like your working Arduino sketch
    lockServo.attach(SERVO_PIN, 500, 2500);
    lockServo.write(LOCK_POS);   // start locked
}

void lock_door() {
    lockServo.write(LOCK_POS);
}

void unlock_door() {
    lockServo.write(UNLOCK_POS);
}


bool is_box_closed(){
    int light = analogRead(LIGHT_PIN);

    if (!boxClosed && light < CLOSED_THRESHOLD) {
        boxClosed = true;

    } else if (boxClosed && light > OPEN_THRESHOLD){
        boxClosed = false;
    }

    if(millis()%1000 == 0) {
        //Serial.println(light);
        //Serial.println(boxClosed);
    }

    return boxClosed;
}