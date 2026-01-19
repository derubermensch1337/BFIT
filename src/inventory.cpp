/**
 * @file    inventory.cpp
 * @brief   Functions responsible for keeping track of the fridge inventory.
 * @author  Baldur G. Toftegaard
*/

#include "inventory.h"
#include <string.h>

void inventory_init (
        inventory *inventory
){
    memset(inventory, 0, sizeof(*inventory));                           // make sure that the part of memory used for storing beverages is empty befor we start filling inventory.
}


product inventory_make_product (
        const char *product_name, 
        beverage_type type,
        uint16_t weight,
        uint8_t price
){
    product new_product;                                                // we make an instance of the item type.
    memset(&new_product, 0, sizeof(new_product));                       // we start by making sure that the memory used for the item is empty.

    if (product_name) {                                                         // make sure the user provided an input for the name.
        strncpy(new_product.name, product_name, sizeof(new_product.name) - 1);  // copy the input into the instanse of the item strukt.
        new_product.name[sizeof(new_product.name) - 1] = '\0';          // go back and manualy add a end of line terminator (incase the input was to long and got cut of).
    } 

    new_product.beverage = type;                                        // we give the item a type.
    new_product.weight = weight;                                        // we give the item a weight. 
    new_product.price = price;                                          // we give the item a price.
    return new_product;
}


bool inventory_add_product (
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

bool inventory_remove_product (
    inventory *inventory, 
    product beverage
){
    for (uint8_t index = 0;
        index < inventory->number_of_products_stocked;
        index++
    ){
        products_stocked *products_in_inventory = &inventory->produckts_in_inventory[index];

        if (products_in_inventory->beverage.beverage == beverage.beverage &&
            strcmp(products_in_inventory->beverage.name, beverage.name) == 0
        ){
            for (uint8_t second_index = index; second_index + 1 < inventory->number_of_products_stocked; second_index++
            ){
                inventory->produckts_in_inventory[second_index] = inventory->produckts_in_inventory[second_index+1];
                
            }
            inventory->number_of_products_stocked--;

            memset(&inventory->produckts_in_inventory[inventory->number_of_products_stocked],
                0,
                sizeof(inventory->produckts_in_inventory[0]));
        }
    }
    return true;
}

bool inventory_add_beverage(
    inventory *inventory, 
    product beverag, 
    uint8_t amount
){
    if (!inventory || amount == 0)
        return false;

    for (uint8_t index = 0; index < inventory->number_of_products_stocked; index++
    ){
        products_stocked *product_in_inventory = &inventory->produckts_in_inventory[index];

        if (product_in_inventory->beverage.beverage == beverag.beverage &&
            strcmp(product_in_inventory->beverage.name, beverag.name) == 0
        ){
            if ((uint16_t)product_in_inventory->current_quantity + amount > UINT8_MAX)
            return false;
            
            product_in_inventory->current_quantity += amount;
            return true;
        }
    }
    return false;
}

bool inventory_remove_beverage(
    inventory *inventory, 
    product beverag, 
    uint8_t amount
){
    if (!inventory || amount == 0)
        return false;

    for (uint8_t index = 0; index < inventory->number_of_products_stocked; index++
    ){
        products_stocked *product_in_inventory = &inventory->produckts_in_inventory[index];

        if (product_in_inventory->beverage.beverage == beverag.beverage &&
            strcmp(product_in_inventory->beverage.name, beverag.name) == 0
        ){
            product_in_inventory->current_quantity -= amount;
            return true;
        }
    }
    return false;
}

void inventory_print (
        inventory *inventory
){
    for (uint8_t index = 0;
        index < inventory->number_of_products_stocked;
        index++
    ){
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
