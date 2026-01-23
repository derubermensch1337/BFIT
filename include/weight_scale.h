/**
 * @file weight_scale.h
 * @author Amal Araweelo Almis
 */
#ifndef WEIGHT_SCALE_H
#define WEIGHT_SCALE_H  

#include <Arduino.h>
#include <HX711_ADC.h>
#include <math.h> 

/**
 * @brief FUnction to get the weight reference.
 * 
 * @return float 
*/
float get_weight_reference(
    void
);

/**
 * @brief Function to set the weight reference.
 * 
 * @param value 
*/
void  set_weight_reference(
    float value
);

/**
 * @brief Function to reset the weight reference.
*/
void  reset_weight_reference(
    void
);

/**
 * @brief Function to send cinfirmation that the weight reference is set.
 * 
 * @return true 
 * @return false 
 */
bool  weight_reference_is_set(
    void
);

/**
 * @brief Define the weight of a beer.
*/
#define BEER_WEIGHT 350

/**
 * @brief Define the error of the weight mesurment.
*/
#define SCALE_TOL 25

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

/**
 * @brief Function to seting up the scale, is called in the begining of the program.
 * 
 * @param calFactor 
 */
void setup_scale(
    float calFactor
);

/**
 * @brief Function for updating the scale value.
 * 
 * @return true 
 * @return false 
 */
bool update_scale(
    void
);

/**
 * @brief Function to get the scale reading.
 * 
 * @return float 
 */
float get_weight(
    void
);

/**
 * @brief Function to tar the scale
*/
void tare_scale(
    void
);

/**
 * @brief Function to signal that the scale has been tarted.
 * 
 * @return true 
 * @return false 
*/
bool tare_complete(
    void
);

/**
 * @brief Function to get the number of beer cans taken.
 * 
 * @param referencWeight 
 * @param currentWeight 
 * @return int 
 */
int get_beer_cans_taken(
    float referencWeight,
    float currentWeight
);

#endif