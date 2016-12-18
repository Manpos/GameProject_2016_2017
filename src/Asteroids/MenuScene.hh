#pragma once
#include "Scene.hh"

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
	bool isPlaying = false;
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
};