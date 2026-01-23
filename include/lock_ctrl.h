/**
 * @file lock_ctrl.h
 * @brief Door lock control interface using a servo and light sensor.
 * @author Amal Araweelo Almis
 */
 
#ifndef LOCK_CTRL_H
#define LOCK_CTRL_H

#include <Servo.h>

// Pins
/** GPIO pin connected to the servo motor */
#define SERVO_PIN 16

/** Light threshold indicating a closed box */
#define CLOSED_THRESHOLD 70

/** GPIO pin connected to light detector */
#define LIGHT_PIN A0

/** Light threshold indicating an open box */
#define OPEN_THRESHOLD 100    // to avoid issues

/**
 * @brief Initializes the lock control module.
 *
 * Must be called once during system startup before any other
 * lock control functions are used.
 */
void lock_ctrl_init();

// Actions
/**
 * @brief Locks the door using the servo.
 */
void lock_door();

/**
 * @brief Unlocks the door using the servo.
 */
void unlock_door();

// Photosensor state
/**
 * @brief Checks whether the box is closed.
 *
 * Uses the light sensor to determine door state.
 *
 * @return true  Box is closed.
 * @return false Box is open.
 */
bool is_box_closed();

/**
 * @brief Plays the sound effect for door opening.
 */
void play_open();

/**
 * @brief Play sound effect when the door closes.
*/
void play_close();

#endif