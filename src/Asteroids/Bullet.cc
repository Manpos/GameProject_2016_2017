#include "Bullet.hh"
#include "Renderer.hh"
#include "TimeManager.hh"
#include <math.h>

Bullet::Bullet() {
	alive = false;
}

void Bullet::Update() {
	if (alive) {
		pos.x += vel.x * TM.GetDeltaTime();
		pos.y += vel.y * TM.GetDeltaTime();
		cir.x = pos.x + RND.spriteClips[BULLET].w / 2;
		cir.y = pos.y + RND.spriteClips[BULLET].h / 2;
	}
	CheckBulletBorders();
}

// velocity.x = sin(M_PI - test.transform.rotation / ((360 / (2 * M_PI)))) * 1;
// velocity.y = cos(M_PI - test.transform.rotation / ((360 / (2 * M_PI)))) * 1;

void Bullet::Shoot(float stX, float stY, float angle) {
	pos.x = stX;
	pos.y = stY;
	vel.y = sin(AUX.degreesToRadians(angle)) * 500;
	vel.x = cos(AUX.degreesToRadians(angle)) * 500;
	alive = true;
	cir.r = RND.spriteClips[BULLET].w / 2;
}

void Bullet::Draw() {
	if (alive) {
		RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[BULLET]);
	}
}

bool Bullet::isAlive() {
	return alive;
}

void Bullet::CheckBulletBorders() {
		if (pos.x + RND.spriteClips[BULLET].w < 0) {
			alive = false;
		}

		else if (pos.y + RND.spriteClips[id].h < 0) {
			alive = false;
		}

		else if (pos.x > AUX.w) {
			alive = false;
		}

		else if (pos.y > AUX.h) {
			alive = false;
		}
}

