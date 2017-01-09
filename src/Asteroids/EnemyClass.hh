#pragma once
#include <SDL.h>
#include "GameObject.hh"
#include <time.h>

enum EnemyType { SMALL, MEDIUM, LARGE, S_OVNI, L_OVNI };

class Enemy : public GameObject{
private:
	EnemyType type;
	SDL_Rect area;
	float rotateSpeed = 0.5, rotateBase = 0;
	float rotValue;
	int rotateSide;
	int radi;
	float difSpeed;
public:
	Enemy(float difSpd) {
		vel.x = 0;
		vel.y = 0;
		id = (SpriteID)(rand() % 8 + 2);
		difSpeed = difSpd;
	} 
	Enemy(float x, float y, EnemyType ty) {
		pos.x = x;
		pos.y = y;
		type = ty;
		defineRotationSize();
	};

	void Start() {

		pos.x = RandomPos();
		pos.y = RandomPos();

		RandomType();

		switch (type)
		{
		case SMALL: 
			id = (SpriteID)(rand() % 2 + 4);
			vel.x = 1.5 * difSpeed;
			vel.y = 1.5 * difSpeed;
			break;
		case MEDIUM:
			id = (SpriteID)(rand() % 2 + 2);
			vel.x = (1)*difSpeed;
			vel.y = (1)*difSpeed;
			break;
		case LARGE:
			id = (SpriteID)(rand() % 3 + 6);
			vel.x = (0.5)*difSpeed;
			vel.y = (0.5)*difSpeed;
			break;
		case S_OVNI:
			break;
		case L_OVNI:
			break;
		default:
			break;
		}
		//std::cout << "PosX:  " << pos.x << "	pos.y:  " << pos.y << std::endl;
	}


	void Update() {
		CheckBorders(id);
		rotValue = rotateEnemy();
		move();

		ptPos.x = pos.x + (float)RND.spriteClips[id].w / 2.00;
		ptPos.y = pos.y + (float)RND.spriteClips[id].h / 2.00;

	}
	
	float RandomPos() {
		return (rand() % 600 + 10);
	}

	void Draw() {
		RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[id], rotValue);
	}

	float rotateEnemy() {
		if (rotateBase >= 360) {
			rotateBase = 0;
			return rotateBase;
		}
		else return (rotateBase += rotateSpeed);
	}

	void move() {
		pos.x += vel.x;
		pos.y += vel.y;
	}

	//void ColidePlayer(float plyX, float plyY, float plyW, float plyH) {
	//	if (pos.x)
	//}

	void defineRotationSize() {
		int temp = rand() % 10 + 1;
		if (temp < 5) {
			rotateSide = -1;
		}
		else rotateSide = 1;
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

	// Dispara en funció del tipus, S_OVNI dispara al jugador. L_OVNI aleatoriament
};