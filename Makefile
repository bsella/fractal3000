CC=gcc
srcDIR=src
CCFLAGS=-Wall
LDFLAGS=`sdl-config --cflags --libs` -lm -lpthread -lSDL
EXE=eliFractal
INCLUDE=-I include
objects=main.o palette.o fractal.o parameterz.o input.o

all: $(EXE)

%.o: $(srcDIR)/%.c
	$(CC) $(CCFLAGS) -c $(INCLUDE) $< -o $@

$(EXE): $(objects)
	$(CC) $(objects) -o $@ $(LDFLAGS)

clean:
	rm -rf $(objects) $(EXE)