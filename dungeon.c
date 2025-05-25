#include <stdlib.h>
#include "dungeon.h"

Room** dungeon = NULL;
int dungeonSize = 0;

void generateDungeon(int numberOfRooms) {
    dungeonSize = numberOfRooms;
    dungeon = malloc(sizeof(Room*) * dungeonSize);
    for (int i = 0; i < dungeonSize; i++) {
        dungeon[i] = malloc(sizeof(Room));
        dungeon[i]->id = i;
        dungeon[i]->visited = 0;
        dungeon[i]->monster = 0;
        dungeon[i]->item = 0;
        dungeon[i]->treasure = 0;
        dungeon[i]->neighbor_count = 0;
        dungeon[i]->neighbors = NULL;
    }
    // Simpel voorbeeld connecties
    if (dungeonSize > 1) {
        dungeon[0]->neighbor_count = 1;
        dungeon[0]->neighbors = malloc(sizeof(Room*));
        dungeon[0]->neighbors[0] = dungeon[1];
    }
}

void freeDungeon() {
    for (int i = 0; i < dungeonSize; i++) {
        free(dungeon[i]->neighbors);
        free(dungeon[i]);
    }
    free(dungeon);
    dungeon = NULL;
    dungeonSize = 0;
}
