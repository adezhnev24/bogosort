#ifndef SEARCH_SHIPS_H
#define SEARCH_SHIPS_H

#include "types.h"

typedef struct {
    int cx;
    int cy;
    int size;
} Ship;

int dfs_iter(uschar* bin, uschar* visited,
             usint width, usint height,
             int sx, int sy,
             long* sumx, long* sumy);

int find_ships(uschar* bin,
               usint width,
               usint height,
               Ship* out,
               int max_ships);

#endif