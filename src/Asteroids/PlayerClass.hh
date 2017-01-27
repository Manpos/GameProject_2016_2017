#pragma once
#include <SDL.h>
#include "InputManager.hh"
#include "GameObject.hh"
#include <iostream>
#include <time.h>
#include "transform.hh"

// Time between two bullets (shooting delay), in seconds
#define SHOOT_TIME 20

class Player : public GameObject{

private:

	float rotValue;					// Rotation of the player
	float bulletCounter = 0;		// Timer between two bullets when the player shoot	
	float friction = 0.90;			// Makes the ship break when the player stops accelerating
	float rotateSpeed = 5;			// Value which define the rotation velocity of the ship when playing with the keyboard
	float speed = 0.1;				// Speed value

public:

	int life;						// Stores the player remaining lifes
	bool dead = false;				// Stores if the player has crashed
	float respawnTime = 0.0;		// Time to respawn after death
	bool invulnerable = false;		// Stores if the player has invulnerability
	float invTime;					// Stores the invulnerability time

	float delta_y;					// Vector y component
	float delta_x;					// Vector x component
	double angle_deg = 0;			// Current angle value
	bool alive = true;				// Stores if the player has lifes remaining

	void Update() {
		// If the player dies calls the Respawn() function
		if (dead) {	
			Respawn(200); 
		}

		//Executes the movement and collision check
		else {
			invulnerable = Invulnerability();
			Move();
			if (!IM.ReturnMouseBlock()) {
				Rotate();
			}
			rotValue = 90 + angle_deg;
			CheckBorders(id);
		}				

		// If life gets to 0 changes alive to false and changes from scene
		if (life <= 0) { alive = false;	}

		//cir.x and cir.y are updated in function of the player position
		cir.x = pos.x + (float)RND.spriteClips[PLAYER].w / 2.00;
		cir.y = pos.y + (float)RND.spriteClips[PLAYER].h / 2.00;

	};

	// Draws the player, including rotation
	void Draw() {
		if (!dead) {
			RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[PLAYER], rotValue);
		}		
	}

	//Constructor of the class player
	Player(int lf) {
		pos.x = AUX.w/2;
		pos.y = AUX.h/2;
		vel.x = 0;
		vel.y = 0;
		life = lf;
		cir.r = RND.spriteClips[PLAYER].w / 2;
		id = PLAYER;
	}

	//Gets the user input and moves the ship adding velocity
	void Move() {

		if (IM.moveUp ) {

			// Takes the angle to get the direction when pointing at the mouse or rotating
			vel.y += sin(AUX.degreesToRadians(angle_deg)) * speed;
			vel.x += cos(AUX.degreesToRadians(angle_deg)) * speed;

			// These ifs limit the max speed of the ship
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

		//Used to add friction
		if (IM.noMove) {
			vel.x *= friction;
			vel.y *= friction;
		}
		
		//Used to rotate the ship with the keyboard
		if (IM.moveLeft) {
			angle_deg -= rotateSpeed ;
		}
		if (IM.moveRight) {
			angle_deg += rotateSpeed ;
		}
		
		pos.x += vel.x;
		pos.y += vel.y;

	};

	// Returns if the player is able to shoot after an amount of time
	bool Shoot() {
		if (IM.IsShooting() && !dead) {
			if (bulletCounter < 0) {
				bulletCounter = SHOOT_TIME;
				return true;
			}
		}
		if (bulletCounter >= 0) {
			bulletCounter -= 1;
			return false;
		}
		return false;
	}

	// Method used to rotate the player with the mouse position
	double Rotate() {
	delta_y = IM.GetMouseCoords().y - pos.y;
	delta_x = IM.GetMouseCoords().x - pos.x;
	angle_deg = ((atan2(delta_y, delta_x) * 180.0000) / 3.1416);
	return angle_deg;
	}

	// Returns a bool to activate or desactivate the player collision
	bool Invulnerability() {
		if (invTime > 0) {
			invTime -= 1;
			return true;
		}
		else return false;
	}

	// Replaces the player to the center when dead and removes 1 life
	void Respawn(float iTime) {
		if (life > 0 ) {
			--life;
			this->pos.x = AUX.w / 2;
			this->pos.y = AUX.h / 2;
			this->vel.x = 0;
			this->vel.y = 0;
			invTime = iTime;
			dead = false;
		}
	}

	// Checks the collision of the player with the enemies
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