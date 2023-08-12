APP_NAME    := game
CC          := g++
SOURCES     := main.cpp TileMap.cpp FPS.cpp
COMP_FLAGS  := -Wall -Werror -Wextra -O3
SDL_MODULES := -lSDL2_image -lSDL2_ttf

ifeq ($(shell uname), Darwin)
	SDL_FLAGS := `sdl2-config --libs` $(SDL_MODULES) `sdl2-config --cflags`
else
	SDL_FLAGS := -lSDL2 $(SDL_MODULES)
endif

all: clean build run

build:
	$(CC) $(SOURCES) $(SDL_FLAGS) $(COMP_FLAGS) -o $(APP_NAME)

run:
	./$(APP_NAME)

clean:
	rm -rf $(APP_NAME)

.PHONY: all build run clean
