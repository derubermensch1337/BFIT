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

// Commands
enum RFIDcommand {
    CMD_NONE,
    CMD_ADD_USER,
    CMD_OPEN,
    CMD_LOCK,
    CMD_REMOVE_USER,
    CMD_CONFIRM,
    CMD_PRINT
};

// User struct
struct User {
    byte uid[UID_LENGTH];
    int roomNumber;
    int balance; 
};

// Extern globals declared
extern User users[MAX_ROOMS];
extern int userCount;

// Function declarations
RFIDcommand check_command(void);
void setup_RFID_reader(MFRC522 &rfid);
bool add_user(MFRC522 &rfid);
bool remove_user();
bool compare_UID(byte *uid1, byte *uid2);
bool read_RFID_tag(MFRC522 &rfid, byte *uidBuffer);
void display_commands(void);
void display_commands_um();


//Anssi
void get_users_db(User* ptr);
void user_management(RFIDcommand cmd, User* ptr, MFRC522 &rfid);
bool validate_rfid(MFRC522 myRFID);

//Printing users
void print_single_user(User* ptr, int idx);
void print_all_users(User* ptr);
void print_uid(byte* ptr);

// Helpers
int read_integer();
bool read_confirmation();
int find_empty_index(User* ptr);
int count_rooms(User* ptr);

/**
 * @brief 
 * @param uidOut 
 * @return true 
 * @return false 
 */
void rfid_set_last_uid(
    const byte *uidIn
);

/**
 * @brief 
 * @param uidOut 
 * @return true 
 * @return false 
 */
bool rfid_get_last_uid(
    byte *uidOut
);


#endif
