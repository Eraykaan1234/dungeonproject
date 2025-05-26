#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combat.h"

void fight(Player* player, Room* room) {
    Monster* monster = room->monster;
    if (!monster) return;

    printf("Er is een %s in kamer %d! Gevecht begint.\n", monster->name, room->id);
    srand(time(NULL));

    while (player->hp > 0 && monster->hp > 0) {
        int attackOrder = rand() % 17; // 0–16
        printf("Aanval volgorde (binair): ");
        for (int i = 4; i >= 0; i--) {
            printf("%d", (attackOrder >> i) & 1);
        }
        printf("\n");

        for (int i = 4; i >= 0; i--) {
            int bit = (attackOrder >> i) & 1;
            if (bit == 0) {
                player->hp -= monster->damage;
                if (player->hp < 0) player->hp = 0;
                printf("%s valt aan! Speler verliest %d hp (%d)\n", monster->name, monster->damage, player->hp);
                if (player->hp == 0) break;
            } else {
                monster->hp -= player->damage;
                if (monster->hp < 0) monster->hp = 0;
                printf("De speler valt aan! %s verliest %d hp (%d)\n", monster->name, player->damage, monster->hp);
                if (monster->hp == 0) break;
            }
        }
    }

    if (player->hp == 0) {
        printf("De speler is verslagen!\n");
    } else {
        printf("%s is verslagen!\n", monster->name);
        free(room->monster);
        room->monster = NULL;
    }
}
