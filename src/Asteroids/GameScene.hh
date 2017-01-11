#pragma once
#include "Scene.hh"
#include <vector>
#include "EnemyClass.hh"
#include "TimeManager.hh"
#include "PlayerClass.hh"
#include "GameObject.hh"
#include "Bullet.hh"

//Score given by each enemy
#define L_SCORE 20
#define M_SCORE 50
#define S_SCORE 100

class GameScene : public Scene {

	enum{LIFE, INI_ENEMIES, INCR_ENEMIES_NUM, ENEMIES_INIT_SPD};

private:
	//Difficulty based data vector
	std::vector<float> difMode;

	//Control variables
	int level;
	bool isPlaying;
	bool end;

	//Pause menu buttons textures
	RTexture  pauseL, exit, mainMenu, resume;

	//Font path
	const char *path = "../../res/ariblk.ttf";
	
	std::string sc;
	std::vector<Enemy>enemC;
	Enemy* enem = nullptr;
	Player *ply = nullptr;
	int score, prevScore;

public:

	//Vector to store a limited amount of bullets
	std::vector<Bullet> bulletVector;
	
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
	void DummyFunc() {};
	void GameUpdate();
	
	//Display Score variables
	TTF_Font *font;
	SDL_Texture *lifeIcon;
	RTexture res;
	
	//Current enemies in scene
	int currEnemyNum;

	//Methods definition
	int EnemySpawnNumber();
	void EnemySpawn(Enemy obj);
	void EnemiesUpdate();
	void EnemiesDraw();
	void BulletsUpdate();
	void BulletsDraw();
	void PlayerInvulnerability();
	void Score();
	void DrawLifes(SDL_Texture *lifeIc, int x, int y);
	void BulletColided();
	int ReturnScore();

	GameScene(std::vector<float> tmp) : difMode(tmp) {
		OnEntry();
	}
};