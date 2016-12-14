#pragma once
#include "Scene.hh"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_surface.h>
#include "InputManager.hh"
#include "Renderer.hh"


class GameScene : public Scene {
private:
	SDL_Surface *firstBoxMs, *secondBoxMs = NULL;
	TTF_Font *font = NULL;
	SDL_Color textColor = { 255,255,255 };

	SDL_Rect msgRect, msgRect2;
	SDL_Texture *firstBox, *secondBox;

public:
	GameScene() = default;
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
};
