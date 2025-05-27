#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // voor usleep
#include "dungeon.h"
#include "player.h"
#include "combat.h"
#include "save.h"
#include "utils.h"

#define INDENT "       "

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Gebruik: %s <aantal_kamers> of %s load\n", argv[0], argv[0]);
        return 1;
    }

    Player *player = malloc(sizeof(Player));
    Room **rooms = NULL;
    int room_count = 0;

    // Nieuw spel of laden
    if (strcmp(argv[1], "load") == 0) {
        load_game("save.txt", player, &rooms, &room_count);
        printf("Spel geladen.\n");
    } else {
        room_count = atoi(argv[1]);
        if (room_count < 5) {
            printf("Gebruik minstens 5 kamers.\n");
            return 1;
        }
        generate_dungeon(&rooms, room_count);
        init_player(player);
        printf("Nieuw spel gestart met %d kamers.\n", room_count);
    }

    while (1) {
        if (player->hp <= 0) {
            // GAME OVER
            printf("\n" INDENT "\033[1;31m╔══════════════════╗\n");
            printf(INDENT "║    GAME OVER     ║\n");
            printf(INDENT "╚══════════════════╝\033[0m\n\n");
            break;
        }

        Room *current = rooms[player->location];

        if (!current->visited) {
            enter_room(current, player);
            current->visited = 1;
            save_game("save.txt", player, rooms, room_count);

            if (player->hp <= 0) {
                printf("\n" INDENT "\033[1;31m╔══════════════════╗\n");
                printf(INDENT "║    GAME OVER     ║\n");
                printf(INDENT "╚══════════════════╝\033[0m\n\n");
                break;
            }
        } else {
            // Terug-keer box
            char terugregel[50];
            sprintf(terugregel, "Je bent terug in kamer %d", current->id);
            int terug_len = strlen(terugregel);
            int terug_box = terug_len + 8;

            printf(INDENT "\033[1;36m╔");
            for (int i = 0; i < terug_box; i++) printf("═");
            printf("╗\n");

            int terug_left = (terug_box - terug_len) / 2;
            int terug_right = terug_box - terug_len - terug_left;
            printf(INDENT "║%*s%s%*s║\n", terug_left, "", terugregel, terug_right, "");

            printf(INDENT "╚");
            for (int i = 0; i < terug_box; i++) printf("═");
            printf("╝\033[0m\n");

            save_game("save.txt", player, rooms, room_count);
        }

if (current->has_treasure) {
    usleep(300000);

    // ✨ BANNER
    char* schat = "🏆  JE HEBT DE SCHAT GEVONDEN! 🏆";
    int breedte = strlen(schat) + 12;  // iets ruimer

    // ✨ Bovenste rij
    printf("\n" INDENT "\033[1;33m");
    for (int i = 0; i < breedte; i++) printf("✨");
    printf("\n");

    // 🏆 Tekst gecentreerd
    int pad = (breedte - strlen(schat)) / 2;
    printf(INDENT "%*s\033[1;35m%s\033[0m\n", (int)pad, "", schat);

    // ✨ Onderste rij
    printf(INDENT "\033[1;33m");
    for (int i = 0; i < breedte; i++) printf("✨");
    printf("\033[0m\n");
    usleep(300000);

    // 🎉 GEFELICITEERD-box
    int boxwidth = 48;
    printf(INDENT "\033[1;36m╔");
    for (int i = 0; i < boxwidth; i++) printf("═");
    printf("╗\n");

    // 🎉 GEFELICITEERD!
    char* r1 = "🎉 GEFELICITEERD! 🎉";
    int r1_pad = (boxwidth - strlen(r1)) / 2;
    printf(INDENT "║%*s\033[1;32m%s\033[1;36m%*s║\n",
       (int)r1_pad, "", r1, (int)(boxwidth - strlen(r1) - r1_pad), "");

    // Jij bent de kampioen!
    char* r2 = "Jij bent de kampioen!";
    int r2_pad = (boxwidth - strlen(r2)) / 2;
    printf(INDENT "║%*s\033[1;34m%s\033[1;36m%*s║\n",
       (int)r2_pad, "", r2, (int)(boxwidth - strlen(r2) - r2_pad), "");

    printf(INDENT "╚");
    for (int i = 0; i < boxwidth; i++) printf("═");
    printf("╝\033[0m\n");

    // Confetti 🎊 veelkleurig, herhalend, verspringend
    const char* kleuren[] = {
        "\033[1;31m* \033[1;33m* \033[1;32m* \033[1;36m* \033[1;35m* \033[1;34m*",
        "\033[1;35m* \033[1;34m* \033[1;31m* \033[1;32m* \033[1;36m* \033[1;33m*",
        "\033[1;36m* \033[1;31m* \033[1;35m* \033[1;33m* \033[1;32m* \033[1;34m*",
    };
    for (int i = 0; i < 12; i++) {
        printf(INDENT "%s\033[0m\n", kleuren[i % 3]);
        usleep(100000);
    }

    save_game("save.txt", player, rooms, room_count);
    break;
}


        print_doors(current);
        printf("Kies een deur: ");
        char input[10];
        int choice;
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Ongeldige invoer. Typ een kamernummer.\n");
            continue;
        }

        int valid = 0;
        for (int i = 0; i < 4; i++) {
            if (current->connections[i] == choice) {
                valid = 1;
                break;
            }
        }

        if (valid) {
            player->location = choice;
            save_game("save.txt", player, rooms, room_count);
        } else {
            printf("Ongeldige keuze. Probeer opnieuw.\n");
        }
    }

    printf("\nSpel afgesloten.\n");
    free_dungeon(rooms, room_count);
    free(player);
    return 0;
}
