#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "../img_operations/rect.h"
#include "../img_operations/segmentation_tools/list.h"


int get_value_list(List *l, int index)
{
    return *(l->letter + index);
}

void save_letters(char *path, List *l, int size_of_letter, int nb_of_letter)
{
    FILE *f = fopen(path, "w");
    float letter[size_of_letter * nb_of_letter];
    size_t index = 0;
    List *curr = l->next;
    while (curr->width != -2)
    {
        for (int y = 0; y < curr->height; y++)
        {
            for (int x = 0; x < curr->width; x++)
            {
                letter[index] = (float)get_value_list(curr, y * curr->width + x);
                index++;
            }
        }
        curr = curr->next;
    }
    fwrite(letter, sizeof(float), size_of_letter * nb_of_letter, f);
    fclose(f);
}

void get_letters_from_file(char *path, float *buffer, int size_of_letter, size_t nb_of_letters)
{
    FILE *f = fopen(path, "r");
    size_t size = nb_of_letters * size_of_letter;
    size_t error = fread(buffer, sizeof(float), size, f);
    if (error != size)
        errx(1, "Reading error");
    fclose(f); 
}
