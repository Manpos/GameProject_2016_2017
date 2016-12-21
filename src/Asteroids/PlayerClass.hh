#pragma once
#include <SDL.h>
#include "InputManager.hh"
#include "GameObject.hh"
#include "Renderer.hh"
#include <iostream>


class Player : public GameObject{
private:
	struct position {
		float x = 400, y = 400;
	};
	position pos;
	int life;
	position referencePoint;
public:
	//void Update();
	void Draw() {
		RND.PrintText(pos.x, pos.y, spriteSheetText, &spriteClips[PLAYER], rotate());
		move();
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
		switch (IM.returnMovement())
		{
		case 1: pos.y -= 0.05; break;
		case 2: pos.x -= 0.05; break;
		case 3: pos.y += 0.05; break;
		case 4: pos.x += 0.05; break;
		}
	};

	double rotate() {
		float delta_y =  pos.y - IM.GetMouseCoords().y;
		float delta_x =  pos.x - IM.GetMouseCoords().x;
		double angle_deg = -90 + ((atan2(delta_y, delta_x) * 180.0000) / 3.1416);
		return angle_deg;
	}
	
	void shoot() {
		
	}
};