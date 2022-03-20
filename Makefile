_GUI = $(if $(NOGUI),, -D GUI)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99 -Wall $(_OPT) $(_GUI) $(_DEBUG) -I./include 
LDFLAGS = `sdl2-config --cflags --libs` #-lSDL -lm

.PHONY: clean doc check-syntax compile-all launch-tests

# rule to remove all .o files and all executables
clean:
	- rm -f *.o
	- find . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete

# compile rules
%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^


main: main.o game.o 
	$(CC) $(CFLAGS) -o$@ $^ $(LDFLAGS)

run: main
	./main