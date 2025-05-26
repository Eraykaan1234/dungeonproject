#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"

typedef struct Monster {
    char name[20];
    int hp;
    int damage;
} Monster;


struct Room;

void fight(Player *player, struct Room *room);

#endif
