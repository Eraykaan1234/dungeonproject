#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"
#include "dungeon.h"

typedef struct Monster {
    char name[20];
    int hp;
    int damage;
} Monster;

void combat(Player *player, Monster *monster);
void fight(Player *player, Room *room); // <-- toegevoegd

#endif
