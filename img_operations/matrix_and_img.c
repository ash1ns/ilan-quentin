#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

#define WHITE 0
#define BLACK 1
#define RED 2
#define BLUE 4

//************************************
// Convert a SDL_Surface to 1D Matrix
//************************************
void toMatrix(SDL_Surface* image_surface, int mat[])
{

    size_t width = image_surface->w;
    size_t height = image_surface->h;

    Uint32 pixel;    

    for(size_t y = 0; y < height; y++)
    {
        for(size_t x = 0; x < width; x++)
	{	
	    pixel = get_pixel(image_surface, (int)x, (int)y);

        if(pixel == 0)
	    {
	        mat[y * width + x] = 1;
	    }
	    else
	    {
		mat[y * width + x] = 0;
	    }		

	 }
    }  
}

//***********************************
// Convert a matrix to a SDL_Surface
//***********************************
void toSurface(int mat[], SDL_Surface* image_surface)
{
    int width = image_surface->w;
    int height = image_surface->h;
    Uint32 pixel;
    Uint8 r, g, b;
    
    for(int y = 0; y < height; y++)
    {
	for(int x = 0; x < width; x++)
	{
	    pixel = get_pixel(image_surface, x, y);
	    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

	    int val = mat[y * width + x];

	    if(val == WHITE)
	    {
		r = 255;
      	g = 255;
		b = 255;		
	    }
	    if(val == BLACK)
	    {
	        r = 0;
		g = 0;
		b = 0;
	    }
	    if(val == BLUE)
	    {
		r = 0;
		g = 0;
		b = 255;
	    }
	    if(val == RED)
	    {
		r = 255;
		g = 0;
		b = 0;
	    }
	
	    pixel = SDL_MapRGB(image_surface->format, r, g, b);
	    put_pixel(image_surface, x, y, pixel);
	}

    } 



}
