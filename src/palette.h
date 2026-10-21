#ifndef SHOWFRACTAL
#define SHOWFRACTAL
#include <SDL/SDL.h>

typedef struct{
	struct paletteColor *first;
}Palette;

int pltEmpty(Palette plt);

Palette* pltInit();

void pltAdd(Palette *p, Uint32 color, double i);

Uint32 pltGet(Palette p, double i);

void pltFree(Palette *p);

#endif