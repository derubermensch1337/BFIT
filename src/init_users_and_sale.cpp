/**
 * @file init_user_and_sale.cpp
 * @brief used to initualice the users and products 
 * @author Baldur G. Toftegaard
*/

#include "init_users_and_sale.h"

void init_users_and_products (
){
    inventory fridge;
    inventory room_1;
    inventory room_2;
    inventory room_3;
    inventory room_4;
    inventory room_5;
    inventory room_6;
    inventory room_7;
    inventory room_8;
    inventory room_9;
    inventory room_10;
    inventory room_11;
    inventory room_12;
    inventory room_13;
    inventory room_14;
    inventory room_15;
    inventory room_16;
    inventory room_17;
    inventory room_18;

    inventory_init(&fridge);
    inventory_init(&room_1);
    inventory_init(&room_2);
    inventory_init(&room_3);
    inventory_init(&room_4);
    inventory_init(&room_5);
    inventory_init(&room_6);
    inventory_init(&room_7);
    inventory_init(&room_8);
    inventory_init(&room_9);
    inventory_init(&room_10);
    inventory_init(&room_11);
    inventory_init(&room_12);
    inventory_init(&room_13);
    inventory_init(&room_14);
    inventory_init(&room_15);
    inventory_init(&room_16);
    inventory_init(&room_17);
    inventory_init(&room_18);
    
    product tuborg_clasic = inventory_make_product("Tuborg clasic", beer, 330, 8);
    product tuborg_green = inventory_make_product("Tuborg green", beer, 330, 8);
    product limfjord = inventory_make_product("Limfjords porter", limfjords_porter, 550, 9);
    product pepsi = inventory_make_product("Pepsi Max", soda, 330, 7);

    inventory_add_product(&fridge, tuborg_clasic, 550);
    inventory_add_product(&fridge, tuborg_green, 550);
    inventory_add_product(&fridge, limfjord, 90);
    inventory_add_product(&fridge, pepsi, 650);
    
    inventory_print(&fridge);
}
  