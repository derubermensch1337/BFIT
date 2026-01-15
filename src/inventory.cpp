/**
 * @file inventory.cpp
 * @authors Baldur G. Toftegaard,
 * @brief  
 * @date 14-01-2026
 * @version 0.1
 * @par Revision history
 * | Version |    Date    | Description                             |
 * |---------|------------|-----------------------------------------|
 * |   0.1   | 14-01-2026 | Create file                             |
 * |   0.2   | 15-01-2026 | Began programming the inventory system  |
 *
 * @copyright Copyright (c) 2026
 * 
*/

#include "inventory.h"

item make_item(const char *name, item_type type, uint8_t weight, uint8_t price) {
    item i;
    strncpy(i.name, name, sizeof(i.name) - 1);
    i.name[sizeof(i.name) - 1] = '\0';  // safety
    i.item = type;
    i.weight = weight;
    i.price = price;
    return i;
}