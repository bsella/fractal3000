#ifndef PARAMETERZ
#define PARAMETERZ
#include <complex.h>
#include <SDL/SDL.h>

extern int width, height;//3508 2480

extern float unit;

extern int it, max, d;
int **mandel;

extern complex double center, c;

SDL_Surface* image;

extern int mode;
pthread_mutex_t mutex;
extern int dx, dy;

void maxUP();
void maxDOWN();
void dUP();
void dDOWN();

void addCenter(complex double cc);
void cUP();
void cDOWN();
void cLEFT();
void cRIGHT();

void nextMode();

void setDX(int x);
void setDY(int y);

void unitUP();

void unitDOWN();

#endif