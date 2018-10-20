#include <stdio.h>

#define RED 2
#define BLUE 4

void copy_array(int input[], size_t row, size_t col, int ret[])
{
    // make the array full of 0
    size_t tot = col*row;
    for (size_t i = 0; i < tot; i++)
    {
        ret[i] = input[i];
    }
}

void make_blue(int input[], size_t y, size_t col, int ret[])
{
    // make a ligne blue
    for (size_t x = 0; x < col; x++)
    {
        if (input[y * col + x] == 0)
        {
            // 4 = blue
            ret[y * col + x] = BLUE;
        }
    }
}


void detect_lign(int input[], size_t row, size_t col, int ret[])
{
    /* Go on the image horizontaly and make the hole lign blue if we find
     a black value */
    copy_array(input, row, col, ret);
    size_t y = 0;
    size_t x = 0;
    while (y < row)
    {
        x = 0;
        // adding y < row in case of security
        while (x < col)
        {
            if (input[y * col + x] == 1)
            {
                // Make the hole line blue
                make_blue(input, y, col, ret);
                /*
                // continue on the new line
                y += 1;
                x = 0;
                continue;
                */
            }
            x++;
        }
        y++;
    }
}

void find_y(int input[], size_t row, size_t col, size_t y, size_t ret[])
{
    /* 
        input = array with blue (ret of the detect_lign function)
        Find y1 and y2 between y and row when y1 is the lower lign index
        and y2 is the next lign index
        Only blue lines between lign y1 and lign y2
        return [0,0] if no line found
        ret size_t 2 values
    */
    ret[0] = 0;
    ret[1] = 0;
    // find the first one
    while (y < row)
    {
        if (input[y * col] == BLUE || input[y * col] == 1)
        {
            ret[0] = y;
            break;
        }
        y++;
    }
    if (ret[0] != 0 || y == 0)
    {
        y++;
        while (y < row && input[y * col] != 0)
        {
            y++;
        }
        if (y <= row)
        {
            ret[1] = y - 1;
        }
    }

    // printf("y1 = %lu       y2 = %lu\n", ret[0], ret[1]);    
}



void make_red(int ret[], size_t col, size_t y1, size_t y2, size_t x)
{
    while (y1 <= y2)
    {
        //sa pete ici
        if (ret[y1 * col + x] == BLUE)
        {
            ret[y1 * col + x] = RED;
        }
        y1++;
    }
}

void find_char_horizontal(int ret[], size_t row, size_t col)
{
    // color in ret
    // must update a struct of rect

    // initialise the array of ret in find_y 
    // y_coords[0] = y1 / y_coords[1] = y2
    size_t y_coords[2];

    // Find the first value of y1 and y2 
    find_y(ret, row, col, 0, y_coords);

    // while find_y return a possible value
    while (y_coords[1] != 0)
    {
        size_t y1 = y_coords[0];
        size_t y2 = y_coords[1];
        
        size_t x = 0;
        
        while (x < col)
        {
            for (size_t y = y1; y <= y2; y++)
            {
                if (ret[y * col + x] == 1)
                {
                    make_red(ret, col, y1, y2, x);
                }
            }
            x++;
        }

        find_y(ret, row, col, y2 + 1, y_coords);
        
    }

}

void segment(int input[], size_t row, size_t col, int ret[])
{
    detect_lign(input, row, col, ret);
    find_char_horizontal(ret, row, col);
}
