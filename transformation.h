#include "types.h"

double cart_y(double y_screen, usint height);
uschar* grayscale(usint width, usint height, uschar* image);
void contrast(uschar *col, usint N);
void cut_unuseful_areas_rgba(uschar* img, usint width, usint height);