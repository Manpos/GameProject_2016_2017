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
	position referencePoint;
	bool hasShoot = false;
	int bulletCounter = 2;
	
	float friction = 0.95;
	float rotateSpeed = 0.5;
	float speed = 10;
	double angle_deg = ((atan2(delta_y, delta_x) * 180.0000) / 3.1416);


public:

	// = pos.y - IM.GetMouseCoords().y
	float delta_y;
	float delta_x;
	// = pos.x - IM.GetMouseCoords().x

	void OnEntry() {

	}
	void Update() {
		move();
		rotate();
		rotValue = angle_deg;
		CheckBorders(id);
	};

	void Draw() {
		RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[PLAYER], rotValue);
		std::cout << "Vel X: " << vel.x << "	Vel Y: " << vel.y << std::endl;
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
		referencePoint.x = refX;
		referencePoint.y = refY;
	};

	void move() {

		if (IM.returnMovement() == FOWARD) {
			if (vel.x <= 70 || vel.y <= 70) {
				vel.y += sin(degreesToRadians(angle_deg)) * speed;
				vel.x += cos(degreesToRadians(angle_deg)) * speed;
			}
		}
		if (IM.returnMovement() == STATIC) {
			vel.x *= friction;
			vel.y *= friction;
		}
		
		if (IM.returnMovement() == LEFT) {
			angle_deg -= rotateSpeed ;
		}
		if (IM.returnMovement() == RIGHT) {
			angle_deg += rotateSpeed ;
		}
		
		pos.x += vel.x * TM.GetDeltaTime() ;
		pos.y += vel.y * TM.GetDeltaTime() ;
		/*
		std::cout << "Vel X: " << vel.x << "	Vel Y: " << vel.y << std::endl;

		switch (IM.returnMovement())
		{
		case 1: pos.y -= vel.y * TM.GetDeltaTime(); break;
		case 2: pos.x -= vel.x * TM.GetDeltaTime(); break;
		case 3: pos.y += vel.y * TM.GetDeltaTime(); break; 
		case 4: pos.x += vel.x * TM.GetDeltaTime(); break;
		}*/
	};

	bool Shoot() {
		if (IM.IsShooting() && !hasShoot) {
			if (bulletCounter >= 200) {
				hasShoot = true;
				bulletCounter = 0;
				std::cout << "SHOT" << std::endl;
				return true;
			}
		}
		if (bulletCounter < 200) {
			bulletCounter += 1;
			hasShoot = false;
			return false;
		}
		return false;
	}

	double rotate() {
	delta_y = pos.y - IM.GetMouseCoords().y;
	delta_x = pos.x - IM.GetMouseCoords().x;
	angle_deg = -90 + ((atan2(delta_y, delta_x) * 180.0000) / 3.1416);
	return angle_deg;
	}

	float degreesToRadians(double degs) {
		return degs * 3.1416 / 180;
	}
};