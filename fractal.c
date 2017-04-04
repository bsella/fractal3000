#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include "parameterz.h"
#include "showFractal.h"
#include "loadFractal.h"

/*Pour "fractaliser" une image :
	//a=(carg(pp)+3.141593)/6.283186*w,
	//r=(h-log(cabs(pp))*(h/7.37790032);//3.6895016
*/

// void novaretti(SDL_Surface *screen, int x1, int y1, int x2, int y2){
// 	int x,y;
// 	Uint32 *pixels= screen->pixels;
// 	for (y=y1;y<y2;y++){
// 		for (x=x1;x<x2;x++){
// 			pixels[x+y*width]=SDL_MapRGB(screen->format,0,0,0);
// 			complex double p=conv(x,y);
// 			//c=p;//mandelbrot
// 			//SDL_Surface* im=image;
// 			double r=creal(p), i=cimag(p);
// 			double sum=0;
// 			for (int j=0;j<it;j++){
// 				double t4=24*r*r*r*r*r*i-4*r*r*r*cimag(c)-80*r*r*r*i*i*i+24*r*i*i*i*i*i+12*r*i*i*cimag(c)-12*r*r*i*creal(c)+4*i*i*i*creal(c)+2*creal(c)*cimag(c),
// 					   t3=4*r*r*r*r*r*r-60*r*r*r*r*i*i-4*r*r*r*creal(c)+60*r*r*i*i*i*i+12*r*r*i*cimag(c)+12*r*i*i*creal(c)-4*i*i*i*i*i*i-4*i*i*i*cimag(c)-cimag(c)*cimag(c)+creal(c)*creal(c),
// 					   t2=-24*r*r*r*i+24*r*i*i*i-6*i*creal(c)-6*r*cimag(c),
// 					   t1=-6*r*r*r*r+36*r*r*i*i-6*r*creal(c)-6*i*i*i*i+6*i*cimag(c);
// 					   //t5=1/(t3*t3+576*pow(r,10)*i*i-3840*pow(r,8)*i*i*i*i-192*pow(r,8)*i*cimag(c)-576*pow(r,7)*i*i*creal(c)+7552*pow(r,6)*pow(i,6)+1216*pow(r,6)*i*i*i*cimag(c)+16*pow(r,6)*cimag(c)*cimag(c)+2112*r*r*r*r*r*i*i*i*i*creal(c)+192*r*r*r*r*r*i*cimag(c)*creal(c)-3840*r*r*r*r*pow(i,8)-2112*r*r*r*r*i*i*i*i*i*cimag(c)-96*r*r*r*r*i*i*cimag(c)*cimag(c)+144*r*r*r*r*i*i*creal(c)*creal(c)-1216*r*r*r*pow(i,6)*creal(c)-640*r*r*r*i*i*i*cimag(c)*creal(c)-16*r*r*r*cimag(c)*cimag(c)*creal(c)+576*r*r*pow(i,10)+576*r*r*pow(i,7)*cimag(c)+144*r*r*i*i*i*i*cimag(c)*cimag(c)-96*r*r*i*i*i*i*creal(c)*creal(c)-48*r*r*i*cimag(c)*creal(c)*creal(c)+192*r*pow(i,8)*creal(c)+192*r*i*i*i*i*i*cimag(c)*creal(c)+48*r*i*i*cimag(c)*cimag(c)*creal(c)+16*pow(i,6)*creal(c)*creal(c)+16*i*i*i*cimag(c)*creal(c)*creal(c)+4*cimag(c)*cimag(c)*creal(c)*creal(c));
// 					   r=(t3*t1+t4*t2)/(t3*t3+t4*t4);
// 					   i=(t3*t2-t4*t1)/(t3*t3+t4*t4);
// 					sum+=log(r*r+i*i);
// 			}
// 					pixels[x+y*width]=color(screen,fabs(sum));
// 		}
// 	}
// }

void terminate(SDL_Surface *s, complex double c){
	printf("%f %f\n", creal(c), cimag(c));
	if(!opendir("output"))
		mkdir("output",700);
	SDL_SaveBMP(s, "output/test.bmp");
}

SDL_Surface **images;

