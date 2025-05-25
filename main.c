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
        load_game(&rooms, &room_count, player);
        printf("Spel geladen.\n");
    } else {
        room_count = atoi(argv[1]);
        generate_dungeon(&rooms, room_count);
        init_player(player);
        printf("Nieuw spel gestart met %d kamers.\n", room_count);
    }

    int playing = 1;
    while (playing) {
        Room *current = rooms[player->location];
        if (!current->visited) {
            enter_room(current, player);
            current->visited = 1;
        } else {
            printf("Je bent terug in kamer %d.\n", current->id);
        }

        if (current->has_treasure) {
            printf("Je hebt de schat gevonden! Gefeliciteerd!\n");
            break;
        }

        print_doors(current);
        printf("Kies een deur: ");
        int choice;
        scanf("%d", &choice);
        player->location = choice;
    }

    save_game(rooms, room_count, player);
    free_dungeon(rooms, room_count);
    free(player);
    return 0;
}
