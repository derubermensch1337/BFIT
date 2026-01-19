/**
 * @file lock_ctrl.h
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
 
#ifndef LOCK_CTRL_H
#define LOCK_CTRL_H

#include <Servo.h>

// Pins
#define SERVO_PIN 5   // D1 = GPIO5
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

#endif
