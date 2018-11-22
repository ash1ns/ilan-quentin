#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"


//***********************************
//Convert to Grayscale a SDL_Surface
//***********************************
SDL_Surface* toGrayscale(SDL_Surface* image_surface)
{
    Uint32 pixel;
    Uint8 r, g, b;
    Uint32 average;
    int width = image_surface->w;
    int height = image_surface->h;

    for(int y = 0; y < height; y++)
    {
	for(int x = 0; x < width; x++)
	{
    	    //Get the pixel value.
    	    pixel = get_pixel(image_surface, x, y);
	
    	    //Get the RGB values of the pixel.
    	    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

    	    //Compute the weighted average of the RGB values:
    	    pixel = SDL_MapRGB(image_surface->format, r, g, b);

	    average = 0.3*r + 0.59*g + 0.11*b;

    	    //Update the RGB values by using this average
	    r = average;
	    g = average;
	    b = average;

    	    //Get the new pixel value from the new RGB values.
    	    Uint32 pixel = SDL_MapRGB(image_surface->format, r, g, b);

    	    //Put the new pixel value on the surface.
    	    put_pixel(image_surface, x, y, pixel);
	}
    }
    return image_surface;
}


//***********************
//Binarize a SDL_Surface
//***********************
SDL_Surface* Binarize(SDL_Surface* image_surface)
{
    Uint32 pixel;
    Uint8 r, g, b;

    int width = image_surface->w;
    int height = image_surface->h;

    unsigned long sum = 0;
    Uint32 threshold;

    //Calcul threshold
    for(int y = 0; y < height; y++)
    {
	for(int x = 0; x < width; x++)
	{
    	    pixel = get_pixel(image_surface, x, y);	
    	    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

            sum += r;
	}
    }	
    
    //No div by 0
    if(width*height != 0)
    {
    	threshold = sum / (width * height) * 0.75;
    }
    else
    {
        errx(1, "Empty image");
    }

    //Check if the pixel is white or black using threshold    
    for(int y = 0; y < height; y++)
    {
	for(int x = 0; x < width; x++)
	{
    	    pixel = get_pixel(image_surface, x, y);
	    SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
	    // r = g = b
	    if(r < threshold)
	    {
	        r = 0;
	    }
	    else
	    {
		r = 255;
	    }
	    Uint32 pixel = SDL_MapRGB(image_surface->format, r, r, r);
    	    put_pixel(image_surface, x, y, pixel);
	}
    }
    return image_surface;
}
	

