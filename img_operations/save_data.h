#ifndef SAVE_DATA_H
#define SAVE_DATA_H

#include "rect.h"

void save_letters(char *path, int main_image[], size_t col, Rect input[], size_t
inputLen);
void get_letters_from_file(char *path, float *buffer, size_t nb_of_letters);
#endif
