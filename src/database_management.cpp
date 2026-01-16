/**
 * @file database_management.cpp
 * @authors Anssi Sohlman,
 * @brief Used to read and write non-volatile memory on ESP8266 
 * @date 16-01-2026
 * @version 0.1
 * @par Revision history
 * | Version |    Date    | Description                       |
 * |---------|------------|-----------------------------------|
 * | 0.1     | 16-01-2026 | Initial version                   |                               |
 * 
 * @copyright Copyright (c) 2026
 * 
*/

#include "rfid/rfid_unlock.h"


void add_user_db(){

}

void delete_user_db(){
    
}

void get_users_db(User* ptr) {

  EEPROM.begin(sizeof(users));

  for (int i = 0; i < MAX_ROOMS; i++) {
    for (int j = 0; j < UID_LENGTH; j++) {
      EEPROM.get(i * sizeof(User) + j, (*(ptr + i)).uid[j]);
    }
    EEPROM.get(i * sizeof(User) + 4, (*(ptr + i)).roomNumber);
    EEPROM.get(i * sizeof(User) + 8, (*(ptr + i)).balance);
  }

  print_users_db(ptr);
}

void print_users_db(User* ptr) {

  for (int i = 0; i < MAX_ROOMS; i++) {
    Serial.print("index: ");
    Serial.println(i);
    Serial.print("Room number: ");
    Serial.println((*(ptr + i)).roomNumber);
    Serial.print("uid: ");
    Serial.print((*(ptr + i)).uid[0]);
    Serial.print(" ");
    Serial.print((*(ptr + i)).uid[1]);
    Serial.print(" ");
    Serial.print((*(ptr + i)).uid[2]);
    Serial.print(" ");
    Serial.println((*(ptr + i)).uid[3]);
    Serial.print("balance: ");
    Serial.println((*(ptr + i)).balance);
    Serial.println("");
  }
}