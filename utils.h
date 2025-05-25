#ifndef UTILS_H
#define UTILS_H

typedef struct Item {
    char name[20];
    int hp_boost;
    int dmg_boost;
} Item;

int randint(int min, int max);
char *read_line();

#endif
