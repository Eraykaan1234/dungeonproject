#ifndef SAVE_H
#define SAVE_H

#include "player.h"
#include "dungeon.h"

int save_game(const char *filename, Player *player, Room *rooms[], int room_count);
int load_game(const char *filename, Player *player, Room *rooms[], int room_count);

#endif
