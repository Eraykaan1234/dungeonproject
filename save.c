#include <stdio.h>
#include <stdlib.h>
#include "dungeon.h"
#include "player.h"
#include "item.h"

void save_game(const char *filename, Player *player, Room **rooms, int room_count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Kan bestand niet openen om op te slaan");
        return;
    }

    fprintf(file, "%s %d %d %d\n", player->name, player->hp, player->damage, player->current_room);

    for (int i = 0; i < room_count; i++) {
        Room *r = rooms[i];
        fprintf(file, "ROOM %d ", r->id);
        for (int j = 0; j < 4; j++) {
            fprintf(file, "%d ", r->connections[j]);
        }
        fprintf(file, "%d ", r->visited);
        fprintf(file, "%d ", r->has_treasure);

        if (r->item != NULL) {
            fprintf(file, "ITEM %d %d ", r->item->type, r->item->value);
        } else {
            fprintf(file, "NOITEM ");
        }

        if (r->monster != NULL) {
            fprintf(file, "MONSTER %s %d %d\n", r->monster->name, r->monster->hp, r->monster->damage);
        } else {
            fprintf(file, "NOMONSTER\n");
        }
    }

    fclose(file);
}

void load_game(const char *filename, Player *player, Room ***rooms_ptr, int *room_count_ptr) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Kan bestand niet openen om te laden");
        return;
    }

    fscanf(file, "%s %d %d %d", player->name, &player->hp, &player->damage, &player->current_room);

    Room **rooms = malloc(sizeof(Room*) * 100);
    int count = 0;

    while (!feof(file)) {
        char label[20];
        fscanf(file, "%s", label);
        if (strcmp(label, "ROOM") != 0) break;

        Room *r = malloc(sizeof(Room));
        fscanf(file, "%d", &r->id);
        for (int i = 0; i < 4; i++) {
            fscanf(file, "%d", &r->connections[i]);
        }
        fscanf(file, "%d", &r->visited);
        fscanf(file, "%d", &r->has_treasure);

        char item_label[20];
        fscanf(file, "%s", item_label);
        if (strcmp(item_label, "ITEM") == 0) {
            r->item = malloc(sizeof(Item));
            int type, value;
            fscanf(file, "%d %d", &type, &value);
            r->item->type = type;
            r->item->value = value;
        } else {
            r->item = NULL;
        }

        char monster_label[20];
        fscanf(file, "%s", monster_label);
        if (strcmp(monster_label, "MONSTER") == 0) {
            r->monster = malloc(sizeof(Monster));
            r->monster->name = malloc(50);
            fscanf(file, "%s %d %d", r->monster->name, &r->monster->hp, &r->monster->damage);
        } else {
            r->monster = NULL;
        }

        rooms[count++] = r;
    }

    *rooms_ptr = rooms;
    *room_count_ptr = count;

    fclose(file);
}
