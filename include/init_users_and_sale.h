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
 * @brief 
 */
void init_users_and_products();

/**
 * @brief  
 * @param weight 
 * @param user_id 
 * @param fridge_inventory 
*/
void perform_sale(
    uint16_t weight,
    uint16_t user_id,
    inventory *fridge_inventory
);

#endif