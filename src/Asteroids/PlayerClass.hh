#pragma once
#include <SDL.h>
#include "InputManager.hh"
#include "GameObject.hh"
#include <iostream>
#include <time.h>
#include "transform.hh"

#define SHOOT_TIME 0.25

class Player : public GameObject{

private:

	float rotValue;
	position refPt;
	float bulletCounter = 0;
	
	float friction = 0.90;
	float rotateSpeed = 5;
	float speed = 5;

public:

	int life;
	bool dead = false;
	float respawnTime = 0.0;
	bool invulnerable = false;
	float invTime;

	float delta_y;
	float delta_x;
	double angle_deg = 0;
	bool alive = true;

	void Update() {
		if (dead) {	
		Respawn(3); 
		}

		else {
			invulnerable = Invulnerability();
			Move();
			if (!IM.ReturnMouseBlock()) {
				Rotate();
			}
			rotValue = 90 + angle_deg;
			CheckBorders(id);
		}				

		if (life <= 0) { alive = false;	}

		cir.x = pos.x + (float)RND.spriteClips[PLAYER].w / 2.00;
		cir.y = pos.y + (float)RND.spriteClips[PLAYER].h / 2.00;

	};

	void Draw() {
		if (!dead) {
			RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[PLAYER], rotValue);
		}		
	}

	Player(int lf) {
		pos.x = AUX.w/2;
		pos.y = AUX.h/2;
		vel.x = 0;
		vel.y = 0;
		life = lf;
		cir.r = RND.spriteClips[PLAYER].w / 2;
		id = PLAYER;
	}

	void Move() {

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
		if (IM.IsShooting() && !dead) {
			if (bulletCounter < 0) {
				bulletCounter = SHOOT_TIME;
				return true;
			}
		}
		if (bulletCounter >= 0) {
			bulletCounter -= TM.GetDeltaTime();
			return false;
		}
		return false;
	}

	double Rotate() {
	delta_y = IM.GetMouseCoords().y - pos.y;
	delta_x = IM.GetMouseCoords().x - pos.x;
	angle_deg = ((atan2(delta_y, delta_x) * 180.0000) / 3.1416);
	return angle_deg;
	}

	bool Invulnerability() {
		if (invTime > 0) {
			invTime -= TM.GetDeltaTime();
			return true;
		}
		else return false;
	}

	void Respawn(float iTime) {
		if (life > 0 && respawnTime < 0) {
			--life;
			this->pos.x = AUX.w / 2;
			this->pos.y = AUX.h / 2;
			this->vel.x = 0;
			this->vel.y = 0;
			invTime = iTime;
			dead = false;
		}

		if (respawnTime <= 0) {
			respawnTime = 2;
		}
		
		if (respawnTime > 0) {
			respawnTime -= TM.GetDeltaTime();
		}
	}

	template <typename T>
	void CheckEnemiesColision(std::vector<T> enemies) {
		float totalRadius, totalRadiusSquared, distancePoints;
		for (auto i = enemies.begin(); i != enemies.end(); ++i) {
			totalRadius = cir.r + i->cir.r;
			totalRadiusSquared = totalRadius * totalRadius;
			distancePoints = pow((i->cir.x - cir.x), 2) + pow((i->cir.y - cir.y), 2);
			if (distancePoints <= totalRadiusSquared) {
				dead = true;
			}
		}
	}

};