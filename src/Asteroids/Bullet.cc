#include "Bullet.hh"

Bullet::Bullet() {
	alive = false;
}

void Bullet::Update() {
	if (alive) {
		pos.x += vel.x;
		pos.y += vel.y;
		cir.x = pos.x + RND.spriteClips[BULLET].w / 2;
		cir.y = pos.y + RND.spriteClips[BULLET].h / 2;
	}
	CheckBulletBorders();
}


void Bullet::Shoot(float stX, float stY, float angle) {
	pos.x = stX;
	pos.y = stY;
	vel.y = sin(AUX.degreesToRadians(angle)) * 7;
	vel.x = cos(AUX.degreesToRadians(angle)) * 7;
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

