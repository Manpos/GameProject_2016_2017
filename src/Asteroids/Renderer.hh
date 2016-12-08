#pragma once
#include <SDL.h>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
int main(int argc, char* args[]) {
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

	}
}