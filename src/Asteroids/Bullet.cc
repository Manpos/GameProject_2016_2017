#include "Bullet.hh"
#include "Renderer.hh"
#include "TimeManager.hh"

Bullet::Bullet() {
	alive = false;
	x = 0;
	y = 0;
	xV = 0;
	yV = 0;
}

void Bullet::Update() {
	if (alive) {
		x -= xV * TM.GetDeltaTime();
		y -= yV * TM.GetDeltaTime();
	}
}

// velocity.x = sin(M_PI - test.transform.rotation / ((360 / (2 * M_PI)))) * 1;
// velocity.y = cos(M_PI - test.transform.rotation / ((360 / (2 * M_PI)))) * 1;

void Bullet::Shoot(float stX, float stY, float xSpee, float ySpee) {
	x = stX;
	y = stY;
	xV = xSpee;
	yV = ySpee;
	alive = true;
}

void Bullet::Draw() {
	if (alive) {
		RND.PrintText(x, y, spriteSheetText, &RND.spriteClips[BULLET]);
	}
}
