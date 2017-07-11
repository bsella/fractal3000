#include <stdio.h>
#include <math.h>
#include <string.h>
#include <complex.h>
#include <SDL/SDL.h>

int width=1757, height=1246;//3508 2480

float unit;

int it=20, max=30, d=0;

complex double center, c;

static complex double conv(int x, int y){
	return creal(center)+(x-width/2)/unit + (cimag(center)-(y-height/2)/unit)*I;
}

static Uint32 color(SDL_Surface *screen, int i){
	int r,g,b;
	i=i+d;
	int m6= max/6;
	double id=(double)(i%m6)/(double)m6;
	switch((i%max/m6)){
		case(0):
			r=255;
			g=id*255;
			b=0;
		break;
		case(1):
			r=(1-id)*255;
			g=255;
			b=0;
		break;
		case(2):
			r=0;
			g=255;
			b=id*255;
		break;
		case(3):
			r=0;
			g=(1-id)*255;
			b=255;
		break;
		case(4):
			r=id*255;
			g=0;
			b=255;
		break;
		case(5):
			r=255;
			g=0;
			b=(1-id)*255;
	}
	return SDL_MapRGB(screen->format,r,g,b);
}

static Uint32 grayscale(SDL_Surface *screen, int i){
	return SDL_MapRGB(screen->format,255-i*255/it,255-i*255/it,255-i*255/it);
}

void load(int x1, int y1, int x2, int y2, SDL_Surface *screen){
	int x,y;
	Uint32 *pixels= screen->pixels;
	for (y=y1;y<y2;y++){
		for (x=x1;x<x2;x++){
			pixels[x+y*width]=SDL_MapRGB(screen->format,0,0,0);
			complex double p=conv(x,y);//,pp;
			//c=p;//mandelbrot
			int i;
			for (i=0;i<it;i++){
				//pp=(2*p*p*p+1)/(3*p*p);
				p=p*p+c;
				//pp=p-(p*p*p-1)/3*p*p;
				if (cabs(p)>2) {pixels[x+y*width]=grayscale(screen,i); break;}
				//p=pp;
			}
		}
	}
	SDL_Flip(screen);
}

void decale(SDL_Surface *screen, SDLKey key){
	int x,y;
	int d=10;
	Uint32 *pixels= screen->pixels;
	switch(key){
		case SDLK_UP:
		for(y=height-1;y>=d;y--)
			for(x=0;x<width;x++)
				pixels[x+y*width]=pixels[x+(y-d)*width];
		center+=d/unit*I;
		load(0,0,width,d,screen);
		break;
		case SDLK_DOWN:
		for(y=0;y<height-d;y++)
			for(x=0;x<width;x++)
				pixels[x+y*width]=pixels[x+(y+d)*width];
		center-=d/unit*I;
		load(0,height-d,width,height,screen);
		break;
		case SDLK_RIGHT:
		for(y=0;y<height;y++)
			for(x=0;x<width-d;x++)
				pixels[x+y*width]=pixels[x+d+y*width];
		center+=d/unit;
		load(width-d,0,width,height,screen);
		break;
		case SDLK_LEFT:
		for(y=0;y<height;y++)
			for(x=width-1;x>=d;x--)
				pixels[x+y*width]=pixels[x-d+y*width];
		center-=d/unit;
		load(0,0,d,height,screen);
		break;

		default: break;
	}
}

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface *screen;
	screen=SDL_SetVideoMode(width,height,32,SDL_HWSURFACE);
	center=0;
	//c=-.835 -.2321*I;
	c=-.23 + .66*I;
	int f, page;
	for(page=0; page<49;page++){
		for(f=0; f<49;f++){
			int xmin, xmax, ymin, ymax;
			xmin=(f%7)*width/7;
			xmax=(f%7+1)*width/7;
			ymin=(f/7)*height/7;
			ymax=(f/7+1)*height/7;
			unit=3488.8;
			c=conv((xmin+xmax)/2,(ymin+ymax)/2)+.503571*(page%7-3)-.357142*(page/7-3)*I;;
			unit=71.2;
			center=-conv((xmin+xmax)/2,(ymin+ymax)/2);
			load(xmin,ymin,xmax,ymax,screen);
			center=0;
		}
		SDL_Flip(screen);
		char file[13];
		sprintf(file,"wall/%d.bmp",page);
		SDL_SaveBMP(screen, file);
	}
	while(1){
		SDL_Event event;
		SDL_WaitEvent(&event);
		if (event.type==SDL_QUIT || (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE)){
			SDL_SaveBMP(screen, "test.bmp");break;
		}
		if (event.type==SDL_KEYDOWN){
			switch(event.key.keysym.sym){
				case(SDLK_q):unit/=1.05; goto label;
				case(SDLK_w):unit*=1.05;goto label;
				case(SDLK_p): if(max!=6) max-=6;goto label;
				case(SDLK_o): max+=6;goto label;
				case(SDLK_l): c+=.01;goto label;
				case(SDLK_j): c-=.01;goto label;
				case(SDLK_i): c+=.01*I;goto label;
				case(SDLK_k): c-=.01*I;goto label;
				case(SDLK_MINUS): if(d)d--;goto label;
				case(SDLK_EQUALS): d++;
				label: for(f=0; f<49;f++){
					int xmin, xmax, ymin, ymax;
					xmin=(f%7)*width/7;
					xmax=(f%7+1)*width/7;
					ymin=(f/7)*height/7;
					ymax=(f/7+1)*height/7;
					unit=3488.8;
					c=conv((xmin+xmax)/2,(ymin+ymax)/2)+.503571*(page%7-3)-.357142*(page/7-3)*I;;
					unit=71.2;
					center=-conv((xmin+xmax)/2,(ymin+ymax)/2);
					load(xmin,ymin,xmax,ymax,screen);
					center=0;
				}
				default:break;
			}
			decale(screen,event.key.keysym.sym);
		}
	}
	SDL_FreeSurface(screen);
	SDL_Quit();
	printf("it vorks!\n");
	return 0;
}
