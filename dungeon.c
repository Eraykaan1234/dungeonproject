// dungeon.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dungeon.h"
#include "combat.h"
#include "player.h"
#include <string.h>


Room *create_room(int id) {
    Room *room = malloc(sizeof(Room));
    room->id = id;
    room->monster = NULL;
    room->item = NULL;
    room->has_treasure = 0;
    room->visited = 0;
    for (int i = 0; i < 4; i++) {
        room->connections[i] = -1;
    }
    return room;
}

void connect_rooms(Room **rooms, int from, int to) {
    for (int i = 0; i < 4; i++) {
        if (rooms[from]->connections[i] == -1) {
            rooms[from]->connections[i] = to;
            break;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (rooms[to]->connections[i] == -1) {
            rooms[to]->connections[i] = from;
            break;
        }
    }
}

void generate_dungeon(Room ***rooms_ptr, int count) {
    srand(time(NULL));
    Room **rooms = malloc(sizeof(Room*) * count);
    for (int i = 0; i < count; i++) {
        rooms[i] = create_room(i);
    }
    for (int i = 1; i < count; i++) {
        int connect_to = rand() % i;
        connect_rooms(rooms, i, connect_to);
    }
    int monster_count = count / 4;
    int item_count = count / 4;
    for (int i = 0; i < monster_count; i++) {
        int idx = rand() % count;
        if (!rooms[idx]->monster) {
            Monster *m = malloc(sizeof(Monster));
          if (rand() % 2) {
    strcpy(m->name, "Goblin");
    m->hp = 8;
    m->damage = 3;
} else {
    strcpy(m->name, "Orc");
    m->hp = 12;
    m->damage = 4;
}
            rooms[idx]->monster = m;
        }
    }
    for (int i = 0; i < item_count; i++) {
        int idx = rand() % count;
        if (!rooms[idx]->item) {
            Item *it = malloc(sizeof(Item));
            if (rand() % 2) {
                it->type = HEAL;
                it->value = 5;
            } else {
                it->type = DAMAGE;
                it->value = 2;
            }
            rooms[idx]->item = it;
        }
    }
    int treasure_room;
    do {
        treasure_room = rand() % count;
    } while (treasure_room == 0);
    rooms[treasure_room]->has_treasure = 1;

    *rooms_ptr = rooms;
}

void enter_room(Room *room, Player *player) {
    printf("Je betreedt kamer %d.\n", room->id);
    if (room->item) {
        if (room->item->type == HEAL) {
            player->hp += room->item->value;
            printf("Je vond een healing item! +%d hp (nu %d hp)\n", room->item->value, player->hp);
        } else {
            player->damage += room->item->value;
            printf("Je vond een damage item! +%d damage (nu %d damage)\n", room->item->value, player->damage);
        }
        free(room->item);
        room->item = NULL;
    }
    if (room->monster) {
        printf("Er is een %s in de kamer!\n", room->monster->name);
        combat(player, room->monster);
        if (room->monster->hp <= 0) {
            free(room->monster);
            room->monster = NULL;
        }
    }
}

void print_doors(Room *room) {
    printf("Deuren naar kamers: ");
    for (int i = 0; i < 4; i++) {
        if (room->connections[i] != -1) {
            printf("%d ", room->connections[i]);
        }
    }
    printf("\n");
}

void free_dungeon(Room **rooms, int count) {
    for (int i = 0; i < count; i++) {
        if (rooms[i]->monster) free(rooms[i]->monster);
        if (rooms[i]->item) free(rooms[i]->item);
        free(rooms[i]);
    }
    free(rooms);
}
