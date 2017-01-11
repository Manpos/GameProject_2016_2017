#pragma once
#include <SDL.h>
#include "GameObject.hh"
#include <time.h>

#define q 10000
enum EnemyType { SMALL, MEDIUM, LARGE, S_OVNI, L_OVNI };

class Enemy : public GameObject{
private:

	float rotateSpeed = 1.5, rotateBase = 0;
	float rotValue;
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
		//std::cout << "Dir X: " << vel.x << "		 Dir Y: " << vel.y << std::endl;

	}
	
	Position RandomPos() {
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

	float rotateEnemy() {
		if (rotateBase >= 360) {
			rotateBase = 0;
			return rotateBase;
		}
		else return (rotateBase += rotateSpeed);
	}

	void move(int score) {		
		pos.x += ((vel.x + ((float)score / float(q)*dirX)));
		pos.y += ((vel.y + ((float)score / float(q)*dirY)));
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