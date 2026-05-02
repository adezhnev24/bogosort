#include <stdio.h>
#include <stdlib.h>
#include "image_work.h"
#include "lodepng.h"

uschar* load_png(const char* filename, usint* width, usint* height) {
    uschar* image = NULL;
    unsigned error = lodepng_decode32_file(&image, width, height, filename);
    if (error) {
        printf("error %u: %s\n", error, lodepng_error_text(error));
        return NULL;
    }
    return image;
}

void convert_into_rgba(uschar* col, uschar* finish, usint width, usint height) {
    usint i;
    for (i = 0; i < width * height; i++) {
        finish[i * 4]     = col[i];
        finish[i * 4 + 1] = col[i];
        finish[i * 4 + 2] = col[i];
        finish[i * 4 + 3] = 255;
    }
}

void save_png(const char* filename, uschar* image, usint width, usint height) {
    unsigned error = lodepng_encode32_file(filename, image, width, height);
    if (error) {
        printf("save error %u: %s\n", error, lodepng_error_text(error));
    }
}
