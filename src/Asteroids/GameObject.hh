#pragma once
#include <SDL.h>

class GameObject {
protected:
	SDL_Texture *spriteSheetText = RND.SurfToText(RND.LoadImage("../../res/SpriteSheet.png"));

public:
	GameObject(){}
	void OnEntry();
	void Update();
	void Draw();
};