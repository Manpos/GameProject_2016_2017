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
	bool isPlaying;

	RTexture pauseL;

	const char *path = "../../res/ariblk.ttf";
	

	SDL_Rect spriteSheetTest = {50,50,50,50};

	EnemySpawnPos spawn;
	Enemy* enemC;
	Player ply;

	int once = 0;

public:
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
	
	//SCORE
	TTF_Font *font;
	std::string sc;
	RTexture res;
	int score, prevScore;

	int currEnemyNum;

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

	void EnemySpawn() {
		if (currEnemyNum <= 0) {
			delete[] enemC;
			if (isPlaying) {
				++level;
				enemC = new Enemy[EnemySpawnNumber()];
				for (int i = 0; i < EnemySpawnNumber(); ++i) {
					enemC[i].Start();
					currEnemyNum++;
				}
			}
		}
	}

	void EnemiesUpdate() {
		for (int i = 0; i < currEnemyNum; ++i) {
			enemC[i].Update();
		}
	}

	void EnemiesDraw() {
		for (int i = 0; i < currEnemyNum; ++i) {
			enemC[i].Draw();
		}
	}

	void Score() {
		if (prevScore != score) {
			prevScore = score;
			sc = "SCORE: " + (std::to_string(score));
			const char* conv = sc.c_str();
			res = RND.PrintFont(font, conv, 255, 255, 255);
			transform.position(res.rect, 15, 15);
		}
		RND.PrintText(res.rect, res.text);
	}
};