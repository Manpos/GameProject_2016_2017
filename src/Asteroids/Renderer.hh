#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define RND Renderer::Instance()

//Color values for SDL_RendererDrawColor
enum RGBA {
	R = 0, G = 0, B = 0, A = 0
};

enum SpriteID {
	PLAYER, BULLET, AST_MED_1, AST_MED_2,
	AST_LIL_1, AST_LIL_2, AST_LAR_1, AST_LAR_2, AST_LAR_3, AST_LIL_3, OVNI
};

//Texture with Rectangle attached
struct RTexture {
	SDL_Rect rect;
	SDL_Texture *text = nullptr;
};

class Renderer {
private:
	SDL_Renderer *renderer = NULL;

	struct ImgSize{
		int w, h;
	};

public:

	SDL_Rect spriteClips[11];

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

	void PrintText(int x, int y, SDL_Texture *text, SDL_Rect* clip, double angle = 0) {
		SDL_Rect renderQuad = { x, y, clip->w, clip->h };
		SDL_RenderCopyEx(renderer, text, clip, &renderQuad, angle, NULL, SDL_FLIP_NONE);
	}

	void CleanRenderer() {
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}

	//Loads an image and creates surface
	SDL_Surface* LoadImage(char* path) {
		IMG_Init(IMG_INIT_PNG);
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

	void SetClips(){
		spriteClips[PLAYER] = { 0, 0, 31,39 };
		spriteClips[BULLET] = { 33, 31, 7, 8 };
		spriteClips[AST_MED_1] = { 41, 3, 38, 36 };
		spriteClips[AST_MED_2] = { 82, 2, 42, 38 };
		spriteClips[AST_LIL_1] = { 128, 1, 19, 18 };
		spriteClips[AST_LIL_2] = { 128, 22, 19, 21 };
		spriteClips[AST_LAR_1] = { 156, 0, 97, 91 };
		spriteClips[AST_LAR_2] = { 0, 52, 73, 71 };
		spriteClips[AST_LAR_3] = { 77, 52, 74, 73 };
		spriteClips[AST_LIL_3] = { 166, 104, 21, 19 };
		spriteClips[OVNI] = { 196, 69, 53, 30 };
	}

	RTexture LoadFont(const char* path, int size, char* txt, int R, int G, int B) {
		RTexture res;
		SDL_Color textColor = { R, G, B };
		TTF_Font *font = nullptr;
		SDL_Surface *surf = nullptr;
		SDL_Rect rec;
		font = TTF_OpenFont(path, size);
		surf = TTF_RenderText_Solid(font, txt, textColor);
		rec = { 0,0, surf->w, surf->h };
		res.text = SurfToText(surf);
		res.rect = rec;
		return res;
	}
};


