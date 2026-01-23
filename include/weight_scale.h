/**
 * @file weight_scale.h
 * @author Amal Araweelo Almis
 * @author Baldur G. Toftegaard
 */
#ifndef WEIGHT_SCALE_H
#define WEIGHT_SCALE_H  

#include <Arduino.h>
#include <HX711_ADC.h>
#include <math.h> 

float get_weight_reference(void);
void  set_weight_reference(float value);
void  reset_weight_reference(void);
bool  weight_reference_is_set(void);

// Constants
#define BEER_WEIGHT 350
#define SCALE_TOL 25 // this is an assumption

// Pins
#define HX711_DOUT 4   // GPIO4=D2
#define HX711_SCK  5   // GPIO5=D1

// Config scale
#define SCALE_DEFAULT_SETTLE_TIME_MS 3000

// Globals
extern HX711_ADC scale;

/**
 * @brief set up the action (input) the rfid_user_id_lattest takes
 */
enum weight_recall_action {
    weight_change_store,
    weight_change_recall
};

// General functions
void setup_scale(float calFactor);
bool update_scale(void);
float get_weight(void);
void tare_scale(void);
bool tare_complete(void);

// Beer function
int get_beer_cans_taken(float referencWeight,float currentWeight);

#endif