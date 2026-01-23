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
 * @brief Play when the door is unlocked
*/
void play_unlock();

/**
 * @brief Play when the door locks
*/
void play_lock();

#endif