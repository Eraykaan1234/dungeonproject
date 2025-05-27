// combat.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "combat.h"
#include "dungeon.h"
#define INDENT "       "

// Print een kleurrijke HP-bar op basis van gezondheid
void print_hp_bar(const char* label, int hp, int max_hp) {
    int bar_width = 20;
    float ratio = (float)hp / max_hp;
    int filled = (int)(ratio * bar_width);

    const char* color;
    if (ratio > 0.6) color = "\033[1;32m";       // Groen bij >60%
    else if (ratio > 0.3) color = "\033[1;33m";  // Geel bij >30%
    else color = "\033[1;31m";                   // Rood bij <=30%

    printf(INDENT "%-12s [", label);
    printf("%s", color);
    for (int i = 0; i < filled; i++) printf("█");
    for (int i = filled; i < bar_width; i++) printf("░");
    printf("\033[0m] %3d%% (%d/%d)\n", (int)(ratio * 100), hp, max_hp);
}

// Beheert het gevecht tussen speler en monster
void fight(Player* player, Room* room) {
    Monster* monster = room->monster;
    if (!monster) return;

    int monster_max_hp = monster->hp;
    int player_max_hp = player->hp;

    // Geanimeerde intro
    usleep(300000);
    printf("\n\033[1;35m*** HET GEVECHT BEGINT TEGEN: %s ***\033[0m\n", monster->name);
    usleep(300000);

    // Titel-box voor sfeer
    char* titel = "EPIC STRIJD START!";
    int total_width = 32;
    int text_len = strlen(titel);
    int side_space = (total_width - 2 - text_len) / 2;

    printf(INDENT "\033[1;35m********************************\n");
    printf(INDENT "*                              *\n");
    printf(INDENT "*%*s\033[1;33m%s\033[1;35m%*s*\n",
           side_space, "", titel, total_width - 2 - side_space - text_len, "");
    printf(INDENT "*                              *\n");
    printf(INDENT "********************************\033[0m\n");
    usleep(500000);
    srand(time(NULL));

    while (player->hp > 0 && monster->hp > 0) {
        int attackOrder = rand() % 17;  // 5-bit volgorde

        printf("\n\033[36mAanval volgorde (binair): \033[1m");
        for (int i = 4; i >= 0; i--) {
            printf("%d", (attackOrder >> i) & 1);
        }
        printf("\033[0m\n");

        // Voer 5 beurten uit
        for (int i = 4; i >= 0; i--) {
            int bit = (attackOrder >> i) & 1;

            // Toon actuele HP's
            print_hp_bar("Speler", player->hp, player_max_hp);
            print_hp_bar(monster->name, monster->hp, monster_max_hp);
            usleep(300000);

            if (bit == 0) {
                // Monster valt speler aan
                player->hp -= monster->damage;
                if (player->hp < 0) player->hp = 0;
                printf(INDENT "\033[1;31m%s valt aan! Speler verliest %d hp (\033[1m%d\033[0m)\n",
                       monster->name, monster->damage, player->hp);
                if (player->hp == 0) break;
            } else {
                // Speler valt monster aan
                monster->hp -= player->damage;
                if (monster->hp < 0) monster->hp = 0;
                printf(INDENT "\033[1;32mSpeler valt aan! %s verliest %d hp (\033[1m%d\033[0m)\n",
                       monster->name, player->damage, monster->hp);
                if (monster->hp == 0) break;
            }

            usleep(1000000); // Wacht 1 seconde tussen acties
        }
    }
    // Eindresultaat
    printf("\n");
    if (player->hp == 0) {
        printf(INDENT "\033[1;31m☠️  De speler is verslagen!\033[0m\n");
    } else {
        printf(INDENT "\033[1;32m%s is verslagen!\033[0m\n", monster->name);
        free(room->monster);
        room->monster = NULL;
    }
}
