#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
    int currentRoom;
    int hp;
    int damage;
} Player;

void initPlayer(Player* player);

#endif
