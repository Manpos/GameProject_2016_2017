#pragma once

enum SceneType {MENU, GAME, RANK};
class SceneManager {
private:
	static SceneManager& Instance() {
		static SceneManager a;
		return a;
	}
public:
};

