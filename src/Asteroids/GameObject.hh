#pragma once
#include <SDL.h>

class GameObject {
protected:
	enum SpriteID {
		PLAYER, BULLET, AST_MED_1, AST_MED_2,
		AST_LIL_1, AST_LIL_2, AST_LAR_1, AST_LAR_2, AST_LAR_3, AST_LIL_3, OVNI
	};
	SDL_Texture *spriteSheetText = RND.SurfToText(RND.LoadImage("../../res/SpriteSheet.png"));
	SDL_Rect spriteClips[11];

public:

	void OnEntry() {

	}
	void Update();
	void Draw();
	void SetClipsValue() {
		spriteClips[0] = { 0, 0, 31,39 };
		spriteClips[1] = { 33, 31, 7, 8 };
		spriteClips[2] = { 41, 3, 38, 36 };
		spriteClips[3] = { 82, 2, 42, 38 };
		spriteClips[4] = { 128, 1, 19, 18 };
		spriteClips[5] = { 128, 22, 19, 21 };
		spriteClips[6] = { 156, 0, 97, 91 };
		spriteClips[7] = { 0, 52, 73, 71 };
		spriteClips[8] = { 77, 52, 74, 73 };
		spriteClips[9] = { 166, 104, 21, 19 };
		spriteClips[10] = { 196, 69, 53, 30 };
	}
};