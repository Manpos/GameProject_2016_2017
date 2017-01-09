#pragma once
#include <SDL.h>
#include "GameObject.hh"
#include <time.h>

enum EnemyType { SMALL, MEDIUM, LARGE, S_OVNI, L_OVNI };

class Enemy : public GameObject{
private:
	EnemyType type = MEDIUM;
	SDL_Rect area;
	float rotateSpeed = 0.5, rotateBase = 0;
	float rotValue;
	int rotateSide;
	int radi;
public:
	Enemy() {
		vel.x = 0;
		vel.y = 0;
		id = (SpriteID)(rand() % 8 + 2);
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

		switch (type)
		{
		case SMALL: 
			vel.x = (rand() % 3) + 5;
			vel.y = (rand() % 3) + 5;
			//radi = ;
			break;
		case MEDIUM:
			vel.x = (rand() % 3) + 1;
			vel.y = (rand() % 3) + 1;
			break;
		case LARGE:
			vel.x = (rand() % 2) + 1;
			vel.y = (rand() % 2) + 1;
			break;
		case S_OVNI:
			break;
		case L_OVNI:
			break;
		default:
			break;
		}
		std::cout << "PosX:  " << pos.x << "	pos.y:  " << pos.y << std::endl;
	}


	void Update() {
		CheckBorders(id);
		rotValue = rotateEnemy();
		move();
	}
	
	float RandomPos() {
		return (rand() % 600 + 10);
	}

	void Draw() {
		RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[id], rotateEnemy());
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


	// Dispara en funció del tipus, S_OVNI dispara al jugador. L_OVNI aleatoriament
};