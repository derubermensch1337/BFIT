/**
 * @file inventory.cpp
 * @authors Baldur G. Toftegaard,
 * @brief  
 * @date 14-01-2026
 * @version 0.1
 * @par Revision history
 * | Version |    Date    | Description                                                                     |
 * |---------|------------|---------------------------------------------------------------------------------|
 * |   0.1   | 14-01-2026 | Create file                                                                     |
 * |   0.2   | 15-01-2026 | Began programming the inventory system                                          |
 * |   0.3   | 16-01-2026 | Added functionality to init inventory, make product and and product to fridge   |
 *
 * @copyright Copyright (c) 2026
 * 
*/

#include "inventory.h"

void inventory_init(inventory *inventory) {             // make an instance of the inventory.
    memset(inventory, 0, sizeof(*inventory));           // make sure that the part of memory used for storing beverages is empty befor we start filling inventory.
}

item make_item(const char *name, item_type type, uint8_t weight, uint8_t price) {
    item new_item;                                      // we make an instance of the item type.
    memset(&new_item, 0, sizeof(new_item));             // we start by making sure that the memory used for the item is empty.

    if (name) {
        strncpy(new_item.name, name, sizeof(new_item.name) - 1);
        new_item.name[sizeof(new_item.name) - 1] = '\0';
    }

    new_item.item = type;                               // we give the item a type.
    new_item.weight = weight;                           // we give the item a weight. 
    new_item.price = price;                             // we give the item a price.
    return new_item;
}

bool inventory_add_product(inventory *inventory, item product, uint8_t quantity) {
    if (inventory->product_stocked >= 6)                // check if the user has atempted to add more products than that suported by the code. 
        return false;  

    product_stock *slot = &inventory->fridge[inventory->product_stocked];
    slot->product = product;
    slot->original_qty = quantity;
    slot->current_qty  = quantity;

    inventory->product_stocked++;
    return true;                                        // if adding the priduct was succsesfull we return 1
}