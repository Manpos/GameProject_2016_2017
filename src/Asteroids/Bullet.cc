#include "Bullet.hh"

Bullet::Bullet() {												// Declaration of the constructor
	alive = false;
}

void Bullet::Update() {											// Declaration of the update
	if (alive) {
		pos.x += vel.x;
		pos.y += vel.y;
		cir.x = pos.x + RND.spriteClips[BULLET].w / 2;			// cir.x and cir.y define the center
		cir.y = pos.y + RND.spriteClips[BULLET].h / 2;			// of the circle used to detect collisions
	}
	CheckBulletBorders();
}


void Bullet::Shoot(float stX, float stY, float angle) {			// This method gives value to a bullet and makes it visible
	pos.x = stX;
	pos.y = stY;
	vel.y = sin(AUX.degreesToRadians(angle)) * 7;
	vel.x = cos(AUX.degreesToRadians(angle)) * 7;
	alive = true;
	cir.r = RND.spriteClips[BULLET].w / 2;
}

void Bullet::Draw() {											// Draws the bullet sprite when alive == true
	if (alive) {
		RND.PrintText(pos.x, pos.y, spriteSheetText, &RND.spriteClips[BULLET]);
	}
}

bool Bullet::isAlive() {										// Return the value of alive if it's request externally
	return alive;
}

void Bullet::CheckBulletBorders() {								//Checks if the bullet arrives at the border of the window and makes alive == false
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

