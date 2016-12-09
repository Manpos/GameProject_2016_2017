#pragma once
#include <unordered_map>
#include "Scene.hh"

enum SceneType {MENU, GAME, RANK};

class SceneManager {
private:
	std::unordered_map<SceneType, Scene> scMap;
public:
	static SceneManager& Instance() {
		static SceneManager a;
		return a;
	}
};

