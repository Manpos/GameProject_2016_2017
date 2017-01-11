#pragma once
#include <SDL.h>
#include "GameObject.hh"
#include <time.h>

#define q 10000													// Value used to modify the speed in function of the score
enum EnemyType { SMALL, MEDIUM, LARGE, S_OVNI, L_OVNI };		// Enum of type of enemy

class Enemy : public GameObject{
private:
			
	float rotateSpeed = 1.5, rotateBase = 0;					// Rotation variables
	float rotValue;
	float difSpeed;
	int *currentScore = nullptr;
	int dirX, dirY;												// Direction variables

public:

	bool colidedByBullet = false;								// Checks if the enemy is hit by a bullet
	EnemyType type;												// Defines the type of enemy

	Enemy(float difSpd, int* score) {							// Constructor used to create an enemy
		vel.x = 0;
		vel.y = 0;
		id = (SpriteID)(rand() % 8 + 2);
		difSpeed = difSpd;
		currentScore = score;
	} 

	Enemy(float x, float y, EnemyType ty, float difSpd, float velX, float velY, int* score) {	// Constructor used to create two enemies from a  larger enemy
		pos.x = x;
		pos.y = y;
		type = ty;
		difSpeed = difSpd;
		currentScore = score;
		switch (type)
		{
		case SMALL:
			id = (SpriteID)(rand() % 2 + 4);
			vel.x = velX + 1;
			vel.y = velY + 1;
			break;
		case MEDIUM:
			id = (SpriteID)(rand() % 2 + 2);
			vel.x = velX + 0.5;
			vel.y = velY + 0.5;
			break;
		default:
			break;
		}
		cir.r = RND.spriteClips[id].w / 2;						// Defines the value of the radius
	};

	void OnEntry() {

		pos.x = RandomPos().x;									// Set random values to enemy position at start
		pos.y = RandomPos().y;

		dirX = RandomVelocityDir();
		dirY = RandomVelocityDir();

		RandomType();

		switch (type)
		{
		case SMALL:
			id = (SpriteID)(rand() % 2 + 4);
			vel.x = ((1.5) * difSpeed) * dirX + rand() % 2;
			vel.y = ((1.5) * difSpeed) * dirY;
				break;
		case MEDIUM:
			id = (SpriteID)(rand() % 2 + 2);
			vel.x = ((1) * difSpeed) * dirX + rand() % 5;
			vel.y = ((1) * difSpeed) * dirY;
			break;
		case LARGE:
			id = (SpriteID)(rand() % 3 + 6);
			vel.x = ((0.5) * difSpeed) * dirX + rand() % 5;
			vel.y = ((0.5) * difSpeed) * dirY;
			break;
		case S_OVNI:
			break;
		case L_OVNI:
			break;
		default:
			break;
		}

		cir.r = RND.spriteClips[id].w / 2;						// Define the value of the radius
	}


	void Update() {

		CheckBorders(id);
		rotValue = rotateEnemy();
		move(*currentScore);	

		cir.x = pos.x + (float)RND.spriteClips[id].w / 2.00;	// Gives value to the cir.x and the cir.y
		cir.y = pos.y + (float)RND.spriteClips[id].h / 2.00;	// in the function of the position of the object

	}

	void Draw() {												// Renders the enemy
		RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[id], rotValue);
	}
	
	Position RandomPos() {										// Generates a random position
		Position tmp;
		tmp.x = rand() % AUX.w;
		tmp.y = rand() % AUX.h;
		if (tmp.x <= AUX.w / 2) {
			tmp.x -= AUX.w;
		}
		else { tmp.x += AUX.w; }
		//tmp.x -= AUX.w;
		//tmp.y -= AUX.h;
		return tmp;
		}

	float rotateEnemy() {										// Used to rotate the enemy
		if (rotateBase >= 360) {
			rotateBase = 0;
			return rotateBase;
		}
		else return (rotateBase += rotateSpeed);
	}

	void move(int score) {										// Used to move the enemy
		pos.x += ((vel.x + ((float)score / float(q)*dirX)));
		pos.y += ((vel.y + ((float)score / float(q)*dirY)));
	}

	velocity GetVelocity() {									// Used to return the velocity externally
		return vel;
	}

	int RandomVelocityDir() {									// Used to give a random direction
		int tmp = rand() % 2;
		if (tmp == 1) {
			return 1;
		}
		else return -1;
	}

	void RandomType() {											// Used to give a random type to the enemy
		int randValue = rand() % 3;
		switch (randValue)
		{
		case 0: type = SMALL; break;
		case 1: type = MEDIUM; break;
		case 2: type = LARGE; break;
		}
	}
};