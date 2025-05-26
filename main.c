#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dungeon.h"
#include "player.h"
#include "combat.h"
#include "save.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Gebruik: %s <aantal_kamers> of %s load\n", argv[0], argv[0]);
        return 1;
    }

    Player *player = malloc(sizeof(Player));
    Room **rooms = NULL;
    int room_count = 0;

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
        printf("Game over.\n");
        break;
    }

    Room *current = rooms[player->location];

   if (!current->visited) {
    enter_room(current, player);
    current->visited = 1;

    // Hier komt de dood-check meteen na gevecht of item
    if (player->hp <= 0) {
        printf("Game over.\n");
        break;
    }
} else {
    printf("Je bent terug in kamer %d.\n", current->id);
}

    if (player->hp <= 0) {
        printf("Game over.\n");
        break;
    }

    if (current->has_treasure) {
        printf("Je hebt de schat gevonden! Gefeliciteerd!\n");
        break;
    }

    print_doors(current);
    printf("Kies een deur: ");
    int choice;
    scanf("%d", &choice);

    int valid = 0;
    for (int i = 0; i < 4; i++) {
        if (current->connections[i] == choice) {
            valid = 1;
            break;
        }
    }

    if (valid) {
        player->location = choice;
    } else {
        printf("Ongeldige keuze. Probeer opnieuw.\n");
    }
}

    if (player->hp > 0) {
        printf("Spel opgeslagen.\n");
        save_game("save.txt", player, rooms, room_count);
    } else {
        printf("Game over.\n");
    }

    free_dungeon(rooms, room_count);
    free(player);
    return 0;
}
