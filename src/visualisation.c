#include "visualisation.h"

void draw_cross(uschar* image, usint width, usint height, int x, int y)
{
    int dx, dy, nx, ny, idx;

    for (dx = -2; dx <= 2; dx++) {
        nx = x + dx;
        ny = y;

        if (nx >= 0 && nx < (int)width && ny >= 0 && ny < (int)height) {
            idx = 4 * (ny * width + nx);
            image[idx]     = 0;
            image[idx + 1] = 255; // зелёный
            image[idx + 2] = 0;
            image[idx + 3] = 255;
        }
    }

    for (dy = -2; dy <= 2; dy++) {
        nx = x;
        ny = y + dy;

        if (nx >= 0 && nx < (int)width && ny >= 0 && ny < (int)height) {
            idx = 4 * (ny * width + nx);
            image[idx]     = 0;
            image[idx + 1] = 255; // зелёный
            image[idx + 2] = 0;
            image[idx + 3] = 255;
        }
    }
}
