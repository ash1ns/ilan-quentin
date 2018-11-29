#include <stdio.h>
#include <stdlib.h>
#include "../rect.h"
#include "list.h"

void free_list(List *l)
{
    // we destroy l 
    List *curr = l->next;
    free(l);
    while (curr->width != -2)
    {
        free(curr->letter);
        List *next = curr->next;
        free(curr);
        curr = next;
    }
    free(curr);
}

int get_value(List *l, int index)
{
    return *(l->letter + index);
}

void printlist(List *l)
{
    List *curr = l->next;
    while (curr->width != -2)
    {
        for (int y = 0; y < curr->height; y++)
        {
            for (int x = 0; x < curr->width; x++)
            {
                printf("%i ", get_value(curr ,y * curr->width + x));
            }
            printf("\n");
        }
        curr = curr->next;
        printf("\n===============\n\n");
    }
}

List *to_list(int main_image[], size_t col, Rect input[], size_t inputlength)
{
    // the returned list first element have -1 -1 on width on height and the
    // last -2 -2.

    // for the first element of the list the pointer is initialisez to -1 
    List *ret;
    ret = (List *)malloc(sizeof (List));
    ret->width = -1;
    ret->height = -1;
    
    List *prev = ret;
    for (size_t i = 0; i < inputlength; i++)
    {
        // initilising next pointer
        List *curr;
        curr = (List *)malloc(sizeof (List));
        prev->next = curr;

        size_t x1 = input[i].x1;
        size_t x2 = input[i].x2;
        size_t y1 = input[i].y1;
        size_t y2 = input[i].y2;

        // define height and width of curr
        int width = ((int)(x2 - x1)) + 1;
        int height = ((int)(y2 - y1)) + 1;

        curr->width = width;
        curr->height = height;

        // define the array letter
        int *letter;
        letter = malloc(width * height * sizeof(int));
        curr->letter = letter;

        int *currletter = letter;

        while (y1 <= y2)
        {
            for (size_t x = x1; x <= x2; x++)
            {
                if (main_image[y1 * col + x] == 2)
                {
                    // add a 0 to the pointer
                    *currletter = 0;
                }
                else
                {
                    // add a 1 to the pointer
                    *currletter = 1;
                }
                currletter++;
            }
            y1++;
        }

        // we make curr to the previous value;
        prev = curr;
    }

    // adding the "empty element" significated that it is the end of the list
    List *last = malloc(sizeof(List));
    last->width = -2;
    last->height = -2;

    prev->next = last;

    return ret;
}
