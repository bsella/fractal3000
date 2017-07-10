#include "fractal.h"
#include "palette.h"
#include "parameterz.h"
#include <complex.h>
#include <math.h>

int maxIt=100;

static complex double nextIteration(complex double z){
	return z*z+c;
}

void load(int x1, int y1, int x2, int y2){
	//novaretti(screen, x1, y1, x2, y2);
	int x,y;
	for (y=y1;y<y2;y++){
		for (x=x1;x<x2;x++){
			complex double p=conv(x,y);
			//c=p;//mandelbrot
			mandel[x+y*width]=0;
			for (int i=0;i<maxIt;i++){
				p=nextIteration(p);
				if(cabs(p)>bailout){
					mandel[x+y*width]=i;
					freyman[0][x+y*width]=-(carg(p)+3.141593)/6.283186+2;
					freyman[1][x+y*width]=log(bailout*bailout/cabs(p))/log(bailout);//2-log(cabs(p))/3.68950177;
					break;
				}
			}
		}
	}
}

void decale(int dx, int dy){
	for(int y=dy<0?0:height-1; (dy<0&&y<height+dy)||(dy>=0&&y>=dy); y=dy<0?y+1:y-1)
		for(int x=dx<0?width-1:0; (dx<0&&x>=-dx)||(dx>=0&&x<width-dx); x=dx<0?x-1:x+1){
			mandel[x+y*width]=mandel[x+dx+(y-dy)*width];
			freyman[0][x+y*width]=freyman[0][x+dx+(y-dy)*width];
			freyman[1][x+y*width]=freyman[1][x+dx+(y-dy)*width];
		}
	addCenter(dx/unit + dy/unit*I);
	dx<0?load(0, 0,-dx,height):load(width-dx, 0, width,height);
	dy<0?load(0, height+dy,width,height):load(0, 0, width,dy);
}

void show(SDL_Surface *s, SDL_Surface **images){
	Uint32 *pixels= s->pixels;
	switch(mode){
		case 0:
			for(int i=0;i<width*height;i++)
				pixels[i]=mandel[i]==0? SDL_MapRGB(s->format,0,0,0):color(s,mandel[i]);
		break;
		default:
			for(int i=0;i<width*height;i++)
				pixels[i]=mandel[i]==0? SDL_MapRGB(s->format,0,0,0):
			get_pixel32(images[mode-1],
				(int)(freyman[0][i]*images[mode-1]->w)
				+(int)(freyman[1][i]*images[mode-1]->h-1)*images[mode-1]->w
			); //x+(y-1)*width //-1 prevents a weird black line on top of every layer
	}
	SDL_Flip(s);
}