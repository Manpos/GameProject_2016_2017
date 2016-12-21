#pragma once
#include <SDL.h>
#include <SDL_image.h>

#define RND Renderer::Instance()

//Color values for SDL_RendererDrawColor
enum RGBA {
	R = 0, G = 0, B = 0, A = 0
};

class Renderer {
private:
	SDL_Renderer *renderer = NULL;
	struct ImgSize{
		int w, h;
	};
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
		SDL_RenderCopyEx(renderer, msgText, nullptr, &msgRect, 0, NULL, SDL_FLIP_NONE);
	}

	void PrintText(int x, int y, SDL_Texture *text, SDL_Rect* clip) {
		SDL_Rect renderQuad = { x, y, clip->w, clip->h };
		SDL_RenderCopyEx(renderer, text, clip, &renderQuad, 0, NULL, SDL_FLIP_NONE);
	}

	void PrintText(int x, int y, SDL_Texture *text, SDL_Rect* clip, double angle) {
		SDL_Rect renderQuad = { x, y, clip->w, clip->h };
		SDL_RenderCopyEx(renderer, text, clip, &renderQuad, angle, NULL, SDL_FLIP_NONE);
	}

	void CleanRenderer() {
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}

	//Loads an image and creates texture
	SDL_Surface* LoadImage(char* path) {
		IMG_Init(IMG_INIT_PNG);
		SDL_Texture *tTemp;
		SDL_Surface *tmp = IMG_Load(path);
		IMG_Quit();
		return tmp;
	}
	ImgSize getImageSize(SDL_Surface *img) {
		ImgSize tmp;
		tmp.w = img->w;
		tmp.h = img->h;
		return tmp;
	}
};


