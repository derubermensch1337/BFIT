/**
 * @file    inventory.cpp
 * @brief   Functions responsible for keeping track of the fridge inventory.
 * @author  Baldur G. Toftegaard
*/

#include "inventory.h"
#include <string.h>

void inventory_init(inventory *inventory) {                             // make an instance of the inventory.
    memset(inventory, 0, sizeof(*inventory));                           // make sure that the part of memory used for storing beverages is empty befor we start filling inventory.
}

product make_product(const char *name, beverage_type type, uint8_t weight, uint8_t price) {
    product new_product;                                                // we make an instance of the item type.
    memset(&new_product, 0, sizeof(new_product));                       // we start by making sure that the memory used for the item is empty.

    if (name) {                                                         // make sure the user provided an input for the name.
        strncpy(new_product.name, name, sizeof(new_product.name) - 1);  // copy the input into the instanse of the item strukt.
        new_product.name[sizeof(new_product.name) - 1] = '\0';          // go back and manualy add a end of line terminator (incase the input was to long and got cut of).
    } 

    new_product.beverage = type;                                        // we give the item a type.
    new_product.weight = weight;                                        // we give the item a weight. 
    new_product.price = price;                                          // we give the item a price.
    return new_product;
}

bool inventory_add_product(inventory *inventory, product product, uint8_t quantity) {
    if (inventory->number_products_stocked >= INVENTORY_CAPACITY)       // check if the user has atempted to add more products than that suported by the code. If so return false. 
        return false;  

    products_stocked *product_in_fridge = &inventory->fridge[
        inventory->number_products_stocked];                            // we make an pointer into the product_stock struct of the inventory.
    
    product_in_fridge->product = product;                               // we can now use that pointer to add the product.
    product_in_fridge->original_qty = quantity;                         // add the starting stock quantity,
    product_in_fridge->current_qty  = quantity;                         // add the current stock quantity.

    inventory->number_products_stocked++;                               // increase the counter keeping track of the number of different products stocked.
    return true;                                                        // if adding the priduct was succsesfull we return 1
}