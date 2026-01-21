#ifndef GRAPH_DATA_H
#define GRAPH_DATA_H

#include <stdint.h>

#define ROOM_COUNT 18  // single source of truth

void graph_add_to_room_green(uint8_t roomNumber, int delta);
void graph_add_to_room_clasic(uint8_t roomNumber, int delta);

#endif
