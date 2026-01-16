/* @date 16-01-2026
 * @version 0.1
 * @par Revision history
 * | Version |    Date    | Description                                             |
 * |---------|------------|---------------------------------------------------------|
 * | 0.1     | 16-01-2026 | Create file                                             |
 *
 * @copyright Copyright (c) 2026
 * 
*/
// import headers
#include <Arduino.h>
#include <Servo.h>

// define the pins
const uint8_t servoControl = D2;   
bool locked = False;


// Mount the servo to take control from D2
servo.attach(servoControl);

void servoTurn(locked) {
  if (locked == True) {
    servo.write(90)
  }
  else if (locked == False) {
    servo.write(-90)
  }
}



