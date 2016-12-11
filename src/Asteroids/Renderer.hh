#pragma once
#include <SDL.h>

#define RND Renderer::Instance()

//Color values for SDL_RendererDrawColor
enum RGBA {
	R = 0, G = 0, B = 0, A = 0
};

class Renderer {
private:
	SDL_Renderer *renderer = NULL;
public:
	inline static Renderer& Instance() {
		static Renderer a;
		return a;
	}

	void SetWindow(SDL_Window* w) {
		renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(renderer, R, G, B, A);
	};

	SDL_Renderer* GetRenderer() {
		return renderer;
	}

	SDL_Texture* SurfToText(SDL_Surface *surface) {
		auto msgText = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		return msgText;
	}
	void PrintText(SDL_Rect msgRect, SDL_Texture *msgText) {
		SDL_RenderCopy(renderer, msgText, nullptr, &msgRect);
	}
	void CleanRenderer() {
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
};


