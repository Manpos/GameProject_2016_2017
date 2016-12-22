#pragma once
#include "Scene.hh"
#include <vector>
#include "EnemyClass.hh"
#include "TimeManager.hh"
#include "PlayerClass.hh"
#include "GameObject.hh"

class GameScene : public Scene {

	struct EnemySpawnPos {
		float x, y;
	};

	enum{LIFE, INI_ENEMIES, INCR_ENEMIES_NUM, ENEMIES_INIT_SPD};

private:
	std::vector<Enemy> enemyVector;
	std::vector<float> difMode;
	int level;
	int currEnemyNum;

	SDL_Rect spriteSheetTest = {50,50,50,50};

	EnemySpawnPos spawn;

	Player ply;

	int once = 0;

public:
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();

	GameScene(std::vector<float> tmp) : difMode(tmp) {
		for (auto it = difMode.begin(); it != difMode.end(); ++it) {
			std::cout << *it << " ";
		}
		OnEntry();
	}

	int EnemySpawnNumber() {
		int totalEnemies;
		totalEnemies = difMode[INI_ENEMIES] + difMode[INCR_ENEMIES_NUM]*level;
		return totalEnemies;
	}
};