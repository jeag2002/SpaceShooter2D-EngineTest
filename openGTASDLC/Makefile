CC=gcc
WINCC=i586-mingw32msvc-gcc

FLAGS = -lm -lGL -lGLU `sdl-config --cflags --libs`
WINFLAGS = -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32 -lm -mwindows -L.

all:
	$(CC) -g *.c -o topdown $(FLAGS)
	
win:
	$(WINCC) -g *.c -o topdown.exe $(WINFLAGS)
