#pragma once
#include "AuxLib.hh"
#include <SDL.h>
#include "Renderer.hh"

class GameObject {
protected:
															// Loads the spritesheet as a texture
	SDL_Texture *spriteSheetText = RND.SurfToText(RND.LoadImage("../../res/SpriteSheet.png"));

	struct velocity {										// struct to store the velocity of the object
		float x , y;
	};

	struct Circle											// struct to store a circle used as a collider
	{
		float x, y, r;
	};

	SpriteID id;											// Object Id and velocity
	velocity vel;

	void CheckBorders(SpriteID sId) {						// Checks if the object is out of the window
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

public:

	struct position {										// struct to store the position
		float x, y;
	};

	position pos;											// Stores the position of the object
	Circle cir;												// Creates a circle struct

	GameObject(){}
	void OnEntry();
	void Update();
	void Draw();
	
};