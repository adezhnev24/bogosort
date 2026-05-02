#include "types.h"

uschar* load_png(const char* filename, usint* width, usint* height);
void convert_into_rgba(uschar* col, uschar* finish, usint width, usint height);
void save_png(const char* filename, uschar* image, usint width, usint height);
