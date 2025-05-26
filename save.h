#ifndef SAVE_H
#define SAVE_H

#include "player.h"
#include "dungeon.h"

void save_game(const char *filename, Player *player, Room **rooms, int room_count);
void load_game(const char *filename, Player *player, Room ***rooms_ptr, int *room_count_ptr);

#endif
