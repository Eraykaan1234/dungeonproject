#include <stdio.h>
#include "save.h"
#include "dungeon.h" 
int save_game(const char *filename, Player *player, Room *rooms[], int room_count) {
    FILE *file = fopen(filename, "w");
    if (!file) return 0;

    fprintf(file, "%d %d %d\n", player->current_room_id, player->hp, player->damage);
    fprintf(file, "%d\n", room_count);

    for (int i = 0; i < room_count; i++) {
        Room *r = rooms[i];
        fprintf(file, "%d %d %d %d %d\n", r->id, r->visited, r->has_monster, r->has_item, r->has_treasure);
    }

    fclose(file);
    return 1;
}

int load_game(const char *filename, Player *player, Room *rooms[], int room_count) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    fscanf(file, "%d %d %d", &player->current_room_id, &player->hp, &player->damage);
    int loaded_room_count;
    fscanf(file, "%d", &loaded_room_count);

    if (loaded_room_count != room_count) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < room_count; i++) {
        int id, visited, has_monster, has_item, has_treasure;
        fscanf(file, "%d %d %d %d %d", &id, &visited, &has_monster, &has_item, &has_treasure);
        Room *r = rooms[i];
        r->id = id;
        r->visited = visited;
        r->has_monster = has_monster;
        r->has_item = has_item;
        r->has_treasure = has_treasure;
    }

    fclose(file);
    return 1;
}
