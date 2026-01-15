/**
 * @file rfid_unlock.h
 * @authors Amal Araweelo Almis
 * @brief 
 * @version 0.1
 * @date 15-01-2026
 * @par Revision history
 * | Version |    Date    | Description                                                             |
 * |---------|------------|-------------------------------------------------------------------------|
 * | 0.1     | 13-01-2026 | Created file.                                                           |
 * |         |            |                                                                         |
 * 
 * @copyright Copyright (c) 2026
 */

#ifndef RFID_UNLOCK_H
#define RFID_UNLOCK_H  

#include <SPI.h>
#include <MFRC522.h>

#define MAX_ROOMS = 17
#define UID_LENGTH = 4 // 4 bytes

// User struct containing room number and UID
struct User {
    byte uid[UID_LENGHT];
    int roomNumber;
}

// Create all users
User user[MAX_ROOMS];
int userCount = 0;


// Add room number 
void add_new_room_number (){
    if (userCount >= MAX_ROOMS) {
        Serial.println("Database full.");
        return;
    }   

    // prompt user for their room number


    // read tag

    // check if it already exists by comparing UIDs

        // if it does, print "already in database"
        // if not, add to database and print something like "resident added"

}



// Helper functions
// Compares two uid tags and returns true if they are identical
bool compare_UID (byte *uid1, byte *uid2){
    for (int i=0; i<UID_LENGTH;i++){
        if (uid1[i] != uid2[i]){
            return false;
        } 
    }
    return true; 
}


#endif 