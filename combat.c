#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combat.h"
#include "dungeon.h"  // <-- zorgt dat 'Room' bekend is

void fight(Player* player, Room* room) {
    Monster* monster = room->monster;
    if (!monster) return;

    printf("\n\033[1mGEVECHT BEGINT TEGEN: %s\033[0m\n", monster->name);
    srand(time(NULL));

    while (player->hp > 0 && monster->hp > 0) {
        int attackOrder = rand() % 17;
        printf("\033[36mAanval volgorde (binair): \033[1m");
        for (int i = 4; i >= 0; i--) {
            printf("%d", (attackOrder >> i) & 1);
        }
        printf("\033[0m\n");

        for (int i = 4; i >= 0; i--) {
            int bit = (attackOrder >> i) & 1;
            if (bit == 0) {
                player->hp -= monster->damage;
                if (player->hp < 0) player->hp = 0;
                printf("\033[31m%s valt aan! Speler verliest %d hp (\033[1m%d\033[0m)\n",
                       monster->name, monster->damage, player->hp);
                if (player->hp == 0) break;
            } else {
                monster->hp -= player->damage;
                if (monster->hp < 0) monster->hp = 0;
                printf("\033[32mSpeler valt aan! %s verliest %d hp (\033[1m%d\033[0m)\n",
                       monster->name, player->damage, monster->hp);
                if (monster->hp == 0) break;
            }
        }
    }

    if (player->hp == 0) {
        printf("\033[31mDe speler is verslagen!\033[0m\n");
    } else {
        printf("\033[32m%s is verslagen!\033[0m\n", monster->name);
        free(room->monster);
        room->monster = NULL;
    }
}
