#ifndef SHOWFRACTAL
#define SHOWFRACTAL
#include <SDL/SDL.h>

int *mandel;
double **freyman;

Uint32 get_pixel32(SDL_Surface *surface, int i);

Uint32 color(SDL_Surface *screen, int i);

Uint32 grayscale(SDL_Surface *screen, int i);

void show(SDL_Surface *screen, SDL_Surface **images);

#endif