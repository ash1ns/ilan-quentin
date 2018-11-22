#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include "rect.h"

void segment(int input[], size_t row, size_t col, int ret[]);
size_t get_Rect(int input[], size_t row, size_t col, Rect ret[]);
size_t write_rect_array(int main_image[], size_t col, Rect input[], size_t inputlength);

#endif
