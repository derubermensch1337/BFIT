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
static const int LOCK_POS   = 100;

const int BUZZER = 2;   // Could be improved, issues with resets
const double HIGH_TONE = 1000;
const double LOW_TONE = 600;
const unsigned long TONE_LENGTH = 200;

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

    if(millis()%1000 == 0) {
        //For debugging
        //Serial.println(light);
        //Serial.println(boxClosed);
    }

    return boxClosed;
}

void play_warning(unsigned long t) {

    switch(millis() - t){
        case 1000 ... 1100:
            tone(BUZZER, HIGH_TONE, TONE_LENGTH);
            break;
        case 3000 ... 3100:
            tone(BUZZER, HIGH_TONE, TONE_LENGTH);
            break;
        default:
        break;
    }
}

void play_open(){
    tone(BUZZER, LOW_TONE);
    delay(TONE_LENGTH);
    noTone(BUZZER);
    tone(BUZZER, HIGH_TONE, 2*TONE_LENGTH);
}

void play_close(){
    tone(BUZZER, HIGH_TONE);
    delay(TONE_LENGTH);
    noTone(BUZZER);
    tone(BUZZER, LOW_TONE, 2*TONE_LENGTH);
}