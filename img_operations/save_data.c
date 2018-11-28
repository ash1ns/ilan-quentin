#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "rect.h"

size_t size_letter = 28 * 28;

void save_letters(char *path, int main_image[], size_t col, Rect input[], size_t inputLen)
{
    FILE *f = fopen(path, "w");
    float letter[size_letter];
    //Change size with size_letter * sizeof(float)
    for (size_t i = 0; i < inputLen; i++)
    {
        size_t index = 0;
        size_t x1 = input[i].x1;
        size_t x2 = input[i].x2;
        size_t y1 = input[i].y1;
        size_t y2 = input[i].y2;
        // between [y1,y2]
        for (size_t y = y1; y < y2; y++)
        {
             //values between [x1,x2]
            for (size_t x = x1; x <= x2; x++)
            {
                if (index > size_letter)
                    break;
                if (main_image[y * col + x] == 2)
                    letter[index] = (float)0;
                else
                    letter[index] = (float)1;
                index++;
            }
            if (index > size_letter)
                break;
        }
        fwrite(letter, sizeof(float), size_letter, f);
    }
    fclose(f);
}

void get_letters_from_file(char *path, float *buffer, size_t nb_of_letters)
{
    FILE *f = fopen(path, "r");
    size_t size = nb_of_letters * size_letter;
    size_t error = fread(buffer, sizeof(float), size, f);
    if (error != size)
        errx(1, "Reading error");

    fclose(f);

        
}

