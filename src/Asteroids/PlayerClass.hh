#pragma once
#include <SDL.h>
#include "InputManager.hh"
#include "GameObject.hh"
#include <iostream>
#include <time.h>
#include "transform.hh"

class Player : public GameObject{

private:

	int life;
	float rotValue;
	position refPt;
	float bulletCounter = 0;
	
	float friction = 0.90;
	float rotateSpeed = 5;
	float speed = 5;


public:

	// = pos.y - IM.GetMouseCoords().y
	float delta_y;
	float delta_x;
	double angle_deg = 0;

	// = pos.x - IM.GetMouseCoords().x

	void OnEntry() {

	}
	void Update() {
		move();
		if (!IM.ReturnMouseBlock()) {
			rotate();
		}
		rotValue = 90 + angle_deg;
		CheckBorders(id);

		ptPos.x = pos.x + (float)RND.spriteClips[PLAYER].w / 2.00;
		ptPos.y = pos.y + (float)RND.spriteClips[PLAYER].h / 2.00;

	};

	void Draw() {
		RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[PLAYER], rotValue);
		//std::cout << "Vel X: " << vel.x << "	Vel Y: " << vel.y << std::endl;
	}
	Player() {
		pos.x = 400;
		pos.y = 400;
		vel.x = 0;
		vel.y = 0;

		id = PLAYER;
	}
	Player(float x, float y, float velX, float velY, int lif, float refX, float refY) {
		pos.x = x;
		pos.y = y;
		//vel.x = velX;
		//vel.y = velY;
		life = lif;
		refPt.x = refX;
		refPt.y = refY;
	};

	void move() {

		if (IM.moveUp ) {

			vel.y += sin(AUX.degreesToRadians(angle_deg)) * speed;
			vel.x += cos(AUX.degreesToRadians(angle_deg)) * speed;
			if (vel.x >= 300) {
				vel.x = 300;
			}
			else if (vel.x <= -300) {
				vel.x = -300;
			}
			if (vel.y >= 300) {
				vel.y = 300;
			}
			else if (vel.y <= -300) {
				vel.y = -300;
			}
		}
		if (IM.noMove) {
			vel.x *= friction;
			vel.y *= friction;
		}
		
		if (IM.moveLeft) {
			angle_deg -= rotateSpeed ;
		}
		if (IM.moveRight) {
			angle_deg += rotateSpeed ;
		}
		
		pos.x += vel.x * TM.GetDeltaTime() ;
		pos.y += vel.y * TM.GetDeltaTime() ;

	};

	bool Shoot() {
		if (IM.IsShooting()) {
			if (bulletCounter < 0) {
				bulletCounter = 0.5;
				std::cout << "SHOT" << std::endl;
				return true;
			}
		}
		if (bulletCounter >= 0) {
			bulletCounter -= TM.GetDeltaTime();
			return false;
		}
		return false;
	}

	double rotate() {
	delta_y = IM.GetMouseCoords().y - pos.y;
	delta_x = IM.GetMouseCoords().x - pos.x;
	angle_deg = ((atan2(delta_y, delta_x) * 180.0000) / 3.1416);
	return angle_deg;
	}

};