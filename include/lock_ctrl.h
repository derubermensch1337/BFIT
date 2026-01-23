/**
 * @file lock_ctrl.h
 * @brief
 * @authors Amal Araweelo Almis 
*/
 
#ifndef LOCK_CTRL_H
#define LOCK_CTRL_H

#include <Servo.h>

// Pins
#define SERVO_PIN 16   // D0 = GP16, D1 = GPIO5
#define LIGHT_PIN A0 
#define CLOSED_THRESHOLD 70   // darker than this = closed
#define OPEN_THRESHOLD 100    // to avoid issues

// Only call once in setup()
void lock_ctrl_init();

// Actions
void lock_door();
void unlock_door();

// Photosensor state
bool is_box_closed();

/**
 * @brief Play the warning sound effet
 * 
 * @param t 
*/
void play_warning(unsigned long t);

/**
 * @brief Play sound effect when door opens.
*/
void play_open();

/**
 * @brief Play sound effect when the door closes.
*/
void play_close();

#endif