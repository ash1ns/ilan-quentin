#include <stdlib.h>
#include "list.h"

void addBlanks_middle(List *l)
{
    // rest is how many cols of zero we will ad
    int rest = l->height - l->width;
    // it should be at the middle thats why left and right
    int left = rest / 2;
    // right add 1 more if not divisible by 2
    int right = left + rest % 2;

    //int *ret = malloc(l->height * l->height * sizeof(int));

    // all init at 0
    int *ret = calloc(l->height * l->height, sizeof(int));


    // add middle values
    int *curr = l->letter;
    for (int y = 0; y < l->height; y++)
    {
        for (int x = left; x < l->height - right; x++)
        {
            *(ret + y * l->height + x) = *curr;
            curr++;
        }
    }
    
    free(l->letter);
    l->letter = ret;
    l->width = l->height;
}

void addBlanks_up(List *l)
{
    int *ret = malloc(l->width * l->width * sizeof(int));
    int addto = l->width - l->height;

    // add 0
    for (int y = 0; y < addto; y++)
    {
        for (int x = 0; x < l->width; x++)
        {
            *(ret + y * l->width + x) = 0;
        }
    }
    
    // complete by normal values
    for (int y = 0; y < l->height; y++)
    {
        for (int x = 0; x < l->width; x++)
        {
            *(ret + addto * l->width + y * l->width + x) = *(l->letter 
                                                            + y * l->width + x);
        }
    }
    
    free(l->letter);
    l->letter = ret;
}

void addBlanks_el(List *l)
{
    if (l->width > l->height)
    {
        addBlanks_up(l);
        l->height = l->width;
    }
    else if (l->width < l->height)
    {
        addBlanks_middle(l);  
    }
}

void addblanks(List *l)
{
    List *curr = l->next;
    while (curr->width != -2)
    {
        addBlanks_el(curr);
        curr = curr->next;
    }
}
