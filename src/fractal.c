#include "fractal.h"
#include "palette.h"
#include "parameterz.h"
#include <complex.h>
#include <math.h>

int maxIt=50;

static complex double nextIteration(complex double z){
	return z*z+c;
}

static Uint32 get_pixel32(SDL_Surface *surface, int i){
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[i];
}

void load(int x1, int y1, int x2, int y2){
	int x,y;
	for (y=y1;y<y2;y++)
		for (x=x1;x<x2;x++){
			complex double p=conv(x,y);
			//c=p;//mandelbrot
			counts[x+y*width]=0;
			for (int i=0;i<maxIt;i++){
				p=nextIteration(p);
				if(cabs(p)>bailout){
					counts[x+y*width]=i;
					freyman[0][x+y*width]=(carg(p)+3.141593)/6.283186;
					freyman[1][x+y*width]=log(bailout*bailout/cabs(p))/log(bailout);//2-log(cabs(p))/3.68950177;
					break;
				}
			}
		}
}

void decale(int dx, int dy){
	for(int y=dy<0?0:height-1; (dy<0&&y<height+dy)||(dy>=0&&y>=dy); y=dy<0?y+1:y-1)
		for(int x=dx<0?width-1:0; (dx<0&&x>=-dx)||(dx>=0&&x<width-dx); x=dx<0?x-1:x+1){
			counts[x+y*width]=counts[x+dx+(y-dy)*width];
			freyman[0][x+y*width]=freyman[0][x+dx+(y-dy)*width];
			freyman[1][x+y*width]=freyman[1][x+dx+(y-dy)*width];
		}
	addCenter(dx/unit + dy/unit*I);
	dx<0?load(0, 0,-dx,height):load(width-dx, 0, width,height);
	dy<0?load(0, height+dy,width,height):load(0, 0, width,dy);
}

static Uint32 getFreyman(int i, SDL_Surface **images, unsigned imgIndex){
	return get_pixel32(images[imgIndex],
				(int)(freyman[0][i]*images[imgIndex]->w)
				+(int)(freyman[1][i]*images[imgIndex]->h-1)*images[imgIndex]->w
			); //x+(y-1)*width //-1 prevents a weird black line on top of every layer
}

static Uint32 colorMulFloat(SDL_Surface* s, Uint32 color, float f){
	Uint8 r,g,b;
	SDL_GetRGB(color,s->format,&r,&g,&b);
	return SDL_MapRGB(s->format,r*f,g*f,b*f);
}

int seuil=7;

void show(SDL_Surface *s, SDL_Surface **images){
	Uint32 *pixels= s->pixels;
	switch(mode){
		case 0:
			for(int i=0;i<width*height;i++)
				pixels[i]=counts[i]==0? SDL_MapRGB(s->format,0,0,0):pltGet(*colors,freyman[0][i]);//color(s,counts[i]);
		break;
		/*case 2:
			for(int i=0;i<width*height;i++){
				Uint8 r,g,b;
				SDL_GetRGB(getFreyman(i,images,0),images[0]->format,&r,&g,&b);
				pixels[i]=counts[i]==0? SDL_MapRGB(s->format,0,0,0): colorMulFloat(s,get_pixel32(background,i),g/255.0);
			}
			break;*/
		default:
			for(int i=0;i<width*height;i++)
				switch((counts[i]+seuil-1)/seuil){
					case 0:
						pixels[i]=SDL_MapRGB(s->format,0,0,0); break;
					case 1:
						pixels[i]=getFreyman(i,images,mode-1); break;
					default:
						pixels[i]=colorMulFloat(s,
							getFreyman(i,images,mode-1),
							exp((counts[i]-seuil)/-10.0));
				}
	}
	SDL_Flip(s);
}