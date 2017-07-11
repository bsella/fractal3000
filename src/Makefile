CC=gcc
CCFLAGS=-Wall
LDFLAGS=`sdl-config --cflags --libs` -lm
objects= main.o palette.o fractal.o parameterz.o input.o
EXE= eliFractal

all: $(EXE)

wall:
	$(CC) wall.c $(OPT) -o fractalTest

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(EXE): $(objects)
	$(CC) $(LDFLAGS) $(objects) -o $@

clean:
	rm -f *.o $(EXE)