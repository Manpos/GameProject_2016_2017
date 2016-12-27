#pragma once
#include "AuxLib.hh"
#include <SDL.h>
#include "Renderer.hh"

class GameObject {
protected:
	SDL_Texture *spriteSheetText = RND.SurfToText(RND.LoadImage("../../res/SpriteSheet.png"));
	struct position {
		float x, y;
	};
	struct velocity {
		float x , y;
	};

	void CheckBorders(SpriteID sId) {
		if (pos.x + RND.spriteClips[sId].w < 0) {
			pos.x = AUX.w;
		}

		else if (pos.x > AUX.w) {
			pos.x = 0 - RND.spriteClips[sId].w;
		}

		else if (pos.y > AUX.h) {
			pos.y = 0 - RND.spriteClips[sId].h;
		}

		else if (pos.y + RND.spriteClips[sId].h < 0) {
			pos.y = AUX.h;
		}
	}

	SpriteID id;
	position pos;
	velocity vel;
public:

	GameObject(){}
	void OnEntry();
	void Update();
	void Draw();
	
};