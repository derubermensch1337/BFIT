// /**
//  * @file database_management.cpp
//  * @authors Anssi Sohlman,
//  * @brief Used to read and write non-volatile memory on ESP8266 
//  * @date 16-01-2026
//  * @version 0.1
//  * @par Revision history
//  * | Version |    Date    | Description                       |
//  * |---------|------------|-----------------------------------|
//  * | 0.1     | 16-01-2026 | Initial version                   |                               |
//  * 
//  * @copyright Copyright (c) 2026
//  * 
// */

// //Is this needed here?
// #include "rfid/rfid_unlock.h"


// void add_user_db(){
// }

// void delete_user_db(){
//     //Asks for index(es) to be deleted and sets their bytes to a defined 'null' value

//   EEPROM.begin(sizeof(users));

//   int idxToDelete = -1;     //Users are in database starting at index 0
//   byte fillByte = 0;        //The byte to fill a deleted user
//   bool wasChanged = false;  //If something becomes deleted

//   do {
//     Serial.println("which index to delete? Negative to cancel.");
//     idxToDelete = read_integer();
//     if (idxToDelete > 0) {

//       //Sets all bytes for one user to a specified 'null' value
//       for (int i = 0; i < sizeof(User); i++) {
//         EEPROM.write(idxToDelete * sizeof(User) + i, fillByte);
//       }

//       wasChanged = true;
//       Serial.print(idxToDelete);
//       Serial.println(" is set for deletion. Delete another index? Negative to continue.");
//     }
//   } while (idxToDelete > 0);  //If one is deleted, another can be as well

//   // Only commit if changes have been made to save flash memory
//   if (wasChanged == true) {
//     EEPROM.commit();
//   }

//   //Get and print the updated database
//   Serial.println("Database after deletion:");
//   get_users_db(&users[0]);
// }

// void get_users_db(User* ptr) {

//   EEPROM.begin(sizeof(users));

//   for (int i = 0; i < MAX_ROOMS; i++) {
//     for (int j = 0; j < UID_LENGTH; j++) {
//       EEPROM.get(i * sizeof(User) + j, (*(ptr + i)).uid[j]);
//     }
//     EEPROM.get(i * sizeof(User) + 4, (*(ptr + i)).roomNumber);
//     EEPROM.get(i * sizeof(User) + 8, (*(ptr + i)).balance);
//   }

//   print_users_db(ptr);
// }

// void print_users_db(User* ptr) {

//   for (int i = 0; i < MAX_ROOMS; i++) {
//     Serial.print("index: ");
//     Serial.print(i);
//     Serial.print('\t');

//     Serial.print("Room:  ");
//     Serial.print((*(ptr + i)).roomNumber);
//     Serial.print('\t');

//     Serial.print("uid: ");
//     print_uid(ptr + i);
//     Serial.print('\t');

//     Serial.print("balance: ");
//     Serial.print((*(ptr + i)).balance);
//     Serial.println("");
//   }
// }

// void print_uid(User* ptr) {
//   //Currently prints decimal
//   //Pads number with spaces to 3 chars
//   //Pointer to the user whose uid we want to print
//   byte myByte = 0;
//   for (int i = 0; i < UID_LENGTH; i++) {
//     myByte = (*ptr).uid[i];
//     if (myByte < 10) {
//       Serial.print("  ");
//     } else if (myByte < 100) {
//       Serial.print(" ");
//     }
//     Serial.print(myByte);
//     Serial.print(" ");
//   }
// }

// int read_integer() {

//   int myInteger = 0;  //Chars converted to string

//   Serial.println("Please insert an integer ");

//   while (myInteger == 0) {
//     myInteger = Serial.parseInt();  //returns 0 after 1 second
//     if (myInteger != 0) {           // If integer is not returned, goes to previous line

//       //Print the received number
//       Serial.print("Received number: ");
//       Serial.println(myInteger);

//       //Ask for confirmation to avoid unexpected chars from the buffer
//       Serial.print("Confirm with 'y': ");
//       while (Serial.available() == 0) {
//         //Wait until there is input
//         // Maybe a timeout would be necessary here?
//       }
//       if (Serial.read() == 'y') {
//         break;  //Breaks out of the while loop and confirm integer
//       } else {
//         //Go back to top of while loop
//         Serial.println("Rejected number. Insert an integer ");
//         myInteger = 0;
//       }
//     }
//   }

//   Serial.print("Confirmed number: ");
//   Serial.println(myInteger);
//   return myInteger;
// }

// int find_empty_index(User* ptr) {
//   //returns -1 if all are full
//   int foundIndex = -1;
//   int numRoom = 0;
//   for (int i = 0; i < MAX_ROOMS; i++) {
//     numRoom = (*(ptr + i)).roomNumber;
//     //Serial.println(numRoom);
//     if (numRoom <= 0) {
//       foundIndex = i;
//       break;
//     }
//   }
//   return foundIndex;
// }

// int count_rooms(User* ptr) {
//   int counter = 0;
//   int numRoom = 0;

//   for (int i = 0; i < MAX_ROOMS; i++) {
//     numRoom = (*(ptr + i)).roomNumber;
//     //Serial.println(numRoom);
//     if (numRoom > 0) {
//       counter++;
//     }
//   }
//   return counter;
// }