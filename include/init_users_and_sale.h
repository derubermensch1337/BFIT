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
 * @brief Old function for initualicing users and products, shuld be moved to fridge_state.h
*/
void init_users_and_products();

/**
 * @brief Function to actually performe a sale between a user and the fridge
 * @param weight 
 * @param user_id 
 * @param fridge_inventory 
*/
void perform_sale(
    inventory *fridge_inventory /**< Inventory that the sale shuld remove item from */
);

#endif