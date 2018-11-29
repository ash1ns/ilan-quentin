#ifndef LIST_OP_H
#define LIST_OP_H

#include "list.h"
#include "../rect.h"

int get_value(List *l, int index);
List *to_list(int main_image[], size_t col, Rect input[], size_t inputlength);
void printlist(List *l);
void free_list(List *l);

#endif
