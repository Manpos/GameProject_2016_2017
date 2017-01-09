#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include "TimeManager.hh"

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
	 //(AUX.w / 2) - (rect.w / 2)

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
		renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

	//Renders a texture including clipping and rotation angle
	void PrintText(int x, int y, SDL_Texture *text, SDL_Rect* clip, double angle = 0) {
		SDL_Rect renderQuad = { x, y, clip->w, clip->h };
		SDL_RenderCopyEx(renderer, text, clip, &renderQuad, angle, NULL, SDL_FLIP_NONE);
	}

	//Functions to clean the renderer
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

	//Returns the size of an Image if it's a SDL_Surface
	ImgSize getImageSize(SDL_Surface *img) {
		ImgSize tmp;
		tmp.w = img->w;
		tmp.h = img->h;
		return tmp;
	}
	//Returns a RTxture with a solid color depending on the RGBA values introduced
	RTexture CreateSolid(Uint32 R, Uint32 G, Uint32 B, Uint32 A, SDL_Rect *rect = nullptr) {
		SDL_Surface *surf = SDL_CreateRGBSurface(0, AUX.w, AUX.h, 32, 0, 0, 0, 0);
		SDL_FillRect(surf, rect, SDL_MapRGB(surf->format, R, G, B));
		RTexture res;
		res.text = RND.SurfToText(surf);
		SDL_SetTextureBlendMode(res.text, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(res.text, A);
		if (rect == nullptr) {
			res.rect.w = AUX.w;
			res.rect.h = AUX.h;
			res.rect.x = 0;
			res.rect.y = 0;
		}
		else res.rect = *rect;

		return res;
	}

	//Declaration of the clipping values
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
	//Loads a font from a path and gives it a size
	TTF_Font *LoadFont(const char* path, int size) {
		TTF_Font *font = nullptr;
		font = TTF_OpenFont(path, size);
		return font;
	}

	//Loads and prepares a font
	RTexture LPFont(const char* path, int size,const char* txt, Uint8 R, Uint8 G, Uint8 B) {
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

	RTexture PrepareFont(TTF_Font *font, const char* txt, Uint8 R, Uint8 G, Uint8 B) {
		RTexture res;
		SDL_Color textColor = { R, G, B };
		SDL_Surface *surf = nullptr;
		SDL_Rect rec;
		surf = TTF_RenderText_Solid(font, txt, textColor);
		rec = { 0,0, surf->w, surf->h };
		res.text = SurfToText(surf);
		res.rect = rec;
		return res;
	}
};


