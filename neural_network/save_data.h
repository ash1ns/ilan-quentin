#ifndef SAVE_DATA_H
#define SAVE_DATA_H

#include "../img_operations/rect.h"
#include "../img_operations/segmentation_tools/list.h"

void save_letters(char *path, List *l, int size_of_letter, int nb_of_letter);
void get_letters_from_file(char *path, float *buffer, int size_of_letter, size_t nb_of_letter);
#endif
