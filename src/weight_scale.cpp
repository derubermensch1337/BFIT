/**
 * @file weight_scale.cpp
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

 #include "weight_scale.h"

 // Global HX711 obj
 HX711_ADC scale(HX711_DOUT, HX711_SCK);

 void setup_scale(float calFactor){
    scale.begin();
    scale.start(SCALE_DEFAULT_SETTLE_TIME_MS, true); // settling + tare
    scale.setCalFactor(calFactor);

    // wait until tare is complete
    while(!scale.getTareStatus()){
        scale.update();
        delay(5);
    }
 }

 bool update_scale(){
    return scale.update();
 }

 float get_weight(){
    return scale.getData();
 }

 void tare_scale(){
    return scale.tareNoDelay();
 }

 bool tare_complete(){
    return scale.getTareStatus();
 }

 // Beer function
 int get_beer_cans_taken(float referenceWeight,float currentWeight){
    float diff = referenceWeight-currentWeight;

    // ignore small changes
    if (diff < SCALE_TOL){
        return 0;
    }

    // calculate number of cans removed
    int cans = (int) round(diff/BEER_WEIGHT);

    // error handling
    if (cans < 0) {
        cans = 0;
    }

    return cans;
 }