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
int userCount = 0;  // Not used?

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
        case 'l':
            return CMD_LOCK;
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

// ======================== CHECK IF SHOULD UNLOCK ================================
bool validate_rfid(MFRC522 &myRFID){
    byte uid[UID_LENGTH];   //Maybe move to more global place?
    bool open = false;
    //If a tag can be read
    if(read_RFID_tag(myRFID, uid)){
        // Check if tag is registered
        for (int i = 0; i<MAX_ROOMS; i++){
            if (compare_UID(uid, users[i].uid)){ // if match is found
                open = true; //
            }
        }
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
        //Serial.println("There is no RFID card present.");
        return false;
    }
    // Verify if the NUID has been read
    if (!rfid.PICC_ReadCardSerial()){
        //Serial.println("NUID has not been read.");
        return false;
    }
    for (byte i = 0; i < UID_LENGTH; i++) {
        uidBuffer[i] = rfid.uid.uidByte[i];
    }
    rfid.PICC_HaltA();
    yield();
    return true;
}


void display_commands(){
    Serial.println("Available commands:\n"
        " -'a' to add a user\n"
        " -'r' to remove users\n"
        " -'p' to print the array 'users'\n"
        " -'l' to lock the door");
}

void display_commands_um(){
    // For user management loop
    Serial.println("Available commands:\n"
        " -'a' to add a user\n"
        " -'r' to remove users\n"
        " -'p' to print the array 'users'\n"
        " -'c' to confirm changes");
}

// ====================== Add and delete users =====================================
// A while loop is used so multiple changes can be committed to EEPROM with one write
void user_management(RFIDcommand incomingCommand, User* ptr, MFRC522 &rfid){

  bool wasChanged = false;  // If something becomes added or deleted, EEPROM is written
  RFIDcommand localCmd = incomingCommand;

  while(localCmd != CMD_CONFIRM){
    switch(localCmd) {
      case CMD_ADD_USER:
        // Try to add new user
        Serial.println("Adding new user");

        if(add_user(rfid)){
          Serial.println("User added succesfully");
          wasChanged = true;
        } else {
          // If for example user count was full, or uid already in use
          Serial.println("Adding user failed.");
        }
        localCmd = CMD_NONE;
        display_commands_um();
        break;
      case CMD_REMOVE_USER:
        // Try to remove user
        if(remove_user()){
            Serial.println("User removed.");
            wasChanged = true;
        }else{
          // If
          Serial.println("Removing user failed.");
        }
        localCmd = CMD_NONE;
        display_commands_um();
        break;
      case CMD_PRINT:
        print_all_users(&users[0]);
        display_commands_um();
        break;
      case CMD_NONE:
      default:
        break;
    }

    localCmd = check_command();
  }

  if (wasChanged == true) {
    EEPROM.begin(sizeof(users));
    
    //Prepare to write users to EEPROM
    for (int i = 0; i < MAX_ROOMS; i++) {
      EEPROM.put(i*sizeof(User), users[i]);
    }
    
    // Actually modify EEPROM
    EEPROM.commit();
    Serial.println("Changes written to EEPROM.");


    //Print the updated database
    Serial.println("Database after modification:");
    print_all_users(ptr);

  } else {
    Serial.println("No changes were made.");
  }
}

// ====================== Add user ===================================
bool add_user (MFRC522 &rfid){
    if (userCount >= MAX_ROOMS) {
        Serial.println("Database full. Delete user before adding new one.");
        return false;
    }   

    int emptyIndex = find_empty_index(&users[0]);
    Serial.print("Index ");
    Serial.print(emptyIndex);
    Serial.println(" is empty:");
    print_single_user(&users[0], emptyIndex);
    Serial.println("");

    // Prompt user for their room number
    Serial.println("Enter room number: ");
    int roomNumber = read_integer();
    Serial.print("Room number received: ");
    Serial.println(roomNumber);

    if(roomNumber<=0){
        Serial.println("Room number must be positive");
        return false;
    }

    // Prompt user to scan their RFID tag
    Serial.println("Scan your RFID tag.");
    byte uid[UID_LENGTH];
    
    // Read tag
    while(!read_RFID_tag(rfid, uid)){
        yield();
        // wait for tag
    }
    Serial.print("Received tag: ");
    print_uid(&uid[0]);
    Serial.println("");

    // Check if tag is already registered
    for (int i = 0; i < MAX_ROOMS; i++){
        if ( users[i].roomNumber>0 && compare_UID(uid, users[i].uid)){ // if match is found
            Serial.print("Tag already registered in database in index ");
            Serial.println(i);
            return false; // skip the rest of the code
        }
    }

    // Store new user
    for (int i = 0; i<UID_LENGTH;  i++){
        users[emptyIndex].uid[i]=uid[i]; // store the 4 bytes
    }
    users[emptyIndex].roomNumber = roomNumber; // add room number
    users[emptyIndex].balance = 0;

    return true;
}

bool remove_user(){
    //Asks for index(es) to be deleted and sets their bytes to a defined 'null' value

  int idxToDelete = -1;     //Users are in database starting at index 0
  byte fillByte = 0;        //The byte to fill a deleted uid with

  Serial.println("which index to delete? Negative to cancel.");
  idxToDelete = read_integer();
  if (idxToDelete > 0) {
    Serial.println("Confirm the removal of following user:");
    print_single_user(&users[0], idxToDelete);
    Serial.println("");

    if(read_confirmation()){

      //Sets all bytes for one user uid to a specified 'null' value
      for (unsigned int i = 0; i < UID_LENGTH; i++) {
        users[idxToDelete].uid[i] = fillByte;
      }
      users[idxToDelete].roomNumber = -1;
      users[idxToDelete].balance = 0;

      return true;
    }
  }

  Serial.println("Removal cancelled");
  return false;
}

