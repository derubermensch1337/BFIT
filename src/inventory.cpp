/**
 * @file    inventory.cpp
 * @brief   Functions responsible for keeping track of the fridge inventory.
 * @author  Baldur G. Toftegaard
*/

#include "inventory.h"
#include <string.h>

void inventory_init(
        inventory *inventory
){
    memset(inventory, 0, sizeof(*inventory));                           // make sure that the part of memory used for storing beverages is empty befor we start filling inventory.
}

/**
 * @todo evt. lav input om til en struct m. en wrapper for ease of use.
 */
product inventory_make_product(
        const char *name, 
        beverage_type type,
        uint8_t weight,
        uint8_t price
){
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

/**
 * @todo Make universal add product, make new function for restocking inventory
*/
bool inventory_add_product(
        inventory *inventory,
        product product,
        uint8_t quantity
){
    if (inventory->number_of_products_stocked >= INVENTORY_CAPACITY)     // check if the user has atempted to add more products than that suported by the code. If so return false. 
        return false;  

    products_stocked *product_in_fridge = &inventory->produckts_in_inventory[
        inventory->number_of_products_stocked];                         // we make an pointer into the product_stock struct of the inventory.
    
    product_in_fridge->beverage = product;                              // we can now use that pointer to add the product.
    product_in_fridge->current_quantity  += quantity;                   // add the product to the inventory stock.

    inventory->number_of_products_stocked++;                            // increase the counter keeping track of the number of different products stocked.
    return true;                                                        // if adding the priduct was succsesfull we return 1
}

bool inventory_remove_product(
    inventory *inventory, 
    product beverage, 
    uint8_t quantity
){

}

void inventory_print(
        inventory *inventory
){
    for (uint8_t index = 0; index < inventory->number_of_products_stocked; index++) {
        products_stocked *produckts_in_inventory = &inventory->produckts_in_inventory[index];
        
        Serial.print("Product ");
        Serial.print(index);
        Serial.print(": ");

        Serial.print(produckts_in_inventory->beverage.name);
        Serial.print(", type=");
        Serial.print((int)produckts_in_inventory->beverage.beverage);

        Serial.print(", weight=");
        Serial.print(produckts_in_inventory->beverage.weight);

        Serial.print(", price=");
        Serial.print(produckts_in_inventory->beverage.price);

        Serial.print(", qty=");
        Serial.print(produckts_in_inventory->current_quantity);
        Serial.print("/");
        Serial.println(produckts_in_inventory->original_quantity);
    }   
}
