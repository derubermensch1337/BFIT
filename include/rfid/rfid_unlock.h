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

// Libraries
#include <SPI.h>
#include <MFRC522.h>

// Pins
#define SS_PIN D8
#define RST_PIN D3

// Constants
#define MAX_ROOMS = 17
#define UID_LENGTH = 4 // 4 bytes is standard

// Commands
// todo: add usr command, like press 'a'


// User struct containing room number and UID
struct User {
    byte uid[UID_LENGTH];
    int roomNumber;
}

// Create all users
User users[MAX_ROOMS];
int userCount = 0;

// ====================== Command


// ====================== Setup RFID reader =================================
void setup_RFID_reader(){
    SPI.begin();
    rfid.PCD_init();
    Serial.println("RFID system ready.");
}

// ====================== Add room number ===================================
void add_user (){
    if (userCount >= MAX_ROOMS) {
        Serial.println("Database full.");
        return;
    }   

    // Prompt user for their room number
    Serial.println("Enter room number: ");
    while(!Serial.available()){

    };

    // Parse room number
    int roomNumber = Serial.parseInt();
    Serial.print("Room number received: ")
    Serial.println(roomNumber);

    // Prompt user to scan their RFID tag
    Serial.println("Scan your RFID tag.")
    byte uid[UID_LENGTH];
    
    // Read tag
    while(!read_RFID_tag(rfid, uid)){
        // wait for tag
    }

    // Check if tag is already registered
    for (int i = 0; i++; i<userCount){
        if (compare_UID(uid, users[i].uid)){ // if match is found
            Serial.println("Tag already registered in database.");
            return; // skip the rest of the code
        }
    }

    // Store new user
    for (int i = 0; i++; i<UID_LENGTH){
        users[userCount].uid[i]=uid[i]; // store the 4 bytes
    }
    users[userCount].roomNumber = roomNumber; // add room number
    userCount++;

    Serial.println("Successfully added new user.");
}

/* Helper functions 
    compare_UID
    read_RFID_tag
*/ 

// Compares two uid tags and returns true if they are identical
bool compare_UID (byte *uid1, byte *uid2){
    for (int i=0; i<UID_LENGTH;i++){
        if (uid1[i] != uid2[i]){
            return false;
        } 
    }
    return true; 
}

 // Read RFID tag (mostly copied from X's github)
 bool read_RFID_tag (MFRC522 &rfid, byte *uidBuffer){

    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if (!rfid.PICC_IsNewCardPresent()){
        return;
    }

    // Verify if the NUID has been read
    if (!rfid.PICC_ReadCardSerial()){
        return;
    }

    for (byte i = 0; i < UID_LENGTH; i++) {
        uidBuffer[i] = rfid.uid.uidByte[i];
    }

    rfid.PICC_HaltA();
    return true;
 }

#endif 