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

    // Timeout: return last known value
    return get_weight();
}

void perform_sale(inventory *fridge_inventory)
{
    byte lastUid[UID_LENGTH];

    if (!rfid_get_last_uid(lastUid)) {
        Serial.println("No last RFID available");
        return;
    }

    uint8_t saleRoom = 0;
    int saleIndex = -1;

    for (int i = 0; i < MAX_ROOMS; i++) {
        if (users[i].roomNumber > 0 &&
            compare_UID(lastUid, users[i].uid)) {

            saleRoom = users[i].roomNumber;  // <-- capture room
            Serial.print("Sale registered to room: ");
            Serial.println(saleRoom);
            saleIndex = i;

            break;
        }
    }

    if (saleRoom == 0) {
        Serial.println("RFID did not match any room");
        return;
    }

    if (fridge_inventory == nullptr) {
        Serial.println("fridge_inventory is null");
        return;
    }

    // 1) Ensure reference weight exists
    if (!weight_reference_is_set()) {
        Serial.println("Weight reference is not set");
        float ref = read_current_weight_blocking();
        set_weight_reference(ref);
        return;
    }

    float referenceWeight = get_weight_reference();
    float currentWeight   = read_current_weight_blocking();

    int cans_taken = get_beer_cans_taken(referenceWeight, currentWeight);
    if (cans_taken <= 0) {
        return;
    }

    //add cans taken to user array
    users[saleIndex].balance += cans_taken;

    // --- inventory update (your existing logic) ---
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

    // --- update graph arrays (example: +5 per can) ---
    graph_add_to_room_green(saleRoom, cans_taken * 5);

    set_weight_reference(currentWeight);
}