/**
 * @file weight_scale.h
 * @authors Amal Araweelo Almis
 * @brief 
 * @version 0.1
 * @date 20-01-2026
 * @par Revision history
 * | Version |    Date    | Description                                                             |
 * |---------|------------|-------------------------------------------------------------------------|
 * | 0.1     | 20-01-2026 | Created file.                                                           |
 * |         |            |                                                                         |
 * 
 * @copyright Copyright (c) 2026
 */
#ifndef WEIGHT_SCALE_H
#define WEIGHT_SCALE_H  

#include <Arduino.h>
#include <HX711_ADC.h>
#include <math.h> 

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

// General functions
void setup_scale(float calFactor);
bool update_scale(void);
float get_weight(void);
void tare_scale(void);
bool tare_complete(void);

// Beer function
int get_beer_cans_taken(float referencWeight,float currentWeight);

#endif