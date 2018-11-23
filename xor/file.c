#include <stdlib.h>
#include <stdio.h>
#include "file.h"

void save_matrix(char *path, float matrix[], size_t nb_element)
{
    FILE *f = fopen(path, "w");
    float *buffer = matrix;
    for (size_t i = 0; i < nb_element; i++)
    {
        printf("%f\n", *(buffer + i));
    }
    fwrite(buffer, sizeof(float), nb_element, f);
    fclose(f);
}

void get_matrix(float *buffer, char *path, size_t nb_element)
{
    FILE *f = fopen(path, "r");
    fread(buffer, sizeof(float), nb_element, f);
    fclose(f);
}
