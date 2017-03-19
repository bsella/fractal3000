#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <SDL.h>
#include <pthread.h>


/*Pour "fractaliser" une image :
	//a=(carg(pp)+3.141593)/6.283186*w,
	//r=(h-log(cabs(pp))*(h/7.37790032);//3.6895016
*/

int width=1080, height=720;//3508 2480

float unit=300;

int it=100, max=30, d=0;
int *mandel;

complex double center, c;

//SDL_Surface* image;
//SDL_Surface* i2;
//SDL_Surface* i3;

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

//Uint32 get_pixel32( SDL_Surface *surface, int i){
//	if(surface==i3)printf("%d\n", i);
//	Uint32 *pixels = (Uint32 *)surface->pixels;
//	return pixels[i];
//}

void novaretti(SDL_Surface *screen, int x1, int y1, int x2, int y2){
	int x,y;
	Uint32 *pixels= screen->pixels;
	for (y=y1;y<y2;y++){
		for (x=x1;x<x2;x++){
			pixels[x+y*width]=SDL_MapRGB(screen->format,0,0,0);
			complex double p=conv(x,y);
			//c=p;//mandelbrot
			//SDL_Surface* im=image;
			double r=creal(p), i=cimag(p);
			double sum=0;
			for (int j=0;j<it;j++){
				double t4=24*r*r*r*r*r*i-4*r*r*r*cimag(c)-80*r*r*r*i*i*i+24*r*i*i*i*i*i+12*r*i*i*cimag(c)-12*r*r*i*creal(c)+4*i*i*i*creal(c)+2*creal(c)*cimag(c),
					   t3=4*r*r*r*r*r*r-60*r*r*r*r*i*i-4*r*r*r*creal(c)+60*r*r*i*i*i*i+12*r*r*i*cimag(c)+12*r*i*i*creal(c)-4*i*i*i*i*i*i-4*i*i*i*cimag(c)-cimag(c)*cimag(c)+creal(c)*creal(c),
					   t2=-24*r*r*r*i+24*r*i*i*i-6*i*creal(c)-6*r*cimag(c),
					   t1=-6*r*r*r*r+36*r*r*i*i-6*r*creal(c)-6*i*i*i*i+6*i*cimag(c);
					   //t5=1/(t3*t3+576*pow(r,10)*i*i-3840*pow(r,8)*i*i*i*i-192*pow(r,8)*i*cimag(c)-576*pow(r,7)*i*i*creal(c)+7552*pow(r,6)*pow(i,6)+1216*pow(r,6)*i*i*i*cimag(c)+16*pow(r,6)*cimag(c)*cimag(c)+2112*r*r*r*r*r*i*i*i*i*creal(c)+192*r*r*r*r*r*i*cimag(c)*creal(c)-3840*r*r*r*r*pow(i,8)-2112*r*r*r*r*i*i*i*i*i*cimag(c)-96*r*r*r*r*i*i*cimag(c)*cimag(c)+144*r*r*r*r*i*i*creal(c)*creal(c)-1216*r*r*r*pow(i,6)*creal(c)-640*r*r*r*i*i*i*cimag(c)*creal(c)-16*r*r*r*cimag(c)*cimag(c)*creal(c)+576*r*r*pow(i,10)+576*r*r*pow(i,7)*cimag(c)+144*r*r*i*i*i*i*cimag(c)*cimag(c)-96*r*r*i*i*i*i*creal(c)*creal(c)-48*r*r*i*cimag(c)*creal(c)*creal(c)+192*r*pow(i,8)*creal(c)+192*r*i*i*i*i*i*cimag(c)*creal(c)+48*r*i*i*cimag(c)*cimag(c)*creal(c)+16*pow(i,6)*creal(c)*creal(c)+16*i*i*i*cimag(c)*creal(c)*creal(c)+4*cimag(c)*cimag(c)*creal(c)*creal(c));
					   r=(t3*t1+t4*t2)/(t3*t3+t4*t4);
					   i=(t3*t2-t4*t1)/(t3*t3+t4*t4);
					sum+=log(r*r+i*i);
			}
					pixels[x+y*width]=color(screen,fabs(sum));
		}
	}
	SDL_Flip(screen);
}

