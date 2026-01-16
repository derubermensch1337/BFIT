/**
 * @file    inventory.h
 * @brief   Functions responsible for keeping track of the fridge inventory.
 * @author  Baldur G. Toftegaard
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include "Arduino.h"

#define INVENTORY_CAPACITY 6

/** 
 * @brief Types of beverages supported by the system. 
*/
typedef enum {                  // Create the different types of beverages.
    beer,               /**< Beer */
    cider,              /**< Cider */
    soda,               /**< Soda */
    limfjords_porter,   /**< Limfjords porter */
    other               /**< Other */
} item_type;

/** 
 * @brief Struct holding the information for one item.
*/
typedef struct {
    char name[20];      /**< Beverage  name */              
    item_type item;     /**< Beverage  type */
    uint8_t weight;     /**< Beverage  weight */
    uint8_t price;      /**< Beverage  price */
} item;

/**
 * @brief Struckt for keeping track of the original and current quantity of a beverage.
*/
typedef struct {
    item product;           /**< The beverage being tracked */
    uint8_t original_qty;   /**< The original quantity of the beverage in stock */
    uint8_t current_qty;    /**< The current quantity of the beverage in stock */
} products_stocked;

/**
 * @brief Struckt for holding the fridge inventory.
*/
typedef struct {
    products_stocked fridge[6];         /**< The beverages being stocked */
    uint8_t number_products_stocked;    /**< Number of beverages stocked, prevents overflow */
} inventory;


/**
 * @brief Function for initualicing the inventory
 * 
 * @param inventory 
 */
void inventory_init(inventory *inventory);

/**
 * @brief Function for defining a new item.
 * 
 * @param name 
 * @param type 
 * @param weight 
 * @param price 
 * @return item 
 */
item make_item(const char *name, item_type type, uint8_t weight, uint8_t price);

/**
 * @brief Function for adding product to inventory.
 * 
 * @param inventory 
 * @param product 
 * @param quantity 
 * @return true 
 * @return false 
 */
bool inventory_add_product(inventory *inventory, item product, uint8_t quantity);

#endif