void get_users_db(User* ptr) {
// Fetches users from database and writes them to users[]

  EEPROM.begin(sizeof(users));

  for (int i = 0; i < MAX_ROOMS; i++) {
    //get uid
    for (int j = 0; j < UID_LENGTH; j++) {
      EEPROM.get(i * sizeof(User) + j, (*(ptr + i)).uid[j]);
    }
    //get other data
    EEPROM.get(i * sizeof(User) + 4, (*(ptr + i)).roomNumber);
    EEPROM.get(i * sizeof(User) + 8, (*(ptr + i)).balance);
  }

  // Count and display number of users
  userCount = count_rooms(ptr);
  Serial.print(userCount);
  Serial.println(" rooms are currently in use.");

  // Display the array users[]
  Serial.println("The following users have been loaded from the database:");
  print_all_users(ptr);
}

// ====================== Print users and UID =====================================

// Prints the users currently at the users array as rows
void print_all_users(User* ptr) {


  for (int i = 0; i < MAX_ROOMS; i++) {
    print_single_user(ptr, i);
    Serial.println("");
  }
    Serial.println("");

}

// ptr is pointer to the users[] array, idx is the index to print
void print_single_user(User* ptr, int idx) {

  User * offsetPointer = ptr + idx;
  byte* bytePointer = &((*offsetPointer).uid[0]);

  // Doesn't print newline
    Serial.print("index: ");
    Serial.print(idx);
    Serial.print('\t');

    Serial.print("Room:  ");
    Serial.print((*offsetPointer).roomNumber);
    Serial.print('\t');

    Serial.print("uid: ");
    print_uid(bytePointer);
    Serial.print('\t');

    Serial.print("balance: ");
    Serial.print((*offsetPointer).balance);
}

//Currently prints decimal, pointer to the first member of uid array we want to print
void print_uid(byte* ptr) {
  //Pads number with spaces to 3 chars
  byte myByte = 0;
  for (int i = 0; i < UID_LENGTH; i++) {
    myByte = *(ptr + i);

    //Whitespace padding
    if (myByte < 10) {
      Serial.print("  ");
    } else if (myByte < 100) {
      Serial.print(" ");
    }

    Serial.print(myByte);
    Serial.print(" ");
  }
}

// ====================== Helper functions =====================================

// Reads a nonzero integer from serial and asks for confirmation, returns the integer 
int read_integer() {

  int myInteger = 0;  //Chars converted to string

  Serial.println("Please insert an integer ");

  while (myInteger == 0) {
    myInteger = Serial.parseInt();  //returns 0 after 1 second (=goes to top of while)
    if (myInteger != 0) {           // If integer is not returned, goes to previous line

      //Print the received number
      Serial.print("Received number: ");
      Serial.println(myInteger);

      //Ask for confirmation to avoid unexpected chars from the buffer
      if(read_confirmation()) {
        break;
      } else {
        //Go back to top of while loop
        Serial.println("Rejected number. Insert an integer ");
        myInteger = 0;
      }
    }
  } return myInteger;
}

//Ask user to press y for confirmation, returns true if y is written to serial
bool read_confirmation() {
  Serial.print("Confirm with 'y': ");
  while (Serial.available() == 0) {
    //Wait until there is input
    // Maybe a timeout would be necessary here?
  }
  if (Serial.read() == 'y') {
    return true;
  } else {
    return false;
  }
}

//Returns the first index for a room with 0 or negative room number
int find_empty_index(User* ptr) {
  //returns -1 if all are full
  int foundIndex = -1;
  int numRoom = 0; //Temporary storage for number of the room

  for (int i = 0; i < MAX_ROOMS; i++) {
    //Use pointer arithmetic, get the user at location, access roomNumber via dot notation
    numRoom = (*(ptr + i)).roomNumber;
    //Serial.println(numRoom); //For debugging
    if (numRoom <= 0) {
      foundIndex = i;

      break; //escape for
    }
  }
  return foundIndex;
}

// Counts the number of rooms in users[] with valid numbers
int count_rooms(User* ptr) {
    // Meaning, how many spots are taken
  int counter = 0;
  int numRoom = 0; //Temporary storage for number of the room

  for (int i = 0; i < MAX_ROOMS; i++) {
    //Use pointer arithmetic, get the user at location, access roomNumber via dot notation
    numRoom = (*(ptr + i)).roomNumber;
    //Serial.println(numRoom); //For debugging
    if (numRoom > 0) {
      counter++;
    }
  }
  return counter;
}

// For debugging
void print_status(bool doorClosed, bool doorUnlocked, RFIDcommand cmd){
    //Serial.println(millis());
    int mod = millis()%1000;
    //Serial.println(mod);

    if(mod <= 36){

        Serial.print("Door open status: ");
        if (doorClosed){
            Serial.println("closed");
        } else{
            Serial.println("open");
        }

        Serial.print("Door lock status: ");
        if (doorUnlocked){
            Serial.println("unlocked");
        } else{
            Serial.println("locked");
        }

        Serial.print("Current command: ");
        Serial.println(cmd);
        Serial.println("");
    }
}



