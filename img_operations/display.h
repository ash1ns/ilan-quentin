#ifndef DISPLAY_H
#define DISPLAY_H


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


void init_sdl();
void wait_for_keypressed();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void SDL_FreeSurface(SDL_Surface *surface);

#endif
