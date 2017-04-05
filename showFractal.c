#include "showFractal.h"
#include "parameterz.h"

static Uint32 get_pixel32(SDL_Surface *surface, int i){
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[i];
}

Uint32 color(SDL_Surface *screen, int i){
	int r,g,b;
	i=i+d;
	int m6= max/6;
	double id=(double)(i%m6)/(double)m6;
	switch((i%max/m6)){
		case 0:
			r=255;
			g=id*255;
			b=0;
		break;
		case 1:
			r=(1-id)*255;
			g=255;
			b=0;
		break;
		case 2:
			r=0;
			g=255;
			b=id*255;
		break;
		case 3:
			r=0;
			g=(1-id)*255;
			b=255;
		break;
		case 4:
			r=id*255;
			g=0;
			b=255;
		break;
		case 5 :
			r=255;
			g=0;
			b=(1-id)*255;
	}
	return SDL_MapRGB(screen->format,r,g,b);
}

Uint32 grayscale(SDL_Surface *screen, int i){
	return SDL_MapRGB(screen->format,255-i*255/max,255-i*255/max,255-i*255/max);
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
				pixels[i]=mandel[i]==0? SDL_MapRGB(s->format,0,0,0):get_pixel32(images[mode-1],(int)(freyman[0][i]*images[mode-1]->w) +(int)(freyman[1][i]*images[mode-1]->h)*images[mode-1]->w);
	}
	SDL_Flip(s);
}