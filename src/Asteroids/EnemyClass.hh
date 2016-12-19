#pragma once

enum EnemyType { SMALL, MEDIUM, LARGE, S_OVNI, L_OVNI };
class Enemy {
private:
	struct position{
		float x, y;
	};
	EnemyType type;
	SDL_Rect area;
public:
	Enemy(float x, float y, EnemyType ty);
};