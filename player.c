#include "player.h"

void initPlayer(Player* player) {
    player->currentRoom = 0;
    player->hp = 20;
    player->damage = 5;
}
