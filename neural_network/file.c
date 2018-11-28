#include <stdlib.h>
#include <stdio.h>
#include "file.h"
#include "err.h"

void save_matrix(char *path, float matrix[], size_t nb_element)
{
    FILE *f = fopen(path, "w");
    float *buffer = matrix;
    fwrite(buffer, sizeof(float), nb_element, f);
    fclose(f);
}

void get_matrix(float *buffer, char *path, size_t nb_element)
{
    FILE *f = fopen(path, "r");
    size_t error = fread(buffer, sizeof(float), nb_element, f);
    if (error != nb_element)
        errx(1, "Reading error");
    fclose(f);
}
