#ifndef ITEM_H
#define ITEM_H

typedef enum { HEAL, DAMAGE } ItemType;

typedef struct Item {
    ItemType type;
    int value;
} Item;

#endif
