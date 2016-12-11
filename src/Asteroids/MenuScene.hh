#pragma once
#include "Scene.hh"
#include <SDL.h>
#include <SDL_ttf.h>
#include "InputManager.hh"
#include "Renderer.hh"
#include <SDL_surface.h>

//Class which Inherits from Scene.hh
class MenuScene : public Scene {
private:
	//FONTS
	SDL_Surface *startMs, *exitMs  = NULL;
	TTF_Font *font = NULL;
	SDL_Color textColor = { 255,255,255 };

	//BUTTONS
	SDL_Rect msgRect, msgRect2;
	SDL_Texture *start, *exit;

public:
	MenuScene() = default;
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
};