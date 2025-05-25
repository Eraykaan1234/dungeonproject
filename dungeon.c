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
    // Eenvoudige connecties: lineair
    for (int i = 0; i < dungeonSize - 1; i++) {
        dungeon[i]->neighbor_count = 1;
        dungeon[i]->neighbors = malloc(sizeof(Room*));
        dungeon[i]->neighbors[0] = dungeon[i+1];
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
