#pragma once
#include "Scene.hh"
#include <vector>
#include "EnemyClass.hh"
#include "TimeManager.hh"
#include "PlayerClass.hh"
#include "GameObject.hh"
#include "Bullet.hh"

class GameScene : public Scene {

	struct EnemySpawnPos {
		float x, y;
	};

	enum{LIFE, INI_ENEMIES, INCR_ENEMIES_NUM, ENEMIES_INIT_SPD};

private:
	std::vector<float> difMode;
	int level;
	bool isPlaying;
	bool end;

	RTexture  pauseL, exit, mainMenu, resume;

	const char *path = "../../res/ariblk.ttf";
	

	SDL_Rect spriteSheetTest = {50,50,50,50};
	EnemySpawnPos spawn;
	std::string sc;
	std::vector<Enemy>enemC;
	Enemy* enem;
	Player *ply;

public:
	std::vector<Bullet> bulletVector;
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
	
	//SCORE
	TTF_Font *font;
	SDL_Texture *lifeIcon;
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

	void EnemySpawn(Enemy obj) {
		if (currEnemyNum <= 0) {
			if (isPlaying) {
				++level;
				for (int i = 0; i < EnemySpawnNumber(); ++i) {
					enemC.push_back(obj);
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
			res = RND.PrepareFont(font, conv, 255, 255, 255);
			transform.position(res.rect, 15, 15);
		}
		RND.PrintText(res.rect, res.text);
	}

	void DrawLifes(SDL_Texture *lifeIc, int x, int y){
		int initalX = x - RND.spriteClips[PLAYER].w, initialY = y;
		for (int i = 0; i < ply->life; ++i) {
			RND.PrintText(initalX - (RND.spriteClips[PLAYER].w * i) , initialY, lifeIc, &RND.spriteClips[PLAYER]);
		}
	}
};