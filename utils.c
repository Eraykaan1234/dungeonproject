#include <stdlib.h>
#include <time.h>
#include "utils.h"

int random_getal_tussen(int min, int max) {
    return rand() % (max - min + 1) + min;
}