pthread_mutex_t mutex;
void *run(void* screen){
	show(screen,images);
	while(1){
		pthread_mutex_lock(&mutex);
		while(dx!=0||dy!=0){
			decale((SDL_Surface*)screen,dx/500,-dy/500);
			show(screen,images);
		}
	}
	return NULL;
}

int width=1080, height=720;//3508 2480

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	SDL_Surface *screen=SDL_SetVideoMode(width,height,32,SDL_HWSURFACE);
	images=malloc(2*sizeof(SDL_Surface*));
	images[0]=SDL_LoadBMP("tigre.bmp");
	images[0]=SDL_ConvertSurface(images[0],screen->format,0);
	images[1]= SDL_LoadBMP("elinfinity.bmp");
	images[1]=SDL_ConvertSurface(images[1],screen->format,0); 
	
	
	mandel=malloc(width*height*sizeof(int));//iterations
	freyman=malloc(2*sizeof(double*));
	freyman[0]=malloc(width*height*sizeof(double));//x
	freyman[1]=malloc(width*height*sizeof(double));//y
	SDL_Joystick *joystick;
	if(SDL_NumJoysticks()){
		printf("%s\n", SDL_JoystickName(0));
		SDL_JoystickEventState(SDL_ENABLE);
		joystick=SDL_JoystickOpen(0);
	}
	
	load(0,0,width,height);
	int stop=0;
	show(screen, images);
	pthread_mutex_init(&mutex,NULL);
	pthread_mutex_lock(&mutex);
	pthread_t ptid;
	if(pthread_create(&ptid, NULL, &run, screen)!=0){
		perror("error creating thread");
		return 1;
	}
	while(!stop){
		SDL_Event event;
		SDL_WaitEvent(&event);
		int reload=1;
		switch(event.type){
			case SDL_JOYAXISMOTION:
				switch(event.jaxis.axis){
					case 0:
						setDX(event.jaxis.value-128);
						break;
					case 1:
						setDY(event.jaxis.value-128);
						break;
					default:break;
				}
				pthread_mutex_unlock(&mutex);
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
				show(screen,images);
				break;
			case SDL_JOYBUTTONDOWN:
				switch(event.jbutton.button){
					case 0: cDOWN(); break;
					case 1: cLEFT(); break;
					case 2: cRIGHT(); break;
					case 3: cUP(); break;
					case 4: dDOWN();reload=0;break;
					case 5: dUP();reload=0;break;
					case 6: maxDOWN();reload=0;break;
					case 7: maxUP();reload=0;break;
					case 8: unitDOWN();break;
					case 9: unitUP();break;
					default:reload=0; break;
				}
				if(reload)
					load(0,0,width,height);
				show(screen,images);
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_q: unitDOWN();break;
					case SDLK_w: unitUP();break;
					case SDLK_p: maxDOWN();reload=0;break;
					case SDLK_o: maxUP();reload=0;break;
					case SDLK_l: cRIGHT();break;
					case SDLK_j: cLEFT();break;
					case SDLK_i: cUP();break;
					case SDLK_k: cDOWN();break;
					case SDLK_MINUS: dDOWN();reload=0;break;
					case SDLK_EQUALS: dUP();reload=0;break;
					case SDLK_DOWN: decale(screen,0,-20);reload=0; break;
					case SDLK_LEFT: decale(screen,-20,0);reload=0; break;
					case SDLK_RIGHT: decale(screen,20,0);reload=0; break;
					case SDLK_UP: decale(screen,0,20);reload=0; break;
					case SDLK_RETURN: nextMode();reload=0;break;
					case SDLK_ESCAPE: terminate(screen,c); stop=1;break;
					default:reload=0;break;
				}
				if(reload)
					load(0,0,width,height);
				show(screen,images);
				break;
			case SDL_QUIT:
				terminate(screen,c);
				stop=1;
				break;
			default: break;
		}
	}
	SDL_FreeSurface(screen);
	SDL_FreeSurface(images[0]);
	SDL_FreeSurface(images[1]);
	free(images);
	free(mandel);
	free(freyman[0]);
	free(freyman[1]);
	free(freyman);
	SDL_Quit();
	printf("it vorks!\n");
	return 0;
}
