#pragma once
#include "Scene.hh"
#include <vector>
#include "EnemyClass.hh"
#include "TimeManager.hh"

class GameScene : public Scene {

	struct EnemySpawnPos {
		float x, y;
	};

private:
	std::vector<Enemy> enemyVector;
	int lifes, initEnemies, incremEnemiesNum;
	float enemInitialSpeed;
	int level;

	EnemySpawnPos spawn;
	SDL_Rect spriteClips[11];

	int once = 0;

public:
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();

	GameScene(int lif, int iniEnem, int incEnem, float enemIniSpd ) 
		: lifes(lif), initEnemies(iniEnem), incremEnemiesNum(incEnem), enemInitialSpeed(enemIniSpd){}

	int EnemySpawnNumber() {
		int totalEnemies;
		totalEnemies = initEnemies + incremEnemiesNum*level;
		return totalEnemies;
	}

};