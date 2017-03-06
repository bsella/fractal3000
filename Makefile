all:
	gcc fractal.c `sdl-config --cflags --libs` -lm -o fractalTest
wall:
	gcc wall.c `sdl-config --cflags --libs` -lm -o fractalTest
	
