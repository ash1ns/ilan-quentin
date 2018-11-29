#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void removeLastLine(List *l)
{
    int *ret = malloc(l->height * l->width * sizeof(int));
    int *curr = ret;
    int *curr_int_l = l->letter;
    for (int y = 0; y < l->height; y++)
    {
        for (int x = 0; x < l->width; x++)
        {
            *curr = *curr_int_l;
            curr++;
            curr_int_l++;
        }
    }
    free(l->letter);
    l->letter = ret;
}

void removefirstLine(List *l)
{
    int *ret = malloc(l->height * l->width * sizeof(int));
    int *curr = ret;
    int *curr_int_l = l->letter + l->width;
    for (int y = 0; y < l->height; y++)
    {
        for (int x = 0; x < l->width; x++)
        {
            *curr = *curr_int_l;
            curr++;
            curr_int_l++;
        }
    }
    free(l->letter);
    l->letter = ret;
}

int isRowEmpty(int *letter, int width, int y)
{
    for (int x = 0; x < width; x++)
    {
        // if we have a black pixel return false
        if (*(letter + y * width + x) == 1)
        {
            return 0;
        }
    }
    return 1;
}

void shorten_el(List *l)
{
    int width = l->width;
    int y = 0;

    // shorten on the first lign to lign with pixel
    while (isRowEmpty(l->letter, width, y))
    {
        l->height -= 1;
        removefirstLine(l);
    }

    y = l->height - 1;
    while (isRowEmpty(l->letter, width, y))
    {
        l->height -= 1;
        y--;
        removeLastLine(l);
    }
    
}

void shorten(List *l)
{
    List *curr = l->next;
    while (curr->width != -2)
    {
        shorten_el(curr);
        curr = curr->next;
    }
}
