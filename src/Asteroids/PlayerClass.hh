#pragma once
#include <SDL.h>
#include "InputManager.hh"
#include "GameObject.hh"
#include "Renderer.hh"
#include <iostream>
#include <time.h>

class Player : public GameObject{
private:
	struct position {
		float x = 400, y = 400;
	};
	struct velocity	{
		float x = 0, y = 0;
	};
	position pos;
	velocity vel;
	int life;
	position referencePoint;

/*
	float speed = 0.03;
	float rotateSpeed = 0.5;
	float friction = 0.95;

	float delta_y = pos.y - IM.GetMouseCoords().y;
	float delta_x = pos.x - IM.GetMouseCoords().x;
	double angle_deg = ((atan2(delta_y, delta_x) * 180.0000) / 3.1416);

*/
public:
	//void Update();
	void Draw() {
		RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[PLAYER], angle_deg);
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
		/*case FOWARD: 
			if (vel.x <= 0.5 && vel.y <= 0.5) {
				vel.y += sin(degreesToRadians(angle_deg)) * speed;
				vel.x += cos(degreesToRadians(angle_deg)) * speed;
			}
			break;
		case STATIC:
			vel.x *= friction;
			vel.y *= friction;
			break;
		case LEFT: 
			angle_deg -= rotateSpeed;
			break;
		case RIGHT:
			angle_deg += rotateSpeed;
			break;
		}

		pos.x += vel.x;
		pos.y += vel.y;
		
		std::cout << "Vel X: " << vel.x << "	Vel Y: " << vel.y << std::endl;*/
	};

	/*double rotate() {
	float delta_y = pos.y - IM.GetMouseCoords().y;
	float delta_x = pos.x - IM.GetMouseCoords().x;
	double angle_deg = -90 + ((atan2(delta_y, delta_x) * 180.0000) / 3.1416);
	return angle_deg;
	}*/

	float degreesToRadians(double degs) {
		return degs * 3.1416 / 180;
	}

	
	void shoot() {
		
	}
};