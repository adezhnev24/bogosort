#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "lodepng.h"

#include "transformation.h"
#include "image_work.h"
#include "visualisation.h"
#include "search_ships.h"

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;

    uschar *image = NULL, *mask_rgba = NULL, *gray = NULL;
    uschar *contrast_rgba = NULL;
    Ship *ships = NULL;
    usint width, height, N;

    // загружаем изображение
    image = load_png(argv[1], &width, &height);
    if (!image) return 1;
    N = width * height;
    
    // делаем копию, чтобы посмотреть на кораблики
    mask_rgba = (uschar*)malloc(4*N*sizeof(uschar));
    if (!mask_rgba) {
        free(image);
        return 1;
    }
    memcpy(mask_rgba, image, 4 * N);

    // делаем маску на копии
    cut_unuseful_areas_rgba(mask_rgba, width, height);
    save_png("masked.png", mask_rgba, width, height);

    // делаем изображение в ч/б по формуле
    gray = grayscale(width, height, mask_rgba);
    free(mask_rgba);

    if (!gray) {
        free(image);
        return 1;
    }

    // делаем контрастную версию ч/б изображения. 
    // потом можем на неё посмотреть в формате png
    contrast(gray, N);

    contrast_rgba = (uschar*)malloc(4 * N);
    if (!contrast_rgba) {
        free(image);
        free(gray);
        return 1;
    }

    convert_into_rgba(gray, contrast_rgba, width, height);
    save_png("contrast.png", contrast_rgba, width, height);

    free(contrast_rgba);

    // считаем корабли
    ships = (Ship*)malloc((N / 2)* sizeof(Ship));
    if (!ships) {
        free(image);
        free(gray);
        return 1;
    }
    int ships_count = find_ships(gray, width, height, ships, N/2);
    printf("Ships: %d\n", ships_count);

    // рисуем корабли на png-картинке, отмечаем их зелёными крестиками
    for (int i = 0; i < ships_count; i++) {
        draw_cross(image, width, height, ships[i].cx, ships[i].cy);
    }
    save_png("result.png", image, width, height);

    // не забыли почистить память
    free(image);
    free(gray);
    free(ships);

    return 0;
}