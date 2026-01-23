#include <Arduino.h> //Tone functions don't work without this here

#ifndef BUZZER_H
#define BUZZER_H

/**
 * @brief Plays short sound when door is closed and about to be locked
 * 
 * @param t 
 */
void play_warning(unsigned long t);

/**
 * @brief Plays an ascending tone, when the door unlocks.
*/
void play_unlock();

/**
 * @brief Play a descending tone, when the door locks.
*/
void play_lock();

#endif