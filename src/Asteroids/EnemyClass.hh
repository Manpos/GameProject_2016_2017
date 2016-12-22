#pragma once
#include <SDL.h>
#include "GameObject.hh"
#include <time.h>


enum EnemyType { SMALL, MEDIUM, LARGE, S_OVNI, L_OVNI };

struct position {
	float x = 100, y = 100;
};
struct velocity {
	float x = 0.02, y = 0.01;
};

class Enemy : public GameObject{
private:
	position pos;
	velocity vel;
	EnemyType type = MEDIUM;
	SDL_Rect area;
	float rotateSpeed = 0.03, rotateBase = 0;
	int rotateSide;
public:
	Enemy() = default;
	Enemy(float x, float y, EnemyType ty) {
		pos.x = x;
		pos.y = y;
		type = ty;
		defineRotationSize();
	};

	void Start() {
		/*switch (type)
		{
		case SMALL: 
			vel.x = (rand() * 9 + 5) / 10;
			vel.y = (rand() * 9 + 5) / 10;
			break;
		case MEDIUM:
			vel.x = (rand() * 4 + 1) / 10;
			vel.y = (rand() * 4 + 1) / 10;
			break;
		case LARGE:
			vel.x = (rand() * 4 + 1) / 10;
			vel.y = (rand() * 4 + 1) / 10;
			break;
		case S_OVNI:
			break;
		case L_OVNI:
			break;
		default:
			break;
		}*/
	}

	void Move() { // Com mes petit, mes velocitat
		pos.x += vel.x;
		pos.y += vel.y;
	};

	void Update() {
		move();
	}
	
	void Draw() {
		RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[AST_MED_1], rotateEnemy());
	}

	float rotateEnemy() {
		if (rotateBase >= 360) {
			rotateBase = 0;
			return rotateBase;
		}
		else return (rotateBase += rotateSpeed)*rotateSide;
	}

	void move() {
		pos.x += vel.x;
		pos.y += vel.y;
	}



	void defineRotationSize() {
		int temp = rand() % 10 + 1;
		if (temp < 5) {
			rotateSide = -1;
		}
		else rotateSide = 1;
	}


	// Dispara en funció del tipus, S_OVNI dispara al jugador. L_OVNI aleatoriament
};