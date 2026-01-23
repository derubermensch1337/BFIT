#include "graph_data.h"

extern int greenHeight[ROOM_COUNT];
extern int classicHeight[ROOM_COUNT];

void graph_add_to_room_green(uint8_t roomNumber, int delta)
{
    if (roomNumber < 1 || roomNumber > ROOM_COUNT) return;
    int &v = greenHeight[roomNumber - 1];
    v += delta;
    if (v < 0) v = 0;
}

void graph_add_to_room_clasic(uint8_t roomNumber, int delta)
{
    if (roomNumber < 1 || roomNumber > ROOM_COUNT) return;
    int &v = classicHeight[roomNumber - 1];
    v += delta;
    if (v < 0) v = 0;
}
