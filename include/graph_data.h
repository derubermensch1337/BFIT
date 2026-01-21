#ifndef GRAPH_DATA_H
#define GRAPH_DATA_H

#include <stdint.h>

#define ROOM_COUNT 18

extern int greenHeight[ROOM_COUNT];
extern int classicHeight[ROOM_COUNT];

void graph_add_to_room_green(uint8_t roomNumber, int delta);
void graph_add_to_room_clasic(uint8_t roomNumber, int delta);


void print_graph_arrays();

#endif
