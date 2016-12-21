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
	struct velocity	{
		float x = 0.2, y = 0.2;
	};
	position pos;
	velocity vel;
	int life;
	position referencePoint;
public:
	//void Update();
	void Draw() {
		RND.PrintText(pos.x, pos.y, spriteSheetText, &spriteClips[PLAYER], rotate());
		move();
	}
	Player() = default;
	Player(float x, float y, float velX, float velY, int lif, float refX, float refY) {
		pos.x = x;
		pos.y = y;
		vel.x = velX;
		vel.y = velY;
		life = lif;
		referencePoint.x = refX;
		referencePoint.y = refY;
	};

	void move() {
		switch (IM.returnMovement())
		{
		case 1: pos.y -= vel.y; break;
		case 2: pos.x -= vel.x; break;
		case 3: pos.y += vel.y; break;
		case 4: pos.x += vel.x; break;
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