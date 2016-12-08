#pragma once

class GameScene {
public:
private:
	static GameScene& Instance() {
		static GameScene a;
		return a;
	}
};

