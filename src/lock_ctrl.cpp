/**
 * @file lock_ctrl.cpp
 * @authors Amal Araweelo Almis
 * @brief 
*/

#include "lock_ctrl.h"

static Servo lockServo;

// Fixed 0 mechanically
static const int UNLOCK_POS = 0;
static const int LOCK_POS   = 100;

// Internal latched state
static bool boxClosed = false;

void lock_ctrl_init() {
    // EXACTLY like your working Arduino sketch
    lockServo.write(LOCK_POS);   // start locked
    lockServo.attach(SERVO_PIN, 500, 2500);
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

    return boxClosed;
}

