/**
 * @file lock_ctrl.cpp
 * @authors Amal Araweelo Almis
 * @brief Implements servo-based locking control and buzzer feedback for the fridge door.
*/

#include "lock_ctrl.h"
#include "buzzer.h" 

static Servo lockServo;

/** @brief Servo position corresponding to the unlocked state (mechanically fixed). */
static const int UNLOCK_POS = 0;

/** @brief Servo position corresponding to the locked state. */
static const int LOCK_POS = 100;

/** @brief GPIO pin connected to the buzzer.
 *
 * @note This pin choice may cause reset issues on some boards.
 */
const int BUZZER = 2;

/** @brief Frequency (Hz) used for the high-tone buzzer sound. */
const double HIGH_TONE = 1000;

/** @brief Frequency (Hz) used for the low-tone buzzer sound. */
const double LOW_TONE = 600;

/** @brief Duration of buzzer tone in milliseconds. */
const unsigned long TONE_LENGTH = 200;

/** @brief Internal latched state indicating whether the box is closed. */
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
        //For debugging
        //Serial.println(light);
        //Serial.println(boxClosed);
    }

    return boxClosed;
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