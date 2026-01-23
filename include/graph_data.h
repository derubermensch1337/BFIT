/**
 * @file graph_data.h
 * @brief File used for setting up the graph section of the web server
 * @author Baldur G. Toftegaard
*/

#ifndef GRAPH_DATA_H
#define GRAPH_DATA_H

#include <stdint.h>

/**
 * @def ROOM_COUNT
 * @brief Number of rooms supported by the sales graph.
*/
#define ROOM_COUNT 18

/**
 * @brief Height values for green product sales per room.
*/
extern int greenHeight[ROOM_COUNT];

/**
 * @brief Height values for classic product sales per room.
*/
extern int classicHeight[ROOM_COUNT];

/**
 * @brief Adds a value to the green sales bar of a given room.
 * 
 * @param roomNumber 
 * @param delta 
*/
void graph_add_to_room_green(
    uint8_t roomNumber, 
    int delta
);

/**
 * @brief Adds a value to the classic sales bar of a given room.
 * 
 * @param roomNumber 
 * @param delta 
*/
void graph_add_to_room_clasic(
    uint8_t roomNumber,
    int delta
);

/**
 * @brief Prints the current graph height arrays.
*/
void print_graph_arrays();

#endif
