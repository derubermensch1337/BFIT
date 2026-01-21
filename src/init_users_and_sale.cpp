/**
 * @file init_user_and_sale.cpp
 * @brief used to initualice the users and products 
 * @author Baldur G. Toftegaard
*/

#include "init_users_and_sale.h"
#include <math.h>
#include "weight_scale.h"
#include "rfid_access.h"
#include "graph_data.h"

void init_users_and_products (
){
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
}

static float read_current_weight_blocking(uint32_t timeoutMs = 1200)
{
    uint32_t start = millis();

    while (millis() - start < timeoutMs) {
        if (update_scale()) {
            return get_weight();
        }
        delay(5);
    }

    return get_weight();
}

void perform_sale(inventory *fridge_inventory)
{
    byte lastUid[UID_LENGTH];

    if (!rfid_get_last_uid(lastUid)) {
        Serial.println("No last RFID available");
        return;
    }

    int saleIndex = -1;  

    for (int i = 0; i < MAX_ROOMS; i++) {
        if (users[i].roomNumber > 0 &&
            compare_UID(lastUid, users[i].uid)) {

            saleIndex = i;   // <-- capture the index
            Serial.print("Sale matched user index: ");
            Serial.println(saleIndex);
            Serial.print("User roomNumber field: ");
            Serial.println(users[i].roomNumber);
            break;
        }
    }

    if (saleIndex < 0) {
        Serial.println("RFID did not match any user index");
        return;
    }

    // Check if reference exists
    if (!weight_reference_is_set()) {
        float ref = read_current_weight_blocking();
        set_weight_reference(ref);
        return;
    }

    float referenceWeight = get_weight_reference();
    float currentWeight   = read_current_weight_blocking();

    int cans_taken = get_beer_cans_taken(referenceWeight, currentWeight);

    Serial.print("[SALE] ref = "); Serial.println(referenceWeight, 2);
    Serial.print("[SALE] cur = "); Serial.println(currentWeight, 2);
    Serial.print("[SALE] ref-cur = "); Serial.println(referenceWeight - currentWeight, 2);
    Serial.print("[SALE] cans_taken = "); Serial.println(cans_taken);

    // if (cans_taken <= 0) {
    //     return;
    // }

    if (cans_taken <= 0) {
        Serial.println("[SALE] No cans detected -> exit");
        return;
    }

    Serial.println(cans_taken);
    Serial.print(" cans sold");


    for (uint8_t index = 0; index < fridge_inventory->number_of_products_stocked; index++) {
        products_stocked *beverage_in_inventory = &fridge_inventory->produckts_in_inventory[index];

        if (beverage_in_inventory->beverage.beverage_variant != beer) continue;

        if (beverage_in_inventory->current_quantity >= cans_taken) {
            beverage_in_inventory->current_quantity -= cans_taken;
        } else {
            beverage_in_inventory->current_quantity = 0;
        }
        break;
    }

    if (saleIndex >= 0 && saleIndex < ROOM_COUNT) {
        greenHeight[saleIndex] += (cans_taken * 5);
        if (greenHeight[saleIndex] < 0) greenHeight[saleIndex] = 0;

        Serial.print("Updated greenHeight[");
        Serial.print(saleIndex);
        Serial.print("] = ");
        Serial.println(greenHeight[saleIndex]);
    } else {
        Serial.println("Sale index out of graph range (check ROOM_COUNT vs MAX_ROOMS)");
    }

    set_weight_reference(currentWeight);

    Serial.println("=== INVENTORY UPDATED ===");
    inventory_print(fridge_inventory);
    Serial.println("=========================");
}
