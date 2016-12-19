#pragma once
#include "Scene.hh"

class GameScene : public Scene {
private:
	int lifes, initEnemies, incremEnemiesNum, enemInitialSpeed;
public:
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
	GameScene(int lif, int iniEnem, int incEnem, float enemIniSpd ) 
		: lifes(lif), initEnemies(iniEnem), incremEnemiesNum(incEnem), enemInitialSpeed(enemIniSpd){}
};