#ifndef DUNGEON_H
#define DUNGEON_H

#include "player.h"

typedef enum { EMPTY, MONSTER, ITEM, TREASURE } RoomType;

typedef struct Room {
    int id;
    RoomType type;
    int visited;
    int has_treasure;
    int num_doors;
    int *connections;
    struct Monster *monster;
    struct Item *item;
} Room;

void generate_dungeon(Room ***rooms, int count);
void enter_room(Room *room, Player *player);
void print_doors(Room *room);
void free_dungeon(Room **rooms, int count);

#endif
