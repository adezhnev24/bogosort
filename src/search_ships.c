#include <stdlib.h>
#include "search_ships.h"
#include "ad_stack.h"

int dfs_iter(uschar* bin, uschar* visited, usint width, usint height, 
             int sx, int sy, long* sumx, long* sumy) {
    ADStack* s = ad_stack_create(width * height); //мой именной стек

    if (!s) return 0;

    int size = 0, index;
    int x, y, nx, ny, nidx;
    int i;

    static const int dx[4] = {-1, 1, 0, 0};
    static const int dy[4] = {0, 0, -1, 1}; // направления движения (без обхода по диагонали)

    ad_push(s, sy * width + sx);
    visited[sy * width + sx] = 1;

    while (!ad_stack_is_empty(s)) {
        index = ad_pop(s);
        x = index % width;
        y = index / width;

        size++;
        *sumx += x;
        *sumy += y;
 
        for (i = 0; i < 4; i++) {
            nx = x + dx[i]; ny = y + dy[i];

            if (nx >= 0 && nx < (int)width && ny >= 0 && ny < (int)height) {
                nidx = ny * width + nx;

                if (bin[nidx] && !visited[nidx]) {
                    visited[nidx] = 1;
                    ad_push(s, nidx);
                }
            }
        }
    }

    ad_stack_destroy(s);
    return size;
}

int find_ships(uschar* bin, usint width, usint height,
               Ship* out, int max_ships) {
    usint x, y, index;
    int size, cnt = 0;
    long sx, sy;
    int cx, cy;
    uschar* visited;

    visited = (uschar*)calloc(width * height, sizeof(uschar));
    if (!visited) return -1;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            index = y * width + x;

            if (bin[index] && !visited[index]) {
                sx = 0, sy = 0;

                size = dfs_iter(bin, visited, width, height, x, y, &sx, &sy);

                if (1 <= size && size <= 9 && cnt < max_ships) {
                    out[cnt].cx = sx / size;
                    out[cnt].cy = sy / size;
                    out[cnt].size = size;
                    cnt++;
                }
            }
        }
    }

    free(visited);
    return cnt;
}
