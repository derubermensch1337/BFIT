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

/**
 * @brief Maximum number of products the inventory can hold.
 */
#define INVENTORY_CAPACITY 6

/**
 * @enum beverage_type
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
 * @struct product
 * @brief Describes a single beverage product.
 */
typedef struct {
    char name[20];                  /**< Display name of the beverage */
    beverage_type beverage_variant; /**< Beverage type */
    uint16_t weight;                /**< Weight of the beverage (e.g. grams) */
    uint8_t price;                  /**< Price of the beverage */
} product;


/**
 * @struct products_stocked
 * @brief Tracks inventory quantities for a single product.
 */
typedef struct {
    product beverage;           /**< Product being tracked */
    uint8_t original_quantity;  /**< Initial stock quantity */
    uint8_t current_quantity;   /**< Current stock quantity */
} products_stocked;


/**
 * @struct inventory
 * @brief Represents a user's beverage inventory.
 */
typedef struct {
    products_stocked products_in_inventory[INVENTORY_CAPACITY];
        /**< Products currently in inventory */

    uint8_t number_of_products_stocked;
        /**< Number of valid entries in products_in_inventory */

    uint8_t room_number;
        /**< Room number associated with the inventory (currently unused) */

    /**< FRID of the user owning the inventory (not implemented) */
} inventory;


/**
 * @brief Initializes an inventory structure.
 *
 * Clears internal state and prepares the inventory for use.
 *
 * @param inventory Pointer to inventory instance to initialize.
 */
void inventory_init(inventory *inventory);


/**
 * @brief Creates a new product instance.
 *
 * @param name Display name of the product.
 * @param type Beverage type.
 * @param weight Weight of the product.
 * @param price Price of the product.
 *
 * @return Initialized product instance.
 */

/**
 * @brief 
 * 
 * @param name 
 * @param type 
 * @param weight 
 * @param price 
 * @return product 
 */
product inventory_make_product(
    const char *name,
    beverage_type type,
    uint16_t weight,
    uint8_t price
);

/**
 * @brief Adds a new product to the inventory.
 *
 * @param inventory Inventory to add the product to.
 * @param product Product to add.
 * @param quantity Initial quantity of the product.
 *
 * @return true Product successfully added.
 * @return false Error occurred (inventory full or duplicate product).
 */
bool inventory_add_product(
    inventory *inventory,
    product product,
    uint16_t quantity
);


/**
 * @brief Removes a product entirely from the inventory.
 *
 * @param inventory Inventory to remove the product from.
 * @param beverage Product to remove.
 *
 * @return true Product removed successfully.
 * @return false Product not found.
 */
bool inventory_remove_product(
    inventory *inventory,
    product beverage
);


/**
 * @brief Increases the quantity of a beverage in the inventory.
 *
 * @param inventory Inventory to modify.
 * @param beverage Beverage to update.
 * @param amount Quantity to add.
 *
 * @return true Quantity updated successfully.
 * @return false Product not found or overflow.
 */
bool inventory_add_beverage(
    inventory *inventory,
    product beverage,
    uint16_t amount
);

/**
 * @brief Function for removing from the amount of a beverage in an inventory.
 * 
 * @param inventory Inventory to modify.
 * @param beverage  Beverage to update.
 * @param amount    Quantity to remove.
 *
 * @return true  Quantity updated successfully.
 * @return false Product not found or insufficient stock.
 */
bool inventory_remove_beverage(
    inventory *inventory,
    product beverage,
    uint8_t amount
);
    
/**
 * @brief Function to print a users inventory
 *
 * @param inventory Inventory to print.
 */
void inventory_print(inventory *inventory);

#endif