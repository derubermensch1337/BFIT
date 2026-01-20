
/**
 * @file measure_weight.cpp
 * @authors Amal Araweelo Almis
 * @brief  
 * @date 20-01-2026
 * @version 0.1
 * @par Revision history
 * | Version |    Date    | Description                       |
 * |---------|------------|-----------------------------------|
 * | 0.1     | 14-01-2026 | Create file                       |
 * |         |            |                                   |
 *
 * @copyright Copyright (c) 2026
 * 
*/
// #include <HX711_ADC.h>

// // ESP8266 safe pins
// const int HX711_dout = 4;  // D2
// const int HX711_sck  = 5;  // D1

// HX711_ADC LoadCell(HX711_dout, HX711_sck);

// void setup() {
//   Serial.begin(115200);
//   delay(300);

//   LoadCell.begin();
//   LoadCell.start(3000, true);     // settle + tare
//   LoadCell.setCalFactor(26.17);   // NEW calibration factor

//   // wait until tare is complete
//   while (!LoadCell.getTareStatus()) {
//     LoadCell.update();
//     delay(5);
//   }

//   Serial.println("READY");
// }

// void loop() {
//   if (LoadCell.update()) {
//     Serial.println(LoadCell.getData());
//     delay(200);
//   }

//   // manual tare
//   if (Serial.available()) {
//     if (Serial.read() == 't') {
//       LoadCell.tareNoDelay();
//     }
//   }
// }
