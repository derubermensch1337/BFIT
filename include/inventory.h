/**
 * @file    inventory.h
 * @brief   Functions responsible for keeping track of the fridge inventory.
 * @author  Baldur G. Toftegaard
*/

#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>

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
    product beverage;           /**< The beverage being tracked */
    uint8_t original_quantity;  /**< The original quantity of the beverage in stock */
    uint8_t current_quantity;   /**< The current quantity of the beverage in stock */
} products_stocked;

/**
 * @brief Struckt for holding the fridge inventory.
*/
typedef struct {
    products_stocked produckts_in_inventory[INVENTORY_CAPACITY];    /**< The beverages being stocked */
    uint8_t number_of_products_stocked;                             /**< Number of beverages stocked, prevents overflow */
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
product inventory_make_product(const char *name, beverage_type type, uint16_t weight, uint8_t price);

/**
 * @brief Function for adding product to inventory.
 * 
 * @param inventory 
 * @param beverage 
 * @param quantity 
 * @return true - the product was added to the inventory
 * @return false - there was an error adding the product
 */
bool inventory_add_product(inventory *inventory, product beverage, uint16_t quantity);

/**
 * @brief Function for removing product from inventory
 * 
 * @param inventory 
 * @param beverage 
 * @param quantity 
 * @return true - the product was removed from the inventory
 * @return false - there was an error removing the product
 */
bool inventory_remove_product(inventory *inventory, product beverage);

/**
 * @brief Function for adding to the amount of a beverage in an inventory
 * 
 * @param inventory 
 * @param beverage_type 
 * @param amount 
 * @return true - the beverage was added to the inventory
 * @return false - there was an error adding the beverage
 */
bool inventory_add_beverage(inventory *inventory, product  beverage, uint16_t amount);

/**
 * @brief Function for removing from the amount of a beverage in an inventory
 * 
 * @param inventory 
 * @param beverag 
 * @param amount 
 * @return true - the beverage was removed from the inventory
 * @return false - there was an error removing the beverage
 */
bool inventory_remove_beverage(inventory *inventory, product beverag, uint8_t amount);

/**
 * @brief Function to print a users inventory
 * 
 * @param inventory 
 */
void inventory_print(inventory *inventory);

#endif