#include <stdio.h>
#include <stdlib.h>
#include "dungeon.h"
#include "player.h"
#include "combat.h"

void printRoom(Room* room) {
    printf("Kamer %d\n", room->id);
    printf("Deuren naar kamers:");
    for (int i = 0; i < room->neighbor_count; i++) {
        printf(" %d", room->neighbors[i]->id);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Gebruik: %s <aantal kamers>\n", argv[0]);
        return 1;
    }

    int numberOfRooms = atoi(argv[1]);
    if (numberOfRooms < 2) {
        printf("Aantal kamers moet minstens 2 zijn.\n");
        return 1;
    }

    generateDungeon(numberOfRooms);

    Player player;
    initPlayer(&player);

    printf("Dungeon met %d kamers gegenereerd.\n", numberOfRooms);

    // Voorbeeld: plaats 1 monster in kamer 1
    if (numberOfRooms > 1) dungeon[1]->monster = 1;

    while (1) {
        Room* currentRoom = dungeon[player.currentRoom];
        if (!currentRoom->visited) {
            printf("Je betreedt kamer %d.\n", currentRoom->id);
            currentRoom->visited = 1;
            if (currentRoom->monster) {
                fight(&player, currentRoom);
                if (player.hp <= 0) {
                    printf("Game over!\n");
                    break;
                }
            }
            if (currentRoom->treasure) {
                printf("Je hebt de schat gevonden! Gefeliciteerd!\n");
                break;
            }
        } else {
            printf("Je bent terug in kamer %d.\n", currentRoom->id);
        }

        printRoom(currentRoom);
        printf("Kies een deur om door te gaan (id): ");
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Ongeldige invoer. Exit.\n");
            break;
        }

        int valid = 0;
        for (int i = 0; i < currentRoom->neighbor_count; i++) {
            if (currentRoom->neighbors[i]->id == choice) {
                player.currentRoom = choice;
                valid = 1;
                break;
            }
        }
        if (!valid) {
            printf("Ongeldige keuze, probeer opnieuw.\n");
        }
    }

    freeDungeon();
    return 0;
}
