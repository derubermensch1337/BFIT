/**
 * @file rfid_unlock.h
 * @brief Track user RFID and inventory
 * @author Amal Araweelo Almis
 * @author Amal Araweelo Almis
 */
#ifndef RFID_UNLOCK_H
#define RFID_UNLOCK_H  

#include <SPI.h>
#include <MFRC522.h>
#include "inventory.h"

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
    CMD_REMOVE_USER
};

/**
 * @brief Define user ID, room, and inventory
 */
struct User {
    byte uid[UID_LENGTH];       /**< User ID */
    int roomNumber;             /**< Users room number */
    inventory user_innventory;  /**< Inventory for the user */
};

// Extern globals declared
extern User users[MAX_ROOMS];
extern int userCount;

// Function prototypes
RFIDcommand check_command(void);
void setup_RFID_reader(MFRC522 &rfid);
void add_user(MFRC522 &rfid);
bool compare_UID(byte *uid1, byte *uid2);
bool read_RFID_tag(MFRC522 &rfid, byte *uidBuffer);
void display_commands(void);

// For database management
void get_users_db(User* ptr);
void print_users_db(User* ptr);
void print_uid(User* ptr);
void delete_user_db();
void add_user_db();
int read_integer();
int find_empty_index(User* ptr);
int count_rooms(User* ptr);

#endif
