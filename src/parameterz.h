#ifndef PARAMETERZ
#define PARAMETERZ
#include <complex.h>
#include <SDL/SDL.h>

const unsigned int width, height;//3508 2480

double unit, bailout;

int max, d;

complex double center, c;

int mode;
int dx, dy;

complex double conv(int x, int y);

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

void bailoutUP();
void bailoutDOWN();

#endif