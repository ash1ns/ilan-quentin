#include <stdlib.h>
#include "list.h"

//test
#include "list_op.h"
#include <stdio.h>

int recizevalue = 28;

int pgcd(int a, int b)
{
    while (b != 0)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void printletter(List *l)
{
    for (int y = 0; y < l->height; y++)
    {
        for (int x = 0; x < l->width; x++)
        {
            printf("%i ", *(l->letter + y * l->width + x));
        }
    }
}

void divide(List *l, int c)
{
    // not possible to be other
    int ret_width = recizevalue;
    int *ret = malloc(ret_width * ret_width * sizeof(int));
    

    for (int y = 0; y < ret_width; y++)
    {
        for (int x = 0; x < ret_width; x++)
        {
            int add = 0;
            for (int y2 = y * c; y2 < y * c + c; y2++)
            {
                for (int x2 = x * c; x2 < x * c + c; x2++)
                {
                    add += *(l->letter + y2 * l->width + x2);
                }
            }
            if (add >= c * c / 2 + (c * c) % 2)
            {
                *(ret + y * ret_width + x) = 1;
            }
            else 
            {
                *(ret + y * ret_width + x) = 0;
            }
        }
    }
    /*
    for (int y = 0; y < l->height; y += c)
    {
        for (int x = 0; x < l->width; x += c)
        {
            int add = 0;
            for (int y2 = y; y2 < y + c; y2++)
            {
                for (int x2 = x; x2 < x + c; x2++)
                {
                    add += *(l->letter + y2 * l->width + x2);
                }
            }
            int val = 0;
            if (add >= c * c / 2 + (c * c) % 2)
            {
                val = 1;
            }
            *(ret + (y/c) * ret_width + x/c) = val;
        }
    }
    */
    free(l->letter);
    l->letter = ret;
    l->width = ret_width;
    l->height = ret_width;
}

void my_multiply(List *l, int b)
{
    int *ret = malloc(l->width * l->width * b * b * sizeof(int));
    int ret_width = l->width * b;
    for (int y = 0; y < l->height; y++)
    {
        for (int x = 0; x < l->width; x++)
        {
            int val = *(l->letter + y * l->width + x);
            for (int y2 = y * b; y2 < y * b + b; y2++)
            {
                for (int x2 = x * b; x2 < x * b + b; x2++)
                {
                    *(ret + y2 * ret_width + x2) = val;
                }
            }
            /*
            int val = *(l->letter + y * l->width + x);
            for (int y2 = y; y2 < y + b; y2++)
            {
                for (int x2 = x; x2 < x + b; x2++)
                {
                    *(ret + y2 * ret_width + x) = val;
                }
            }
            */
        }
    }

    //update l
    free(l->letter);
    l->letter = ret;
    l->width = ret_width;
    l->height = ret_width;
}

void resize_el(List *l)
{
    // recizevalue = l->width * b / c
    // objective : find b and c
    int pgc = pgcd(l->width, recizevalue);
    int b = recizevalue / pgc;
    int c = l->width / pgc;
    
    my_multiply(l, b);
    divide(l, c);
}

void resize(List *l)
{
    List *curr = l->next;
    while (curr->width != -2)
    {
        if (curr->width != recizevalue)
            resize_el(curr);
        curr = curr->next;
    }
}
