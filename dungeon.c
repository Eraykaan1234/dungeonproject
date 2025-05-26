#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dungeon.h"
#include "combat.h"
#include "player.h"
#include "utils.h"
#include "item.h"

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

    // Maak verbindingen
    for (int i = 1; i < count; i++) {
        int connect_to = rand() % i;
        connect_rooms(rooms, i, connect_to);
    }

    // Plaats de schat in een latere kamer
    int treasure_idx = count - 1 - rand() % (count / 4);
    rooms[treasure_idx]->has_treasure = 1;

    // Voeg monsters toe (1/3 van kamers)
    int monster_count = count / 3;
    int monsters_placed = 0;
    while (monsters_placed < monster_count) {
        int idx = rand() % count;
        if (!rooms[idx]->monster && !rooms[idx]->has_treasure) {
            Monster *m = malloc(sizeof(Monster));
            int type = rand() % 2;
            if (type == 0) {
                strcpy(m->name, "Goblin");
                m->hp = 8;
                m->damage = 3;
            } else {
                strcpy(m->name, "Orc");
                m->hp = 12;
                m->damage = 5;
            }
            rooms[idx]->monster = m;
            monsters_placed++;
        }
    }

    // Voeg items toe (1/3 van kamers)
    int item_count = count / 3;
    int items_placed = 0;
    while (items_placed < item_count) {
        int idx = rand() % count;
        if (!rooms[idx]->item && !rooms[idx]->has_treasure && !rooms[idx]->monster) {
            Item *it = malloc(sizeof(Item));
            int type = rand() % 2;
            if (type == 0) {
                it->type = HEAL;
                it->value = 5 + rand() % 6; // 5–10
            } else {
                it->type = DAMAGE;
                it->value = 1 + rand() % 3; // 1–3
            }
            rooms[idx]->item = it;
            items_placed++;
        }
    }

    *rooms_ptr = rooms;
}

void enter_room(Room *room, Player *player) {
    printf("\033[33m===========================\n");
    printf("\033[1mJe betreedt kamer %d\033[0m\n", room->id);
    printf("---------------------------\033[0m\n");

    // Items
    if (room->item) {
        if (room->item->type == HEAL) {
            player->hp += room->item->value;
            printf("Je vindt een healing item! +%d HP (\033[1m%d\033[0m)\n", room->item->value, player->hp);
        } else if (room->item->type == DAMAGE) {
            player->damage += room->item->value;
            printf("Je vindt een kracht-item! +%d damage (\033[1m%d\033[0m)\n", room->item->value, player->damage);
        }
        free(room->item);
        room->item = NULL;
    }

    // Monster
    if (room->monster) {
        fight(player, room);
    }

    printf("\033[33m===========================\033[0m\n");
}



void print_doors(Room *room) {
    printf("De kamer heeft deuren naar kamers: ");
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
