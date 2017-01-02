#pragma once
#define transform Transform::Instance()
struct Position{
	float x, y;
};

enum WRPosition {DEFAULT, CENTERED, TOP_PADDING, BOTTOM};

class Transform {
public:
	static Transform &Instance() {
		static Transform t;
		return t;
	}
	template <typename T>
	void position(T &object, int x = 0, int y = 0, WRPosition pos = DEFAULT) {
		T* ch = &object;
		ch->x = x;
		ch->y = y;
		
		//Works with SDL_Rect
		switch (pos)
		{
		case CENTERED:
			ch->x = (AUX.w / 2) - (ch->w / 2) + x;
			ch->y = (AUX.h / 2) - (ch->h / 2) + y;
			break;
		case TOP_PADDING:
			ch->y = 20 + y;
			break;
		case BOTTOM:
			break;
		default:
			break;
		}
	}
};