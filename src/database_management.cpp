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
    Serial.print(i);
    Serial.print('\t');

    Serial.print("Room:  ");
    Serial.print((*(ptr + i)).roomNumber);
    Serial.print('\t');

    Serial.print("uid: ");
    print_uid(ptr + i);
    Serial.print('\t');

    Serial.print("balance: ");
    Serial.print((*(ptr + i)).balance);
    Serial.println("");
  }
}

void print_uid(User* ptr) {
  //Currently prints decimal
  //Pads number with spaces to 3 chars
  //Pointer to the user whose uid we want to print
  byte myByte = 0;
  for (int i = 0; i < UID_LENGTH; i++) {
    myByte = (*ptr).uid[i];
    if (myByte < 10) {
      Serial.print("  ");
    } else if (myByte < 100) {
      Serial.print(" ");
    }
    Serial.print(myByte);
    Serial.print(" ");
  }
}

int read_integer() {

  int myInteger = 0;  //Chars converted to string

  Serial.println("Please insert an integer ");

  while (myInteger == 0) {
    myInteger = Serial.parseInt();  //returns 0 after 1 second
    if (myInteger != 0) {           // If integer is not returned, goes to previous line

      //Print the received number
      Serial.print("Received number: ");
      Serial.println(myInteger);

      //Ask for confirmation to avoid unexpected chars from the buffer
      Serial.print("Confirm with 'y': ");
      while (Serial.available() == 0) {
        //Wait until there is input
        // Maybe a timeout would be necessary here?
      }
      if (Serial.read() == 'y') {
        break;  //Breaks out of the while loop and confirm integer
      } else {
        //Go back to top of while loop
        Serial.println("Rejected number. Insert an integer ");
        myInteger = 0;
      }
    }
  }

  Serial.print("Confirmed number: ");
  Serial.println(myInteger);
  return myInteger;
}