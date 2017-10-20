#include <SDL/SDL.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include "input.h"
#include "parameterz.h"
#include "palette.h"
#include "fractal.h"

void terminate(SDL_Surface *s, complex double c){
	printf("c= %f %f\n", creal(c), cimag(c));
	printf("unit= %f\n", unit);
	printf("center= %f %f\n", creal(center), cimag(center));
	if(!opendir("./output"))
		mkdir("./output",700);
	SDL_SaveBMP(s, "./output/test.bmp");
}

void *run(void* screen){
	show(screen,images);
	while(1){
		pthread_mutex_lock(&mutex);
		while(dx!=0||dy!=0){
			decale(dx/500,-dy/500);
			show(screen,images);
		}
	}
	return NULL;
}

void loop(){
	int run=1;
	SDL_Event event;
	while(run){
		SDL_WaitEvent(&event);
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
					case SDL_HAT_DOWN: decale(0,-20); break;
					case SDL_HAT_LEFT: decale(-20,0); break;
					case SDL_HAT_RIGHT: decale(20,0); break;
					case SDL_HAT_UP: decale(0,20); break;
					case SDL_HAT_RIGHTDOWN: decale(20,-20); break;
					case SDL_HAT_LEFTDOWN: decale(-20,-20); break;
					case SDL_HAT_RIGHTUP: decale(20,20); break;
					case SDL_HAT_LEFTUP: decale(-20,20); break;
					default:break;
				}
				show(screen,images);
				break;
			case SDL_JOYBUTTONDOWN:
				switch(event.jbutton.button){
					case 0: cDOWN(); load(0,0,width,height); break;
					case 1: cLEFT(); load(0,0,width,height); break;
					case 2: cRIGHT(); load(0,0,width,height); break;
					case 3: cUP(); load(0,0,width,height); break;
					case 4: dDOWN();break;
					case 5: dUP();break;
					case 6: maxDOWN();break;
					case 7: maxUP();break;
					case 8: unitDOWN(); load(0,0,width,height);break;
					case 9: unitUP(); load(0,0,width,height);break;
					default: break;
				}
				show(screen,images);
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_q: unitDOWN(); load(0,0,width,height); break;
					case SDLK_w: unitUP(); load(0,0,width,height); break;
					case SDLK_p: maxDOWN();break;
					case SDLK_o: maxUP();break;
					case SDLK_l: cRIGHT(); load(0,0,width,height);break;
					case SDLK_j: cLEFT(); load(0,0,width,height);break;
					case SDLK_i: cUP(); load(0,0,width,height);break;
					case SDLK_k: cDOWN(); load(0,0,width,height);break;
					case SDLK_MINUS: dDOWN();break;
					case SDLK_EQUALS: dUP();break;
					case SDLK_DOWN: decale(0,-20); break;
					case SDLK_LEFT: decale(-20,0); break;
					case SDLK_RIGHT: decale(20,0); break;
					case SDLK_UP: decale(0,20); break;
					case SDLK_RETURN: nextMode();break;
					case SDLK_ESCAPE: terminate(screen,c); run=0;break;
					default: break;
				}
				show(screen,images);
				break;
			case SDL_MOUSEBUTTONDOWN:{
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX,&mouseY);
				printf("(%d,%d) (%f,%f)\n", mouseX, mouseY,freyman[0][mouseX+mouseY*width],freyman[1][mouseX+mouseY*width]);
				break;
			}
			case SDL_QUIT:
				terminate(screen,c);
				run=0;
				break;
			default: break;
		}
	}
}