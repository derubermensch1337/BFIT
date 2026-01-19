/**
 * @file rfid_access.cpp
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
#include "rfid_access.h"

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
        case 'r':
            return CMD_REMOVE_USER;
            break;
        case 'c':
            return CMD_CONFIRM;
            break;
        case 'p':
            return CMD_PRINT;
            break;
        case 'n':
            // This might be unnecessary
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

// ====================== Add user ===================================
bool add_user (MFRC522 &rfid){
    if (userCount >= MAX_ROOMS) {
        Serial.println("Database full. Delete user before adding new one.");
        return false;
    }   

    int emptyIndex = find_empty_index(&users[0]);
    Serial.print("The index ");
    Serial.print(emptyIndex);
    Serial.println(" is unused:");
    print_single_user(&users[0], emptyIndex);
    Serial.println("");

    // Prompt user for their room number
    Serial.println("Enter room number: ");
    int roomNumber = read_integer();
    Serial.print("Room number received: ");
    Serial.println(roomNumber);

    // Prompt user to scan their RFID tag
    Serial.println("Scan your RFID tag.");
    byte uid[UID_LENGTH];
    
    // Read tag
    while(!read_RFID_tag(rfid, uid)){
        // wait for tag
    }
    Serial.print("Received tag: ");
    print_uid(&uid[0]);

    // Check if tag is already registered
    for (int i = 0; i < MAX_ROOMS; i++){
        if ( users[i].roomNumber>0 && compare_UID(uid, users[i].uid)){ // if match is found
            Serial.println("Tag already registered in database.");
            return false; // skip the rest of the code
        }
    }

    // Store new user
    for (int i = 0; i<UID_LENGTH;  i++){
        users[emptyIndex].uid[i]=uid[i]; // store the 4 bytes
    }
    users[emptyIndex].roomNumber = roomNumber; // add room number
    users[emptyIndex].balance = 0;

    Serial.println("Successfully added new user.");
    return true;
}

// ======================== CHECK IF SHOULD UNLOCK ================================
bool validate_rfid(MFRC522 myRFID){
    byte uid[UID_LENGTH];   //Maybe move to more global place?
    bool open = false;
    //If a tag can be read
    if(read_RFID_tag(myRFID, uid)){
        // Check if tag is registered
        for (int i = 0; i<userCount; i++){
            if (compare_UID(uid, users[i].uid)){ // if match is found
                open = true; //
            }
        }

    //Open door
    Serial.println("Door will be opened!");
    }

    return open;
}

// ======================== HELPER FUNCTIONS ================================

bool compare_UID (byte *uid1, byte *uid2){
    // Compares two uid tags and returns true if they are identical
    for (int i=0; i<UID_LENGTH;i++){
        if (uid1[i] != uid2[i]){
            return false;
        } 
    }
    return true; 
}

bool read_RFID_tag (MFRC522 &rfid, byte *uidBuffer){
    // Returns true if uid can be read, also saves the uid tag to array starting with *uidBuffer
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


void display_commands(){
    Serial.println("Available commands:\n\t-'a' to add a user.\n\t-'r' to remove users.");
}



