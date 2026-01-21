#include "buzzer.h"

const int BUZZERPIN = 2;   // D4 = GPIO2. Could be improved, issues with resets
const double HIGH_TONE = 1000;
const double LOW_TONE = 600;
const unsigned long TONE_LENGTH = 200;

// ====================== Buzzer functions =====================================

// Plays short sound when door is closed and about to be locked
void play_warning(unsigned long t) {

    // Should play once every 2 seconds
    switch(millis() - t){
        case 1000 ... 1100:
            tone(BUZZERPIN, HIGH_TONE, TONE_LENGTH);
            break;
        case 3000 ... 3100:
            tone(BUZZERPIN, HIGH_TONE, TONE_LENGTH);
            break;
        default:
        break;
    }
}

// Plays a sound when door is unlocked
void play_unlock(){
    tone(BUZZERPIN, LOW_TONE);
    delay(TONE_LENGTH); // A small delay is introduced for simplicity
    noTone(BUZZERPIN);
    tone(BUZZERPIN, HIGH_TONE, 2*TONE_LENGTH); // A Delay not needed, this continues in the background
}

//Plays a sound when door is locked
void play_lock(){
    tone(BUZZERPIN, HIGH_TONE);
    delay(TONE_LENGTH); // A small delay is introduced for simplicity
    noTone(BUZZERPIN);
    tone(BUZZERPIN, LOW_TONE, 2*TONE_LENGTH); // A Delay not needed, this continues in the background
}