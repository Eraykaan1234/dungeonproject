#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dungeon.h"
#include "player.h"
#include "item.h"

void save_game(const char *filename, Player *player, Room **rooms, int room_count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Kan bestand niet openen om op te slaan");
        return;
    }

    fprintf(file, "%d %d %d\n", player->location, player->hp, player->damage);
    fprintf(file, "%d\n", room_count);

    for (int i = 0; i < room_count; i++) {
        Room *r = rooms[i];
        fprintf(file, "%d ", r->id);
        for (int j = 0; j < 4; j++) {
            fprintf(file, "%d ", r->connections[j]);
        }
        fprintf(file, "%d %d ", r->visited, r->has_treasure);

        if (r->item) {
            fprintf(file, "ITEM %d %d ", r->item->type, r->item->value);
        } else {
            fprintf(file, "NOITEM ");
        }

        if (r->monster) {
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

    fscanf(file, "%d %d %d", &player->location, &player->hp, &player->damage);
    fscanf(file, "%d", room_count_ptr);

    int count = *room_count_ptr;
    Room **rooms = malloc(sizeof(Room*) * count);

    for (int i = 0; i < count; i++) {
        Room *r = malloc(sizeof(Room));
        r->monster = NULL;
        r->item = NULL;
        fscanf(file, "%d", &r->id);
        for (int j = 0; j < 4; j++) {
            fscanf(file, "%d", &r->connections[j]);
        }
        fscanf(file, "%d %d", &r->visited, &r->has_treasure);

        char buffer[20];
        fscanf(file, "%s", buffer);
        if (strcmp(buffer, "ITEM") == 0) {
            r->item = malloc(sizeof(Item));
            int type, value;
            fscanf(file, "%d %d", &type, &value);
            r->item->type = type;
            r->item->value = value;
            fscanf(file, "%s", buffer); // Lees MONSTER/NOMONSTER
        }

        if (strcmp(buffer, "MONSTER") == 0) {
            r->monster = malloc(sizeof(Monster));
            fscanf(file, "%s %d %d", r->monster->name, &r->monster->hp, &r->monster->damage);
        }

        rooms[i] = r;
    }

    *rooms_ptr = rooms;
    fclose(file);
}
