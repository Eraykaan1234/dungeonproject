#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "combat.h"
#include "dungeon.h"

#define INDENT "       "

// Functie om de healthbar van de speler of monster te printen met kleur
void print_hp_bar(const char* label, int hp, int max_hp) {
    int bar_width = 20;                  // Maximalen breedte van de healthbar
    float ratio = (float)hp / max_hp;    // Percentage van HP
    int filled = (int)(ratio * bar_width); // Aantal gevulde blokken op de bar

    const char* color;
    if (ratio > 0.6) color = "\033[1;32m"; // Groen als HP boven de 60%
    else if (ratio > 0.3) color = "\033[1;33m"; // Geel als HP tussen 30% en 60%
    else color = "\033[1;31m"; // Rood als HP onder de 30%

    // Print healthbar met kleur
    printf(INDENT "%-12s [", label); // Label voor speler of monster
    printf("%s", color);
    for (int i = 0; i < filled; i++) printf("█"); // Gevulde blokken
    for (int i = filled; i < bar_width; i++) printf("░"); // Lege blokken
    printf("\033[0m] %3d%% (%d/%d)\n", (int)(ratio * 100), hp, max_hp);
}

// Functie voor het gevecht tussen de speler en een monster
void fight(Player* player, Room* room) {
    Monster* monster = room->monster;
    if (!monster) return;  // Als er geen monster is, doe dan niks

    int monster_max_hp = monster->hp;  // Bewaar de originele HP van het monster
    int player_max_hp = player->hp;    // Bewaar de originele HP van de speler

    // Geanimeerde intro van het gevecht
    usleep(300000);
    printf("\n\033[1;35m*** HET GEVECHT BEGINT TEGEN: %s ***\033[0m\n", monster->name);
    usleep(300000);

    // Intro box voor de strijd
    char* titel = "EPIC STRIJD START!";
    int total_width = 32;
    int text_len = strlen(titel);
    int side_space = (total_width - 2 - text_len) / 2; // Bereken ruimte aan beide zijden van de tekst

    // Print de box rond de titel
    printf(INDENT "\033[1;35m********************************\n");
    printf(INDENT "*                              *\n");
    printf(INDENT "*%*s\033[1;33m%s\033[1;35m%*s*\n",
           side_space, "", titel, total_width - 2 - side_space - text_len, "");
    printf(INDENT "*                              *\n");
    printf(INDENT "********************************\033[0m\n");
    usleep(500000);

    srand(time(NULL));  // Initialiseer de random generator

    while (player->hp > 0 && monster->hp > 0) {  // Blijf vechten zolang beide nog leven
        int attackOrder = rand() % 17;  // Genereer een willekeurige aanval volgorde

        printf("\n\033[36mAanval volgorde (binair): \033[1m");
        for (int i = 4; i >= 0; i
        
        --) {
            printf("%d", (attackOrder >> i) & 1);  // Print de aanval volgorde in binair
        }
        printf("\033[0m\n");

        // Voer de aanvallen uit
        for (int i = 4; i >= 0; i--) {
            int bit = (attackOrder >> i) & 1;  // Haal de individuele bits op

            // Toon de HP van speler en monster voor elke actie
            print_hp_bar("Speler", player->hp, player_max_hp);
            print_hp_bar(monster->name, monster->hp, monster_max_hp);
            usleep(300000);  // Wacht 300ms voor visuele vertraging

            if (bit == 0) {  // Als het bit 0 is, valt het monster aan
                player->hp -= monster->damage;
                if (player->hp < 0) player->hp = 0;
                printf(INDENT "\033[1;31m%s valt aan! Speler verliest %d hp (\033[1m%d\033[0m)\n",
                       monster->name, monster->damage, player->hp);
                if (player->hp == 0) break;  // Stop het gevecht als speler sterft
            } else {  // Als het bit 1 is, valt de speler aan
                monster->hp -= player->damage;
                if (monster->hp < 0) monster->hp = 0;
                printf(INDENT "\033[1;32mSpeler valt aan! %s verliest %d hp (\033[1m%d\033[0m)\n",
                       monster->name, player->damage, monster->hp);
                if (monster->hp == 0) break;  // Stop het gevecht als monster sterft
            }

            usleep(1000000);  // Wacht 1 seconde tussen acties voor visuele vertraging
        }
    }

    // Einde van het gevecht
    printf("\n");
    if (player->hp == 0) {
        printf(INDENT "\033[1;31m☠️  De speler is verslagen!\033[0m\n");
    } else {
        printf(INDENT "\033[1;32m%s is verslagen!\033[0m\n", monster->name);
        free(room->monster);  // Verwijder het monster uit de kamer
        room->monster = NULL;  // Zet het monster naar NULL
    }
}