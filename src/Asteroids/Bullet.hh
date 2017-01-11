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

	template <typename T>
	void CheckColision(std::vector<T> &enemies) {
		float totalRadius, totalRadiusSquared, distancePoints;
		bool colision = false;
		for (auto i = enemies.begin(); i != enemies.end(); ++i) {
			totalRadius = cir.r + i->cir.r;
			totalRadiusSquared = totalRadius * totalRadius;
			distancePoints = pow((i->cir.x - cir.x), 2) + pow((i->cir.y - cir.y), 2);
			if (distancePoints < totalRadiusSquared) {
				i->colidedByBullet = true;
				alive = false;
			}
		}
	}

private:

	bool alive;

};