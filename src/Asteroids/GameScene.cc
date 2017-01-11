#include "GameScene.hh"
#include "SceneManager.hh"
#include "InputManager.hh"

#define MAX_BULLETS 10

//Attributes declaration
void GameScene::OnEntry() {
	RND.SetClips();
	pauseL = RND.CreateSolid(0, 0, 0, 200);
	font = RND.LoadFont(path, 20);

	resume = RND.PrepareFont(font, "RESUME", 255, 255, 255);
	transform.position(resume.rect, 0, -50, CENTERED);

	mainMenu = RND.PrepareFont(font, "MAIN MENU", 255, 255, 255);
	transform.position(mainMenu.rect, 0, 0, CENTERED);

	exit = RND.PrepareFont(font, "EXIT", 255, 255, 255);
	transform.position(exit.rect, 0, 50, CENTERED);

	lifeIcon = RND.SurfToText(RND.LoadImage("../../res/SpriteSheet.png"));
	
	isPlaying = true;
	end = false;
	AUX.inGame = true;

	level = 0;
	score = 0;
	prevScore = -1;
	currEnemyNum = 0;
	
	ply = new Player(difMode[LIFE]);
	enem = new Enemy(difMode[ENEMIES_INIT_SPD], &score);
	Bullet bulletTest;
	for (int i = 0; i < MAX_BULLETS; ++i) {
		bulletVector.push_back(bulletTest);
	}
	
}

//Called when changing scene
void GameScene::OnExit() {
	//Delete enem and ply
	delete enem;
	delete ply;
	//Reset 
	AUX.paused = false;
	AUX.inGame = false;
	delete this;
}

void GameScene::Update() {
	GameUpdate();
}

void GameScene::GameUpdate() {
	IM.Update();

	if (!ply->alive) { end = true; }

	if (AUX.paused) {
		if (IM.ButtonPress(resume.rect)) AUX.paused = false;
		else if (IM.ButtonPress(mainMenu.rect)) { SM.menu = new MenuScene; SM.curr = MENU; }
		else if (IM.ButtonPress(exit.rect)) AUX.gameRunning = false;
	}

	else {

		ply->Update();
		EnemySpawn(*enem);
		EnemiesUpdate();
		BulletColided();
		PlayerInvulnerability();
		BulletsUpdate();
		
	}

	
	if (end) {
		if (SM.rank == nullptr) {
			SM.rank = new RankScene;
		}

		SM.curr = RANK;
	}

	IM.ResetButton();
}

void GameScene::Draw() {
	EnemiesDraw();
	Score();
	ply->Draw();
	DrawLifes(lifeIcon, AUX.w-20, 20);
	BulletsDraw();

	if (AUX.paused) {
		RND.PrintText(pauseL.rect, pauseL.text);
		RND.PrintText(resume.rect, resume.text);		
		RND.PrintText(mainMenu.rect, mainMenu.text);
		RND.PrintText(exit.rect, exit.text);
	}

	RND.CleanRenderer();
}

int GameScene::EnemySpawnNumber() {
	int totalEnemies;
	totalEnemies = difMode[INI_ENEMIES] + difMode[INCR_ENEMIES_NUM] * level;
	return totalEnemies;
}

void GameScene::EnemySpawn(Enemy obj) {
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

void GameScene::EnemiesUpdate() {
	for (int i = 0; i < currEnemyNum; ++i) {
		enemC[i].Update();
	}
}

void GameScene::EnemiesDraw() {
	for (int i = 0; i < currEnemyNum; ++i) {
		enemC[i].Draw();
	}
}

void GameScene::BulletsUpdate(){
	if (ply->Shoot()) {
		for (auto i = bulletVector.begin(); i != bulletVector.end(); ++i) {
			if (i->isAlive() == false) {
				i->Shoot(ply->cir.x, ply->cir.y, ply->angle_deg);
				break;
			}

		}
	}

	for (auto i = bulletVector.begin(); i != bulletVector.end(); ++i) {
		i->Update();
		if (i->isAlive()) {
			i->CheckColision(enemC);
		}
	}
}

void GameScene::BulletsDraw() {
	for (auto i = bulletVector.begin(); i != bulletVector.end(); ++i) {
		i->Draw();
	}
}

void GameScene::PlayerInvulnerability() {
	if (!ply->invulnerable) {
		ply->CheckEnemiesColision(enemC);
	}
}


void GameScene::Score() {
	if (prevScore != score) {
		prevScore = score;
		sc = "SCORE: " + (std::to_string(score));
		const char* conv = sc.c_str();
		res = RND.PrepareFont(font, conv, 255, 255, 255);
		transform.position(res.rect, 15, 15);
	}
	RND.PrintText(res.rect, res.text);
}

void GameScene::DrawLifes(SDL_Texture *lifeIc, int x, int y) {
	int initalX = x - RND.spriteClips[PLAYER].w, initialY = y;
	for (int i = 0; i < ply->life; ++i) {
		RND.PrintText(initalX - (RND.spriteClips[PLAYER].w * i), initialY, lifeIc, &RND.spriteClips[PLAYER]);
	}
}

void GameScene::BulletColided() {
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
				Enemy dividedEnemy3(i->cir.x - rand() % 10, i->cir.y, MEDIUM, difMode[ENEMIES_INIT_SPD], i->GetVelocity().x, i->GetVelocity().y, &score);
				Enemy dividedEnemy4(i->cir.x + rand() % 10, i->cir.y, MEDIUM, difMode[ENEMIES_INIT_SPD], -i->GetVelocity().x, -i->GetVelocity().y, &score);
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

int GameScene::ReturnScore() {
	return score;
}