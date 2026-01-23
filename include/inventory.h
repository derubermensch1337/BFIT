/**
 * @file    inventory.h
 * @brief   Inventory system for tracking the inventory of both the fridge and the induvidual users
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
 * @enum enum docomentation ?
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
    char name[20];                  /**< Beverage  name */              
    beverage_type beverage_variant; /**< Beverage  type */
    uint16_t weight;                /**< Beverage  weight */
    uint8_t price;                  /**< Beverage  price */
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
 * @brief Strukt used for making the inventory
 * 
 */
typedef struct {
    products_stocked produckts_in_inventory[INVENTORY_CAPACITY];    /**< The beverages being stocked */
    uint8_t number_of_products_stocked;                             /**< Number of beverages stocked, prevents overflow */
    uint8_t room_number;                                            /**< Not used in the current system */
    /**< Store the FRID belonging to the spesific user, not implemented */
} inventory;


/**
 * @brief Function for initualicing the inventory
 * 
 * @param Inventory Inventory instance to initialize 
 */
void inventory_init(
    inventory *inventory    /*< Inventory you cant to initialize, ensures that the memory space is empty */
);

/**
 * @brief Function for making a new product.
 * 
 * @param name
 * @param type
 * @param weight 
 * @param price 
 * @return item created
 */
product inventory_make_product(
    const char *name,               /**< Display name of product */
    beverage_type type,             /**< What type of product it is, whuld allow to sort by product type */
    uint16_t weight,                /**< Weight of the product, used for detecting how much of the product that was removed */
    uint8_t price                   /**< Price of the product, this whuld make it posible to automaticaly calculate the bill for eatch user */
);

/**
 * @brief Function for adding product to inventory.
 * 
 * @param inventory 
 * @param beverage 
 * @param quantity 
 * @return true - the product was added to the inventory
 * @return false - there was an error adding the product
 */
bool inventory_add_product (
        inventory *inventory,       /**< Inventory you want to add a product to */
        product product,            /**< The product you want to add to the inventory */
        uint16_t quantity           /**< The amount of the priduct you want to add to the inventory */
);

/**
 * @brief Function for removing product from inventory
 * 
 * @param inventory 
 * @param beverage 
 * @param quantity 
 * @return true - the product was removed from the inventory
 * @return false - there was an error removing the product
 */
bool inventory_remove_product(
    inventory *inventory,           /**< Inventory you want to remove a product from */
    product beverage                /**< Beverage you want to remove */
);

/**
 * @brief Function for adding to the amount of a beverage in an inventory
 * 
 * @param inventory 
 * @param beverage_type 
 * @param amount 
 * @return true - the beverage was added to the inventory
 * @return false - there was an error adding the beverage
 */
bool inventory_add_beverage(
    inventory *inventory,       /**< The inventory you want to add a beverage to */
    product  beverage,          /**< The beverage you want to edit the amount of */
    uint16_t amount             /**< The amount you want to add to the inventory */
);

/**
 * @brief Function for removing from the amount of a beverage in an inventory
 * 
 * @param inventory 
 * @param beverag 
 * @param amount 
 * @return true - the beverage was removed from the inventory
 * @return false - there was an error removing the beverage
 */
bool inventory_remove_beverage(
    inventory *inventory,       /**< The inventory you want to add a beverage to */
    product beverag,            /**< The beverage you want to edit the amount of */ 
    uint8_t amount              /**< The amount you want to remove from the inventory */
);
    
/**
 * @brief Function to print a users inventory
 * 
 * @param inventory 
 */
void inventory_print(
    inventory *inventory    /**< Inventory you want to print the content of */
);

#endif