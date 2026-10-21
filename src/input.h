#ifndef INPUT
#define INPUT
#include <SDL/SDL.h>

extern SDL_Surface **images;
extern SDL_Surface *screen;

void loop();

void *run(void* screen);

#endif