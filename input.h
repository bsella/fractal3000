#ifndef INPUT
#define INPUT
#include <SDL/SDL.h>

SDL_Surface **images;
SDL_Surface *screen;

pthread_mutex_t mutex;

void loop();

void *run(void* screen);

#endif