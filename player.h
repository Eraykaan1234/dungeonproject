#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int location;
    int hp;
    int damage;
} Player;

void init_player(Player *player);

#endif
