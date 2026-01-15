/**
 * @file inventory.h
 * @authors Baldur G. Toftegaard,
 * @brief  
 * @date 14-01-2026
 * @version 0.1
 * @par Revision history
 * | Version |    Date    | Description                                             |
 * |---------|------------|---------------------------------------------------------|
 * | 0.1     | 14-01-2026 | Create file                                             |
 * | 0.2     | 15-01-2026 | Added data type for beverages, products and invenntory  |
 *
 * @copyright Copyright (c) 2026
 * 
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include "Arduino.h"

typedef enum {                  // Create the different types of beverages.
    beer, 
    cider,
    soda,
    limfjords_porter,
    other
} item_type;

typedef struct {                // create different types of products.
    char name[20];
    item_type item;
    uint8_t weight;
    uint8_t price; 
} item;

typedef struct {                // Keep track of one type of product.
    item product;
    uint8_t original_qty;
    uint8_t current_qty;
} product_stock;

typedef struct {                // type to keep track of all products.
    product_stock fridge[6];    // the different products being stocked in the fridge.
    uint8_t product_stocked;    // used to keep track if there are items out of stock.
} inventory;

item make_item(const char *name, item_type type, uint8_t weight, uint8_t price);

#endif