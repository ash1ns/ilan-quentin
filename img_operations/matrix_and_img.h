#ifndef MATRIX_AND_IMG_H
#define MATRIX_AND_IMG_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

void toMatrix(SDL_Surface* screen_surface, int mat[]);
void toSurface(int mat[], SDL_Surface* screen_surface);

#endif
