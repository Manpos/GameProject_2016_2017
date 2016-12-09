#pragma once
#include <SDL.h>
#include <iostream>
#include "Window.hh"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//Color values for SDL_RendererDrawColor
enum RGBA {
	R = 0, G = 0, B = 0, A = 0
};

class Renderer {
private:
	SDL_Renderer *renderer = NULL;
public:
	Renderer(SDL_Window*);
	~Renderer() { delete[] renderer; };
	SDL_Renderer* GetRenderer() {
		return renderer;
	}
};

Renderer::Renderer(SDL_Window* w) {
	renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, R, G, B, A);
}
