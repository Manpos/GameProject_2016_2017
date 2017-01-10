#pragma once
#include <SDL.h>
#include "GameObject.hh"
#include <time.h>

#define q 10000
enum EnemyType { SMALL, MEDIUM, LARGE, S_OVNI, L_OVNI };

class Enemy : public GameObject{
private:
	SDL_Rect area;
	float rotateSpeed = 50, rotateBase = 0;
	float rotValue;
	int rotateSide;
	float difSpeed;
	int *currentScore = nullptr;
	int dirX, dirY;
public:

	bool colidedByBullet = false; // Checks if the enemy is hit by a bullet
	EnemyType type;

	Enemy(float difSpd, int* score) {
		vel.x = 0;
		vel.y = 0;
		id = (SpriteID)(rand() % 8 + 2);
		difSpeed = difSpd;
		currentScore = score;
	} 

	Enemy(float x, float y, EnemyType ty, float difSpd, float velX, float velY, int* score) {
		pos.x = x;
		pos.y = y;
		type = ty;
		difSpeed = difSpd;
		currentScore = score;
		switch (type)
		{
		case SMALL:
			id = (SpriteID)(rand() % 2 + 4);
			vel.x = velX + velX;
			vel.y = velY + velY;
			break;
		case MEDIUM:
			id = (SpriteID)(rand() % 2 + 2);
			vel.x = velX + velX;
			vel.y = velY + velY;
			break;
		default:
			break;
		}
		cir.r = RND.spriteClips[id].w / 2;
	};

	void OnEntry() {

		pos.x = RandomPos().x;
		pos.y = RandomPos().y;

		dirX = RandomVelocityDir();
		dirY = RandomVelocityDir();

		RandomType();

		switch (type)
		{
		case SMALL:
			id = (SpriteID)(rand() % 2 + 4);
			vel.x = (((rand() % 40) + 150) * difSpeed) * dirX;
			vel.y = (((rand() % 40) + 150) * difSpeed) * dirY;
			break;
		case MEDIUM:
			id = (SpriteID)(rand() % 2 + 2);
			vel.x = (((rand() % 30) + 100) * difSpeed) * dirX;
			vel.y = (((rand() % 30) + 100) * difSpeed) * dirY;
			break;
		case LARGE:
			id = (SpriteID)(rand() % 3 + 6);
			vel.x = (((rand() % 20) + 50) * difSpeed) * dirX;
			vel.y = (((rand() % 20) + 50) * difSpeed) * dirY;
			break;
		case S_OVNI:
			break;
		case L_OVNI:
			break;
		default:
			break;
		}

		cir.r = RND.spriteClips[id].w / 2;
	}


	void Update() {

		CheckBorders(id);
		rotValue = rotateEnemy();
		move(*currentScore);	

		cir.x = pos.x + (float)RND.spriteClips[id].w / 2.00;
		cir.y = pos.y + (float)RND.spriteClips[id].h / 2.00;

	}

	void Draw() {
		RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[id], rotValue);
	}
	
	Position RandomPos() {
		Position tmp;
		tmp.x = rand() % AUX.w;
		tmp.y = rand() % AUX.h;
		tmp.x -= AUX.w;
		tmp.y -= AUX.h;
		return tmp;
	}

	float rotateEnemy() {
		if (rotateBase >= 360) {
			rotateBase = 0;
			return rotateBase;
		}
		else return (rotateBase += rotateSpeed*TM.GetDeltaTime());
	}

	void move(int score) {		
		pos.x += ((vel.x + ((float)score / float(q)*dirX)))*TM.GetDeltaTime();
		pos.y += ((vel.y + ((float)score / float(q)*dirY)))*TM.GetDeltaTime();
	}

	velocity GetVelocity() {
		return vel;
	}

	int RandomVelocityDir() {
		int tmp = rand() % 2;
		if (tmp == 1) {
			return 1;
		}
		else return -1;
	}

	void RandomType() {
		int randValue = rand() % 3;
		switch (randValue)
		{
		case 0: type = SMALL; break;
		case 1: type = MEDIUM; break;
		case 2: type = LARGE; break;
		}
	}
};