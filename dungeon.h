#ifndef DUNGEON_H
#define DUNGEON_H

typedef struct Room {
    int id;
    int visited;
    int monster;  // 0 = geen, 1 = goblin, 2 = orc
    int item;     // 0 = geen, 1 = healing, 2 = damage boost
    int treasure; // 0 = nee, 1 = ja
    struct Room **neighbors;
    int neighbor_count;
} Room;

void generateDungeon(int numberOfRooms);
void freeDungeon();
    
extern Room** dungeon;
extern int dungeonSize;

#endif