void load(int x1, int y1, int x2, int y2, SDL_Surface *screen){
	//novaretti(screen, x1, y1, x2, y2);
	int x,y;
	//Uint32 *pixels= screen->pixels;
	for (y=y1;y<y2;y++){
		for (x=x1;x<x2;x++){
			//pixels[x+y*width]=SDL_MapRGB(screen->format,0,0,0);
			complex double p=conv(x,y);
			//c=p;//mandelbrot
			//SDL_Surface* im;
			mandel[x+y*width]=it;
			for (int i=0;i<it;i++){
				p=p*p+c;
				if(cabs(p)>40){
					mandel[x+y*width]=i;
					//pixels[x+y*width]=color(screen,i);
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
	SDL_Flip(screen);
}

void show(SDL_Surface *s){
	Uint32 *pixels= s->pixels;
	for(int i=0;i<width*height;i++)
		pixels[i]=mandel[i]==it? SDL_MapRGB(s->format,0,0,0):color(s,mandel[i]);
}

void decale(SDL_Surface *screen, int dx, int dy){
	for(int y=dy<0?0:height-1; (dy<0&&y<height+dy)||(dy>=0&&y>=dy); y=dy<0?y+1:y-1)
		for(int x=dx<0?width-1:0; (dx<0&&x>=-dx)||(dx>=0&&x<width-dx); x=dx<0?x-1:x+1)
			mandel[x+y*width]=mandel[x+dx+(y-dy)*width];
	center+=dx/unit + dy/unit*I;
	dx<0?load(0, 0,-dx,height,screen):load(width-dx, 0, width,height,screen);
	dy<0?load(0, height+dy,width,height,screen):load(0, 0, width,dy,screen);
	show(screen);
}

void terminate(SDL_Surface *s, complex double c){
	printf("%f %f\n", creal(c), cimag(c));
	SDL_SaveBMP(s, "output/test.bmp");
}

pthread_mutex_t mutex;
int dx=0, dy=0;
void *run(void* screen){
	while(1){
		pthread_mutex_lock(&mutex);
		decale((SDL_Surface*)screen,dx/500,-dy/500);
		//if(dx!=0||dy!=0)
		pthread_mutex_unlock(&mutex);
		show(screen);
	}
	return NULL;
}

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	SDL_Surface *screen=SDL_SetVideoMode(width,height,32,SDL_HWSURFACE);
	//image= SDL_LoadBMP("lol.bmp");
	//image=SDL_ConvertSurface(image,screen->format,0);
	//i2= SDL_LoadBMP("flying.bmp");
	//i2=SDL_ConvertSurface(i2,screen->format,0);
	//i3= SDL_LoadBMP("poke.bmp");
	//i3=SDL_ConvertSurface(i3,screen->format,0);
	mandel=malloc(width*height*sizeof(int));
	center=0;
	c=-.835 -.2321*I;
	//c=-.23 + .66*I;
	//c=-.2+.5*I;
	//c=-.61+.02*I;
	load(0,0,width,height,screen);
	show(screen);
	SDL_Joystick *joystick;
	if(SDL_NumJoysticks()){
		printf("%s\n", SDL_JoystickName(0));
		SDL_JoystickEventState(SDL_ENABLE);
		joystick=SDL_JoystickOpen(0);
	}
	pthread_mutex_init(&mutex,NULL);
	pthread_mutex_lock(&mutex);
	pthread_t ptid;
	if(pthread_create(&ptid, NULL, &run, screen)!=0){
		perror("error creating thread");
		return 1;
	}
	int stil=1;
	while(stil){
		SDL_Event event;
		SDL_WaitEvent(&event);
		int reload=2;
		switch(event.type){
			case SDL_JOYAXISMOTION:
				pthread_mutex_unlock(&mutex);
				switch(event.jaxis.axis){
					case 0:
						dx=event.jaxis.value-128;
						break;
					case 1:
						dy=event.jaxis.value-128;
						break;
					default:break;
				}
				//if(dx==0 && dy==0)
					pthread_mutex_lock(&mutex);
				break;
			case SDL_JOYHATMOTION:
				switch(event.jhat.value){
					case SDL_HAT_DOWN: decale(screen,0,-20); break;
					case SDL_HAT_LEFT: decale(screen,-20,0); break;
					case SDL_HAT_RIGHT: decale(screen,20,0); break;
					case SDL_HAT_UP: decale(screen,0,20); break;
					case SDL_HAT_RIGHTDOWN: decale(screen,20,-20); break;
					case SDL_HAT_LEFTDOWN: decale(screen,-20,-20); break;
					case SDL_HAT_RIGHTUP: decale(screen,20,20); break;
					case SDL_HAT_LEFTUP: decale(screen,-20,20); break;
					default:break;
				}
				show(screen);
				break;
			case SDL_JOYBUTTONDOWN:
				switch(event.jbutton.button){
					case 0: c-=.01*I; break;
					case 1: c-=.01; break;
					case 2: c+=.01; break;
					case 3: c+=.01*I; break;
					case 4: if(d)d--;reload=1;break;
					case 5: d++;reload=1;break;
					case 6: if(max!=6)max-=6;reload=1;break;
					case 7: max+=6;reload=1;break;
					case 8: unit/=1.05;break;
					case 9: unit*=1.05;break;
					default:reload=0; break;
				}
				if(reload==2){
					load(0,0,width,height,screen);
					show(screen);
				}
				if(reload==1)show(screen);
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_q: unit/=1.05;break;
					case SDLK_w: unit*=1.05;break;
					case SDLK_p: if(max!=6) max-=6;reload=1;break;
					case SDLK_o: max+=6;reload=1;break;
					case SDLK_l: c+=.01;break;
					case SDLK_j: c-=.01;break;
					case SDLK_i: c+=.01*I;break;
					case SDLK_k: c-=.01*I;break;
					case SDLK_MINUS: if(d)d--;reload=1;break;
					case SDLK_EQUALS: d++;reload=1;break;
					case SDLK_ESCAPE: terminate(screen,c); stil=0;break;
					case SDLK_DOWN: decale(screen,0,-20);reload=1; break;
					case SDLK_LEFT: decale(screen,-20,0);reload=1; break;
					case SDLK_RIGHT: decale(screen,20,0);reload=1; break;
					case SDLK_UP: decale(screen,0,20);
					default:reload=1;break;
				}
				if(reload==2){
					load(0,0,width,height,screen);
					show(screen);
				}
				show(screen);
				break;
			case SDL_QUIT:
				terminate(screen,c);
				stil=0;
				break;
			default: break;
		}
		SDL_Flip(screen);
	}
	SDL_FreeSurface(screen);
	free(mandel);
	SDL_Quit();
	printf("it vorks!\n");
	return 0;
}
