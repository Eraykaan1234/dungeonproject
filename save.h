#ifndef SAVE_H
#define SAVE_H

#include "dungeon.h"
#include "player.h"

void save_game(Room **rooms, int count, Player *player);
void load_game(Room ***rooms, int *count, Player *player);

#endif
