#ifndef DUNGEON_H
#define DUNGEON_H

#include "player.h"
#include "utils.h"
#include "combat.h"  // voor struct Monster
#include "item.h"


typedef enum { EMPTY, MONSTER, ITEM, TREASURE } RoomType;

typedef struct Room {
    int id;
    RoomType type;
    int visited;
    int has_treasure;
    int connections[4];         // max 4 richtingen (N, O, Z, W)
    struct Monster *monster;
    struct Item *item;
} Room;

void generate_dungeon(Room ***rooms, int count);
void enter_room(Room *room, Player *player);
void print_doors(Room *room);
void free_dungeon(Room **rooms, int count);

#endif
