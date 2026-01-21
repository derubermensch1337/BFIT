#include <Arduino.h> //Tone functions don't work without this here

#ifndef BUZZER_H
#define BUZZER_H

// Sound effects

// Plays short sound when door is closed and about to be locked
void play_warning(unsigned long t);
void play_unlock();
void play_lock();

#endif