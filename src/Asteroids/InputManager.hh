#pragma once
#include <queue>
#include <SDL.h>

#define IM InputManager::Instance()



class InputManager {
private:


public:
	inline static InputManager& Instance() {
		static InputManager a;
		return a;
	}
};