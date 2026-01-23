/**
 * @file rfid_access.h
 * @brief 
 * @author Amal Araweelo Almis
 * @author Baldur G. Toftegaard
 */

#ifndef RFID_ACCESS_H
#define RFID_ACCESS_H  

#include <SPI.h>
#include <MFRC522.h>

// Pins
#define SS_PIN 15 // Use GPIO pins for HUZZAH instead of D8
#define RST_PIN 0 // Instead of D3

// Constants
#define MAX_ROOMS 17
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
 * @param rfid 
*/
void setup_RFID_reader(
    MFRC522 &rfid
);

/**
 * @brief Adds a new user by reading room number and scanning an RFID tag.
 * 
 * @param rfid 
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
 * @brief 
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
 * @brief 
 * 
 * @param rfid 
 * @param uidBuffer 
 * @return true 
 * @return false 
*/
bool read_RFID_tag(
    MFRC522 &rfid, 
    byte *uidBuffer
);

/**
 * @brief 
*/
void display_commands(
    void
);

/**
 * @brief 
*/
void display_commands_um(
);

/**
 * @brief Get the users db object
 * 
 * @param ptr 
*/
void get_users_db(
    User* ptr
);

/**
 * @brief 
 * 
 * @param cmd 
 * @param ptr 
 * @param rfid 
*/
void user_management(
    RFIDcommand cmd, 
    User* ptr, 
    MFRC522 &rfid
);

/**
 * @brief 
 * 
 * @param myRFID 
 * @return true 
 * @return false 
*/
bool validate_rfid(
    MFRC522 myRFID
);

/**
 * @brief 
 * 
 * @param ptr 
 * @param idx 
*/
void print_single_user(
    User* ptr, 
    int idx
);
/**
 * @brief 
 * 
 * @param ptr 
*/
void print_all_users(
    User* ptr
);

/**
 * @brief 
 * 
 * @param ptr 
*/
void print_uid(
    byte* ptr
);

/**
 * @brief 
 * 
 * @return int 
*/
int read_integer(
);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
*/
bool read_confirmation(
);

/**
 * @brief 
 * 
 * @param ptr 
 * @return int 
*/
int find_empty_index(
    User* ptr
);

/**
 * @brief 
 * 
 * @param ptr 
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
