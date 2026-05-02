#include <stdlib.h>
#include "transformation.h"

double cart_y(double y_screen, usint height) {
    return (double)(height - 1) - y_screen;
}

uschar* grayscale(usint width, usint height, uschar* image) {
    uschar *gray;
    usint i, idx, N = width * height;

    gray = (uschar*)malloc(N * sizeof(uschar));
    if (!gray) return NULL;

    for (i = 0; i < N; i++) {
        idx = 4*i;
        gray[i] = (uschar)((0.299*image[idx] + 0.587*image[idx + 1] + 0.114*image[idx + 2])); // формула серого цвета
    }

    return gray;
}

void contrast(uschar *col, usint N)
{
    for (usint i = 0; i < N; i++) {
        col[i] = (col[i] > 45) ? 255 : 0;
    }
}

void cut_unuseful_areas_rgba(uschar* img, usint width, usint height)
{
    usint x, y;
    usint idx;

    double yc;

    double x0 = width - 1;
    double y0 = cart_y(1.0, height);

    double a = 0.456 * width;
    double b = 0.488 * height;

    double dx, dy;
    double value;
    double orient1, orient2, orient3;

    double x1 = 0.20925 * width, y1 = cart_y(0.0, height);
    double x2 = 0.3078125 * width, y2 = cart_y((double)height, height);
    double Y1 = cart_y(0.03245749613*height, height);

    double xx1 = 0.23125 * width, yy1 = cart_y(0.24884 * height, height);
    double xx2 = 0.328125 * width, yy2 = cart_y(0.0, height);

    double _X_1 = 0.3046875*width, _X_2 = 0.3203125*width;

    double xxx1 = 0.41875 * width;
    double yyy1 = cart_y(0.463679 * height, height);

    double xxxx1 = 0.39755625 * width;
    double yyyy1 = cart_y(0.76816074 * height, height);
    double xxxx2 = 0.47265625 * width;
    double yyyy2 = cart_y((double)height, height);

    double _y1 = cart_y(0.65996908809 * height, height);
    double _y2 = cart_y(0.69088098918 * height, height);

    double __x1 = 0.43046875 * width;
    double __y1 = cart_y(0.48840803709 * height, height);
    double __y2 = cart_y(0.50695517774 * height, height);

    double _x_1 = 0.86125 * width;

    for (y = 0; y < height; y++) {
        yc = cart_y((double)y, height);

        for (x = 0; x < width; x++) {

            int erase = 0;

            //far upper
            if (yc > Y1) erase = 1;

            //Iran: ellipse//
            dx = x - x0;
            dy = yc - y0;
            value = (dx * dx)/(a * a) + (dy * dy)/(b * b);
            if (value <= 1.0)
                erase = 1;

            //left land
            orient1 = (x - x1)*(y2 - y1) - (yc - y1)*(x2 - x1);
            if (orient1 > 0) erase = 1;

            /* upper land */
            orient2 = (x - xx1)*(yy2 - yy1) - (yc - yy1)*(xx2 - xx1);
            if (orient2 > 0 && x < xxx1 && yc > yyy1)
                erase = 1;
            
            if (_X_1 < x && x < _X_2) erase = 1;

            /* lower land */
            if (x < xxxx1 && yc < yyy1)
                erase = 1;

            orient3 = (x - xxxx1)*(yyyy2 - yyyy1) - (yc - yyyy1)*(xxxx2 - xxxx1);

            if (orient3 > 0 && x > xxxx1)
                erase = 1;

            /* right land */
            if (x > _x_1)
                erase = 1;

            if (erase) {
                idx = 4 * (y * width + x);

                img[idx]     = 0;
                img[idx + 1] = 0;
                img[idx + 2] = 0;
                img[idx + 3] = 255;
            }
        }
    }
}
