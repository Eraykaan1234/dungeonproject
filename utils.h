#ifndef UTILS_H
#define UTILS_H

typedef enum { HEAL, DAMAGE } ItemType;

typedef struct Item {
    ItemType type;
    int value;
} Item;

int random_getal_tussen(int min, int max);

#endif
