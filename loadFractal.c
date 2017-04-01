#include "loadFractal.h"
#include "parameterz.h"
#include <complex.h>
#include <math.h>

static complex double conv(int x, int y){
	return creal(center)+(x-width/2)/unit + (cimag(center)-(y-height/2)/unit)*I;
}

void load(int x1, int y1, int x2, int y2, SDL_Surface *screen){
	//novaretti(screen, x1, y1, x2, y2);
	int x,y;
	for (y=y1;y<y2;y++){
		for (x=x1;x<x2;x++){
			//pixels[x+y*width]=SDL_MapRGB(screen->format,0,0,0);
			complex double p=conv(x,y);
			//c=p;//mandelbrot
			SDL_Surface* im=image;
			mandel[0][x+y*width]=it;
			for (int i=0;i<it;i++){
				p=p*p+c;
				if(cabs(p)>40){
					mandel[0][x+y*width]=i;
					int w=im->w, h=im->h;
					mandel[1][x+y*width]=(carg(p)+3.141593)/6.283186*w;
					mandel[2][x+y*width]=2*h-log(cabs(p))*(h/3.6895016);
					break;
				}
				// if(cabs(p)>10){
				// 	pixels[x+y*width]=color(screen,i);
				// 	break;
				// }
				// p=csin(p)+p;
				// if(cabs(p)>5){
				// 	pixels[x+y*width]=color(screen,i);
				// 	break;
				// }
			}
		}
	}
}

void decale(SDL_Surface *screen, int dx, int dy){
	for(int y=dy<0?0:height-1; (dy<0&&y<height+dy)||(dy>=0&&y>=dy); y=dy<0?y+1:y-1)
		for(int x=dx<0?width-1:0; (dx<0&&x>=-dx)||(dx>=0&&x<width-dx); x=dx<0?x-1:x+1){
			mandel[0][x+y*width]=mandel[0][x+dx+(y-dy)*width];
			mandel[1][x+y*width]=mandel[1][x+dx+(y-dy)*width];
			mandel[2][x+y*width]=mandel[2][x+dx+(y-dy)*width];
		}
	addCenter(dx/unit + dy/unit*I);
	dx<0?load(0, 0,-dx,height,screen):load(width-dx, 0, width,height,screen);
	dy<0?load(0, height+dy,width,height,screen):load(0, 0, width,dy,screen);
}