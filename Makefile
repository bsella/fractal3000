CC=gcc
OPT=`sdl-config --cflags --libs` -lm

all: main.o showfractal.o loadfractal.o parameterz.o
	$(CC) main.o parameterz.o showfractal.o loadfractal.o $(OPT) -o fractalTest
	make clean
wall:
	$(CC) wall.c $(OPT) -o fractalTest
	
showfractal.o:
	$(CC) -c showfractal.c -o showfractal.o
loadfractal.o:
	$(CC) -c loadfractal.c -o loadfractal.o
parameterz.o:
	$(CC) -c parameterz.c -o parameterz.o
main.o:
	$(CC) -c fractal.c -o main.o

clean:
	rm -f *.o