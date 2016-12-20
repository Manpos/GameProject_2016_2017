#pragma once
#include <SDL.h>
#include "InputManager.hh"
#include "Window.hh"


struct position {
	float x, y;
};

class Player {
private:
	position pos;
	int life;
	position referncePoint;
	SDL_Rect area;
public:
	Player(float x, float y, int lif, float refX, float refY) {
		pos.x = x;
		pos.y = y;
		life = lif;
		referncePoint.x = refX;
		referncePoint.y = refY;
	};

	void move() {
		int mX = IM.GetMouseCoords().x;
		int mY = IM.GetMouseCoords().y;
	};
	
	void shoot() {
		
	}
};