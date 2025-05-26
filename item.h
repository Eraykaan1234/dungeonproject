#ifndef ITEM_H
#define ITEM_H

typedef enum {
    HEAL,
    DAMAGE
} ItemType;

typedef struct Item {
    char name[20];
    ItemType type;
    int value;
} Item;

#endif
