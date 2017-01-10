#pragma once
#include "Scene.hh"
#include <vector>
#include "EnemyClass.hh"
#include "TimeManager.hh"
#include "PlayerClass.hh"
#include "GameObject.hh"
#include "Bullet.hh"

#define L_SCORE 20
#define M_SCORE 50
#define S_SCORE 100

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
	Enemy* enem = nullptr;
	Player *ply = nullptr;
	int score, prevScore;

public:
	std::vector<Bullet> bulletVector;
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
	void DummyFunc() {};
	void GameUpdate();
	
	//SCORE
	TTF_Font *font;
	SDL_Texture *lifeIcon;
	RTexture res;
	
	int currEnemyNum;

	GameScene(std::vector<float> tmp) : difMode(tmp) {
		for (auto it = difMode.begin(); it != difMode.end(); ++it) {
			std::cout << *it << " ";
		}

		OnEntry();
	}

	int EnemySpawnNumber();

	void EnemySpawn(Enemy obj) {
		if (currEnemyNum <= 0) {
			if (isPlaying) {
				++level;
				for (int i = 0; i < EnemySpawnNumber(); ++i) {
					enemC.push_back(obj);
					enemC[i].OnEntry();
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

	void BulletColided() {
		for (auto i = enemC.begin(); i != enemC.end(); ++i) { // Iterate through the vector of enemies
			if (i->colidedByBullet) { // Checks if the enemy is hited
								
				if (i->type == SMALL) {
					enemC.erase(i);
					--currEnemyNum;
					score += S_SCORE;
					break;
				}
							
				else if (i->type == MEDIUM) {
					Enemy dividedEnemy(i->cir.x - rand() % 5, i->cir.y, SMALL, difMode[ENEMIES_INIT_SPD], i->GetVelocity().x, i->GetVelocity().y, &score);
					Enemy dividedEnemy2(i->cir.x + rand() % 5, i->cir.y, SMALL, difMode[ENEMIES_INIT_SPD], -i->GetVelocity().x, -i->GetVelocity().y, &score);
					enemC.erase(i);
					enemC.push_back(dividedEnemy);
					enemC.push_back(dividedEnemy2);
					++currEnemyNum;
					score += M_SCORE;
					break;
				}
				else if (i->type == LARGE) {
					Enemy dividedEnemy3(i->cir.x - rand() % 10 , i->cir.y, MEDIUM, difMode[ENEMIES_INIT_SPD], i->GetVelocity().x, i->GetVelocity().y, &score);
					Enemy dividedEnemy4(i->cir.x + rand() % 10, i->cir.y, MEDIUM,difMode[ENEMIES_INIT_SPD], -i->GetVelocity().x, -i->GetVelocity().y, &score);
					enemC.erase(i);
					enemC.push_back(dividedEnemy3);
					enemC.push_back(dividedEnemy4);
					++currEnemyNum;
					score += L_SCORE;
					break;
				}
				
			}
		}
	}
	int ReturnScore() {
		return score;
	}
};