#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combat.h"

void fight(Player* player, Room* room) {
    if (room->monster == 0) return; // Geen monster

    int monster_hp = 10;
    int monster_damage = (room->monster == 1) ? 3 : 5; // Goblin=3, Orc=5
    printf("Er is een monster in kamer %d! Gevecht begint.\n", room->id);

    srand(time(NULL));

    while (player->hp > 0 && monster_hp > 0) {
        int attackOrder = rand() % 17; // 0-16, 5 bits max
        printf("Aanval volgorde (binair): ");
        for (int i = 4; i >= 0; i--) {
            printf("%d", (attackOrder >> i) & 1);
        }
        printf("\n");

        for (int i = 4; i >= 0; i--) {
            int bit = (attackOrder >> i) & 1;
            if (bit == 0) {
                // Monster valt speler aan
                player->hp -= monster_damage;
                if (player->hp < 0) player->hp = 0;
                printf("De monster valt aan! Speler verliest %d hp (%d)\n", monster_damage, player->hp);
                if (player->hp == 0) break;
            } else {
                // Speler valt monster aan
                monster_hp -= player->damage;
                if (monster_hp < 0) monster_hp = 0;
                printf("De speler valt aan! Monster verliest %d hp (%d)\n", player->damage, monster_hp);
                if (monster_hp == 0) break;
            }
        }
    }

    if (player->hp == 0) {
        printf("De speler is verslagen!\n");
    } else {
        printf("Het monster is verslagen!\n");
        room->monster = 0; // Monster dood
    }
}
