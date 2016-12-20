#pragma once
#include <SDL.h>


enum EnemyType { SMALL, MEDIUM, LARGE, S_OVNI, L_OVNI };

struct position {
	float x, y;
};
struct velocity {
	float x, y;
};

class Enemy {
private:
	position pos;
	velocity vel;
	EnemyType type;
	SDL_Rect area;
public:
	Enemy(float x, float y, EnemyType ty) {
		pos.x = x;
		pos.y = y;
		type = ty;
	};

	void Start() {

	}

	void Move() { // Com mes petit, mes velocitat
		pos.x += vel.x;
		pos.y += vel.y;
	};

	void Update() {

	}

	// Dispara en funció del tipus, S_OVNI dispara al jugador. L_OVNI aleatoriament
};