#pragma once
#define transform Transform::Instance()

// Position struct with coordinates x and y
struct Position{ 
	float x, y;
};

enum WRPosition {DEFAULT, CENTERED, TOP_PADDING, BOTTOM};

class Transform {
public:
	static Transform &Instance() {												// Singleton declaration
		static Transform t;
		return t;
	}
	template <typename T>
	void position(T &object, int x = 0, int y = 0, WRPosition pos = DEFAULT) {	// Function to replace a SDL_Rect to a certain position pased by parameter
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