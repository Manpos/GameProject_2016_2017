#pragma once
#include <queue>

#define IM InputManager::Instance()

class InputManager {
private:
	static InputManager& Instance() {
		static InputManager a;
		return a;
	}

public:
};