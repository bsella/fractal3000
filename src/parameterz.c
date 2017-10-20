#include "parameterz.h"
#include <math.h>

double unit=300;

int max=30, d=0;

complex double center=0,
c=-.835 -.2321*I;
//c=-.23 + .66*I;
//c=-.2+.5*I;
//c=-.61+.02*I;0
unsigned mode=0;
int dx=0, dy=0;
double bailout = 50;

complex double conv(int x, int y){
	return creal(center)+((double)x-width/2)/unit + (cimag(center)-((double)y-height/2)/unit)*I;
}

void maxUP(){
	if(mode==0)
		max+=6;
}

void maxDOWN(){
	if(mode==0)
		if(max!=6)max-=6;
}
void dUP(){
	if(mode==0)
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
	mode= mode==2?0:mode+1;
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

void bailoutUP(){
	bailout*=1.05;
}

void bailoutDOWN(){
	if(bailout>3)
		bailout/=1.5;
}