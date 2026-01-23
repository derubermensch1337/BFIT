/**
 * @file rfid_access.h
 * @brief Declare functions related to RFID reading and user database
 * @author Amal Araweelo Almis
 * @author Baldur G. Toftegaard
 * @author Anssi Sohlman
 */

#ifndef RFID_ACCESS_H
#define RFID_ACCESS_H  

#include <SPI.h>
#include <MFRC522.h>

// Pins
/** GPIO pin connected to SS */
#define SS_PIN 15 // Use GPIO pins for HUZZAH instead of D8

/** GPIO pin connected to RST */
#define RST_PIN 0 // Instead of D3

// Constants
/** Maximum number of rooms supported by the system */
#define MAX_ROOMS 17

/** Length of an RFID UID in bytes */
#define UID_LENGTH 4

/**
 * @brief Supported serial commands for the RFID management interface.
*/
enum RFIDcommand {
    CMD_NONE,
    CMD_ADD_USER,
    CMD_OPEN,
    CMD_LOCK,
    CMD_REMOVE_USER,
    CMD_CONFIRM,
    CMD_PRINT
};

/**
* @brief User record stored in the RFID user database.
*/
struct User {
    byte uid[UID_LENGTH];
    int roomNumber;
    int balance; 
};

/**
 * @brief Global user database array.
*/
extern User users[MAX_ROOMS];

/**
 * @brief Number of currently registered users.
*/
extern int userCount;

/**
 * @brief brief Reads a command from the serial interface and maps it to an RFIDcommand.
 * 
 * @return RFIDcommand 
*/
RFIDcommand check_command(
    void
);

/**
 * @brief Initializes SPI and the MFRC522 RFID reader.
 * 
 * @param rfid An instance of a MFRC522 object
*/
void setup_RFID_reader(
    MFRC522 &rfid
);

/**
 * @brief Adds a new user by reading room number and scanning an RFID tag.
 * 
 * @param rfid An instance of a MFRC522 object
 * @return true 
 * @return false 
*/
bool add_user(
    MFRC522 &rfid
);

/**
 * @brief Removes a user from the database.
 * 
 * @return true 
 * @return false 
*/
bool remove_user(
);

/**
 * @brief Compares two RFID UIDs.
 * 
 * @param uid1 
 * @param uid2 
 * @return true 
 * @return false 
*/
bool compare_UID(
    byte *uid1, 
    byte *uid2
);

/**
 * @brief Reads an RFID tag UID from the MFRC522 reader.
 * 
 * @param rfid An instance of a MFRC522 object
 * @param uidBuffer An array where the UID is saved to
 * @return true 
 * @return false 
*/
bool read_RFID_tag(
    MFRC522 &rfid, 
    byte *uidBuffer
);

/**
 * @brief Prints the available serial commands.
*/
void display_commands(
    void
);

/**
 * @brief Prints the available serial commands for user-management mode. 
*/
void display_commands_um(
);

/**
 * @brief Copies the current user database to a provided buffer.
 * 
 * @param ptr A pointer to the users[] array
*/
void get_users_db(
    User* ptr
);

/**
 * @brief Executes user-management actions based on the provided command.
 * 
 * @param cmd The current RFIDcommand (add or remove user)
 * @param ptr A pointer to the users[] array
 * @param rfid An instance of a MFRC522 object
*/
void user_management(
    RFIDcommand cmd, 
    User* ptr, 
    MFRC522 &rfid
);

/**
 * @brief Validates an RFID tag against the registered user database.
 * 
 * @param myRFID An instance of a MFRC522 object
 * @return true 
 * @return false 
*/
bool validate_rfid(
    MFRC522 myRFID
);

/**
 * @brief brief Prints a single user entry to the serial interface.
 * 
 * @param ptr A pointer to the users[] array
 * @param idx The index to be printed
*/
void print_single_user(
    User* ptr, 
    int idx
);

/**
 * @brief Prints all users in the database to the serial interface. 
 * 
 * @param ptr A pointer to the users[] array
*/
void print_all_users(
    User* ptr
);

/**
 * @brief Prints a UID buffer to the serial interface.
 * 
 * @param ptr A pointer to member of the users[] array
*/
void print_uid(
    byte* ptr
);

/**
 * @brief Reads an integer from the serial interface.
 * 
 * @return int 
*/
int read_integer(
);

/**
 * @brief Reads a confirmation input from the serial interface.
 * 
 * @return true 
 * @return false 
*/
bool read_confirmation(
);

/**
 * @brief brief Finds an empty slot in the user database.
 * 
 * @param ptr A pointer to the users[] array
 * @return int 
*/
int find_empty_index(
    User* ptr
);

/**
 * @brief brief Counts the number of occupied user entries in the database.
 * 
 * @param ptr A pointer to the users[] array
 * @return int 
*/
int count_rooms(
    User* ptr
);

/**
 * @brief Function for storing the last used RFID
 * @param uidOut 
 * @return true 
 * @return false 
*/
void rfid_set_last_uid(
    const byte *uidIn
);

/**
 * @brief Function for restoring the last used RFID
 * @param uidOut 
 * @return true 
 * @return false 
*/
bool rfid_get_last_uid( 
    byte *uidOut
);


#endif
