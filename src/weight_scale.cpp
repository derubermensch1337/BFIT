/**
 * @file weight_scale.cpp
 * @brief 
 * @author Amal Araweelo Almis
*/

#include "weight_scale.h"
HX711_ADC scale(HX711_DOUT, HX711_SCK);

static float g_referenceWeight = NAN;

float get_weight_reference(void){
    return g_referenceWeight;
}

void set_weight_reference(float value){
    g_referenceWeight = value;
}

void reset_weight_reference(void){
    g_referenceWeight = NAN;
}

bool weight_reference_is_set(void){
    return !isnan(g_referenceWeight);
}

void setup_scale(float calFactor)
{
    scale.begin();
    scale.start(SCALE_DEFAULT_SETTLE_TIME_MS, true);
    scale.setCalFactor(calFactor);

    const uint32_t timeoutMs = 8000;
    uint32_t startMs = millis();

    while(!scale.getTareStatus()){
        scale.update();
        delay(5);

        if (millis() - startMs > timeoutMs) {
            Serial.println("ERROR: HX711 tare timeout (check DT/SCK wiring and power)");
            break;
        }
    }

    if (scale.getTareStatus()) {
        Serial.println("HX711 tare complete");
    }
}

bool update_scale(
){
   return scale.update();
}

float get_weight(
){
   return scale.getData();
}

void tare_scale(
){
   return scale.tareNoDelay();
}

bool tare_complete(
){
   return scale.getTareStatus();
}

// Beer function
int get_beer_cans_taken(
   float referenceWeight,
   float currentWeight
){
   float diff = referenceWeight-currentWeight;
    Serial.print("reference: ");
    Serial.println(referenceWeight);
    Serial.print("current: ");
    Serial.println(currentWeight);


    Serial.print("diff: ");
    Serial.println(diff);


   // ignore small changes
   if (diff < SCALE_TOL){
      return 0;
   }

   // calculate number of cans removed
   int cans = (int) round(diff/BEER_WEIGHT);

   Serial.print("cans: ");
   Serial.println(cans);

   // error handling
   if (cans < 0) {
      cans = 0;
   }
   return cans;
}
