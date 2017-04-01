#include "parameterz.h"
#include <math.h>

float unit=300;

int it=100, max=30, d=0;
int **mandel;

complex double center=0,
c=-.835 -.2321*I;
//c=-.23 + .66*I;
//c=-.2+.5*I;
//c=-.61+.02*I;
int mode=0;
int dx=0, dy=0;

void maxUP(){
	max+=6;
}

void maxDOWN(){
	if(max!=6)max-=6;
}
void dUP(){
	d++;
}
void dDOWN(){
	if(d)d--;
}

void addCenter(complex double cc){
	center+=cc;
}
void cUP(){
	c+=(.05/sqrt(unit))*I;
}
void cDOWN(){
	c-=(.05/sqrt(unit))*I;
}
void cLEFT(){
	c+=.05/sqrt(unit);
}
void cRIGHT(){
	c-=.05/sqrt(unit);
}

void nextMode(){
	mode= mode==1?0:mode+1;
}

void setDX(int x){
	dx=x;
}

void setDY(int y){
	dy=y;
}

void unitUP(){
	unit*=1.05;
}

void unitDOWN(){
	unit/=1.05;
}