/**
 * @file    inventory.h
 * @brief   Functions responsible for keeping track of the fridge inventory.
 * @author  Baldur G. Toftegaard
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdint.h>
#include <stdbool.h>

#define INVENTORY_CAPACITY 6

/** 
 * @brief Types of beverages supported by the system. 
*/
typedef enum {
    beer,                   /**< Beer */
    cider,                  /**< Cider */
    soda,                   /**< Soda */
    limfjords_porter,       /**< Limfjords porter */
    other                   /**< Other */
} beverage_type;

/** 
 * @brief Struct holding the information for one item.
*/
typedef struct {
    char name[20];          /**< Beverage  name */              
    beverage_type beverage; /**< Beverage  type */
    uint8_t weight;         /**< Beverage  weight */
    uint8_t price;          /**< Beverage  price */
} product;

/**
 * @brief Struckt for keeping track of the original and current quantity of a beverage.
*/
typedef struct {
    product beverage;       /**< The beverage being tracked */
    uint8_t original_qty;   /**< The original quantity of the beverage in stock */
    uint8_t current_qty;    /**< The current quantity of the beverage in stock */
} products_stocked;

/**
 * @brief Struckt for holding the fridge inventory.
*/
typedef struct {
    products_stocked fridge[INVENTORY_CAPACITY];    /**< The beverages being stocked */
    uint8_t number_products_stocked;                /**< Number of beverages stocked, prevents overflow */
} inventory;


/**
 * @brief Function for initualicing the inventory
 * 
 * @param Inventory Inventory instance to initialize 
 */
void inventory_init(inventory *inventory);

/**
 * @brief Function for defining a new item.
 * 
 * @param name 
 * @param type 
 * @param weight 
 * @param price 
 * @return item created
 */
product make_product(const char *name, beverage_type type, uint8_t weight, uint8_t price);

/**
 * @brief Function for adding product to inventory.
 * 
 * @param inventory 
 * @param beverage 
 * @param quantity 
 * @return true - the beverage was added to the inventory
 * @return false - there was an error adding the beverage
 */
bool inventory_add_product(inventory *inventory, product beverage, uint8_t quantity);

#endif