#ifndef SHOWFRACTAL
#define SHOWFRACTAL
#include <SDL/SDL.h>
Uint32 color(SDL_Surface *screen, int i);

Uint32 grayscale(SDL_Surface *screen, int i);

void show(SDL_Surface *screen);

#endif