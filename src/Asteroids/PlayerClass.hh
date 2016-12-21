#pragma once
#include <SDL.h>
#include "InputManager.hh"
#include "GameObject.hh"
#include "Renderer.hh"


class Player : public GameObject{
private:
	struct position {
		float x = 0, y = 0;
	};
	position pos;
	int life;
	position referencePoint;
public:
	//void Update();
	void Draw() {
		RND.PrintText(50,50, spriteSheetText, &spriteClips[AST_LAR_1]);
	}
	Player() = default;
	Player(float x, float y, int lif, float refX, float refY) {
		pos.x = x;
		pos.y = y;
		life = lif;
		referencePoint.x = refX;
		referencePoint.y = refY;
	};

	void move() {
		int mX = IM.GetMouseCoords().x;
		int mY = IM.GetMouseCoords().y;
	};
	
	void shoot() {
		
	}
};