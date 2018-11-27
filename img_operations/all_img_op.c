#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "display.h"
#include "grayscale_binarize.h"
#include "pixel_operations.h"
#include "matrix_and_img.h"
#include "segmentation.h"
// begin modif
#include "rect.h"
// end modif

void print_matrix(int input[], size_t row, size_t col)
{
    for (size_t y = 0; y < row; y++)
    {
	for (size_t x = 0; x < col; x++)
	{
	    printf("%i ", input[y * col + x]);
	}
	printf("\n");
    }
}


void all_img_op(char *argv[])
{
	
	SDL_Surface* image_surface;
	SDL_Surface* screen_surface;

    //Initialisation, load image and display
	init_sdl();
	image_surface = load_image(argv[1]);
	screen_surface = display_image(image_surface);	
	wait_for_keypressed();

	int width = image_surface->w;
    int height = image_surface->h;

    //Convert to grayscale
	image_surface = toGrayscale(image_surface);
	update_surface(screen_surface, image_surface);
	wait_for_keypressed();
	
    //Binarise
	image_surface = Binarize(image_surface);
	update_surface(screen_surface, image_surface);
	wait_for_keypressed();	

    //Convert to matrix
   	size_t size = (size_t)width * (size_t)height;

	int mat[size];
	toMatrix(screen_surface, mat);

    //Print matrix
    if (size <= 32 * 32)
        print_matrix(mat, height, width);

    wait_for_keypressed();

    //Make segmentation
    int mat2[size];
    segment(mat, (size_t)height, (size_t)width, mat2);
    

    // begin modif


    // row = height
    // col = width
    // Character recuperation in a matrix of 1k rect
    // for final make it in a dynamic list with next prev
    // Because we cant treat text with more than size / seuil characters
    // seuil = 100;
    size_t row = (size_t)height;
    size_t col = (size_t)width;

    size_t matlength = size / 100;
    Rect matrect[matlength];

    // get the array of rect of all characters
    size_t rect_array_length = get_Rect(mat2, row, col, matrect);
    
    // Print the array of rect in a file
    write_rect_array(mat2, col, matrect, rect_array_length);

    // end modif

    // Convert the matrix with segmentation to surface and display it
	toSurface(mat2, image_surface);
	update_surface(screen_surface, image_surface);
	wait_for_keypressed();

	SDL_FreeSurface(image_surface);
	SDL_FreeSurface(screen_surface);
}


