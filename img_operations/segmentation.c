#include <stdio.h>
#include "rect.h"
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


// segmentation function
void segment(int input[], size_t row, size_t col, int ret[])
{
    detect_lign(input, row, col, ret);
    find_char_horizontal(ret, row, col);
}

// Get the output of segmentation to an dynamic list of Rect

void find_x(int input[], size_t col, size_t y1, size_t x, size_t ret[])
{
    ret[0] = 0;
    ret[1] = 0;
    // find the first one
    while (x < col)
    {
        if (input[y1 * col + x] == RED || input[y1 * col + x] == 1)
        {
            ret[0] = x;
            break;
        }
        x++;
    }
    if (ret[0] != 0 || x == 0)
    {
        x++;
        // the hole line is blue and no characters
        while (x < col && input[y1 * col + x] != BLUE)
        {
            x++;
        }
        if (x <= col)
        {
            ret[1] = x - 1;
        }
    } 
}

// all rect stuff

void find_y_rect(int input[], size_t row, size_t col, size_t y, size_t ret[])
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
        if (input[y * col] == BLUE || input[y * col] == 1 || input[y * col] == RED)
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

        // useless test maybe opti
        if (y <= row)
        {
            ret[1] = y - 1;
        }
    }

    // printf("y1 = %lu       y2 = %lu\n", ret[0], ret[1]);    
}


Rect init_rect(size_t get_x[], size_t get_y[])
{
    Rect ret;
    ret.x1 = get_x[0];
    ret.y1 = get_y[0];
    ret.x2 = get_x[1];
    ret.y2 = get_y[1];
    return ret;
}


void write_rect_array(int main_image[], size_t col, Rect input[], 
        size_t inputlength)
{
    // write all characters in a file
    // create a FILE typed pointer
	FILE *file_pointer;

	// open the file "name_of_file.txt" for writing
	file_pointer = fopen("characters", "w");

	// Write to the file
	// fprintf(file_pointer, "This will write to a file.");

    
    for (size_t i = 0; i < inputlength; i++)
    {
        size_t x1 = input[i].x1;
        size_t x2 = input[i].x2;
        size_t y1 = input[i].y1;
        size_t y2 = input[i].y2;
        // between [y1,y2]
        while (y1 <= y2)
        {
            // print values between [x1,x2]
            for (size_t x = x1; x <= x2; x++)
            {
                if (main_image[y1 * col + x] == 2)
                {
                    fprintf(file_pointer, "0 ");
                }
                else
                {
                    fprintf(file_pointer, "1 ");
                }
            }
            fprintf(file_pointer, "\n");
            y1++;
        }

        fprintf(file_pointer, "================\n");
    }

	// Close the file
	fclose(file_pointer);
}


size_t get_Rect(int input[], size_t row, size_t col, Rect ret[])
{
    // modify the ret array in place and return his length;
 
    // Inititialise arrays
    // get_y[0] = y1;
    // get_y[1] = y2;
    // get_x[0] = x1;
    // get_x[1] = x2;
    size_t get_y[2];
    size_t get_x[2];
    
    // Get the first values of y1 and y2
    find_y_rect(input, row, col, 0, get_y);
    
    // The returned index = number of characters in the image
    size_t ret_index = 0;
    
    // condition is: when we have y2 and x2 set diffent than 0 else loop is over
    while (get_y[1] != 0)
    {
        // get the first values of x1 and x2 at each loop with the y parameter
        find_x(input, col, get_y[0], 0, get_x);

        while (get_x[1] != 0)
        {
            ret[ret_index] = init_rect(get_x, get_y);

            // get the 2 next values of x
            find_x(input, col, get_y[0], get_x[1] + 1, get_x);
    
            // update index of the ret array
            ret_index++;
        }
        // get the 2 next values of y
        find_y_rect(input, row, col, get_y[1] + 1, get_y);
    }

    return ret_index;
}
