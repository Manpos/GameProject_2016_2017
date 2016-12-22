#pragma once
#define transform Transform::Instance()
struct Position{
	float x, y;
};

class Transform {
public:
	static Transform &Instance() {
		static Transform t;
		return t;
	}
	template <typename T>
	void position(T &object, int x, int y) {
		T* ch = &object;
		ch->x = x;
		ch->y = y;
	}
};