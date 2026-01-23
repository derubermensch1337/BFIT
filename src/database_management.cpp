/**
 * @file database_management.cpp
 * @authors Anssi Sohlman,
 * @brief Functions for user management and read/write of non-volatile memory on ESP8266 
 * 
*/

/* 
 * Notes on EEPROM:
 * The non-volatile memory of ESP8266 has limited writes (about 10k) and unlimited reads. 
 * 1 write can be saving multiple things. From what I can tell wearing it out doesn’t break other parts of the board, 
 * but it’s probably a good idea to be mindful of writes. I propose the following:
 * 
 * - Write to EEPROM only when needed, not repeatedly in a loop
 * - User id and room number are stored in EEPROM with balance of 0. These rarely need to be changed.
 * - When device is reset, load data from EEPROM to users[]
 * - Discard balance changes when power is reset, don't save to EEPROM (or have a specific command to bulk save if needed for testing)
 * 
 * Editing users:
 * - Add/delete users to/from users[] array
 * - When done, write users[] to EEPROM
 * 
 * Use commands from EEPROM.h library
*/

#include "rfid_access.h"
#include <EEPROM.h>

// ====================== Add and delete users =====================================
// A while loop is used so multiple changes can be committed to EEPROM with one write
void user_management(RFIDcommand incomingCommand, User* ptr, MFRC522 &rfid){

  bool wasChanged = false;  // If something becomes added or deleted, EEPROM is written
  RFIDcommand localCmd = incomingCommand;

  while(localCmd != CMD_CONFIRM){
    switch(localCmd) {
      case CMD_ADD_USER:
        // Try to add new user
        if(add_user(rfid)){
          Serial.println("User added succesfully.");
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

bool remove_user(){
    //Asks for index(es) to be deleted and sets their bytes to a defined 'null' value

  int idxToDelete = -1;     //Users are in database starting at index 0
  byte fillByte = 0;        //The byte to fill a deleted uid with

  Serial.println("which index to delete? Negative to cancel.");
  idxToDelete = read_integer();
  if (idxToDelete > 0) {
    Serial.println("Confirm the removal of following user:");
    print_single_user(&users[0], idxToDelete);
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
//Ask user to press y for confirmation
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


int find_empty_index(User* ptr) {
//Returns the first index for a room with 0 or negative room number
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

int count_rooms(User* ptr) {
    // Counts the number of rooms in users[] with valid numbers
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