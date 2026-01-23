/**
 * @file    init_users_and_sale.h
 * @brief   Function used for declearing the system users and products
 * @author  Baldur G. Toftegaard
*/

#ifndef INIT_USERS_AND_SALE_H
#define INIT_USERS_AND_SALE_H

#include "inventory.h"
#define number_of_users 18

/**
 * @brief Old function for initializing users and products.
*/
void init_users_and_products();

/**
 * @brief Performs a sale between a user and the fridge.
 * @param weight - Read the value from the weight.
 * @param user_id - The user the sale shuld be registered to.
 * @param fridge_inventory - The inventory we wish to remove the beverage from.
*/
void perform_sale(
    inventory *fridge_inventory /**< Inventory that the sale shuld remove item from */
);

#endif