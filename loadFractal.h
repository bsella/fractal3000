#ifndef LOADFRACTAL
#define LOADFRACTAL
#include <SDL/SDL.h>

int *mandel;
double **freyman;

void load(int x1, int y1, int x2, int y2);

void decale(SDL_Surface *screen, int dx, int dy);

#endif