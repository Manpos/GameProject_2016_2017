#pragma once
#include <SDL.h>
#include <vector>
#include "PlayerClass.hh"
#include "Renderer.hh"
#include <math.h>

class Bullet : public GameObject {

public:
	Bullet();
	void Update();
	void Shoot(float startX, float startY, float angle);
	void Draw();
	bool isAlive();
	void CheckBulletBorders();
	void MakeUnitaryVector(float coordX, float coordY);

	struct unitaryVector
	{
		float x, y;
	};

private:

	bool alive;
	float x, y;
	float xV, yV;

};