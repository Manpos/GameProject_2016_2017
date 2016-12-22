#pragma once
#include <SDL.h>
//Rotation function BETA
//Not finished
class Colision {
private:
	struct Rect {
		SDL_Point p1, p2, p3, p4;
	};
public:
	Rect ret;
	void GetRect(SDL_Rect *r) {
		ret.p1.x = r->x;
		ret.p1.y = r->y;
		ret.p2.x = ret.p1.x + r->w;
		ret.p2.y = ret.p1.y;
		ret.p3.x = ret.p1.x;
		ret.p3.y = ret.p1.y + r->h;
		ret.p4.x = ret.p1.x + r->w;
		ret.p4.y = ret.p1.y + r->h;
	}
};