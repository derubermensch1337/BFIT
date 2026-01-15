/**
 * @file rfid_unlock.cpp
 * @authors Amal Araweelo Almis
 * @brief 
 * @version 0.1
 * @date 15-01-2026
 * @par Revision history
 * | Version |    Date    | Description                                                             |
 * |---------|------------|-------------------------------------------------------------------------|
 * | 0.1     | 15-01-2026 | Created file.                                                           |
 * |         |            |                                                                         |
 * 
 * @copyright Copyright (c) 2026
 */
#include "rfid/rfid_unlock.h"

// Definitions
User users[MAX_ROOMS];
int userCount = 0;

// ====================== Check command =====================================
RFIDcommand check_command(){
    if (!Serial.available()){
        return CMD_NONE;
    };

    char cmd = Serial.read(); // Read keyboard character pressed

    switch (cmd) {
        case 'a':
            return CMD_ADD_USER; 
            break;
        case 'n':
            return CMD_NONE;
            break;
        default:
            return CMD_NONE;
            break;
    }

}

// ====================== Setup RFID reader =================================

void setup_RFID_reader(MFRC522 &rfid){
    SPI.begin();
    rfid.PCD_Init();
    Serial.println("RFID system ready.");
}

// ====================== Add room number ===================================
void add_user (MFRC522 &rfid){
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
    Serial.print("Room number received: ");
    Serial.println(roomNumber);

    // Prompt user to scan their RFID tag
    Serial.println("Scan your RFID tag.");
    byte uid[UID_LENGTH];
    
    // Read tag
    while(!read_RFID_tag(rfid, uid)){
        // wait for tag
    }

    // Check if tag is already registered
    for (int i = 0; i<userCount; i++){
        if (compare_UID(uid, users[i].uid)){ // if match is found
            Serial.println("Tag already registered in database.");
            return; // skip the rest of the code
        }
    }

    // Store new user
    for (int i = 0; i<UID_LENGTH;  i++){
        users[userCount].uid[i]=uid[i]; // store the 4 bytes
    }
    users[userCount].roomNumber = roomNumber; // add room number
    userCount++;

    Serial.println("Successfully added new user.");
}

// ======================== HELPER FUNCTIONS ================================

// Compares two uid tags and returns true if they are identical
bool compare_UID (byte *uid1, byte *uid2){
    for (int i=0; i<UID_LENGTH;i++){
        if (uid1[i] != uid2[i]){
            return false;
        } 
    }
    return true; 
}

bool read_RFID_tag (MFRC522 &rfid, byte *uidBuffer){
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if (!rfid.PICC_IsNewCardPresent()){
        return false;
    }
    // Verify if the NUID has been read
    if (!rfid.PICC_ReadCardSerial()){
        return false;
    }
    for (byte i = 0; i < UID_LENGTH; i++) {
        uidBuffer[i] = rfid.uid.uidByte[i];
    }
    rfid.PICC_HaltA();
    return true;
}

