#pragma once
#include <SDL.h>
#include <vector>
#include "PlayerClass.hh"
#include "Renderer.hh"

class Bullet : public GameObject {

public:
	Bullet();
	void Update();
	void Shoot(float startX, float startY, float xSpeed, float ySpeed);
	void Draw();

private:

	bool alive;
	float x, y;
	float xV, yV;

};