#include "GameScene.hh"
#include "SceneManager.hh"
#include "InputManager.hh"

#define MAX_BULLETS 10

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

	currEnemyNum = 0;
	isPlaying = true;
	end = false;
	level = 0;
	score = 0;
	prevScore = -1;
	Bullet bulletTest;
	AUX.inGame = true;
	ply = new Player(difMode[LIFE]);
	enem = new Enemy(difMode[ENEMIES_INIT_SPD]);
	for (int i = 0; i < MAX_BULLETS; ++i) {
		bulletVector.push_back(bulletTest);
	}
	
}

void GameScene::OnExit() {
	delete enem;
	delete ply;
	AUX.paused = false;
	AUX.inGame = false;
	delete this;
}

void GameScene::Update() {
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
		
		if (ply->Shoot()) {
			for (auto i = bulletVector.begin(); i != bulletVector.end(); ++i) {
				if (i->isAlive() == false) {
					i->Shoot(ply->ptPos.x, ply->ptPos.y, ply->angle_deg);
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

	
	if (end) {
		SM.rank = new RankScene;
		SM.curr = RANK;
	}

	IM.ResetButton();
}

void GameScene::Draw() {
	EnemiesDraw();
	Score();
	ply->Draw();
	DrawLifes(lifeIcon, AUX.w-20, 20);
	for (auto i = bulletVector.begin(); i != bulletVector.end(); ++i) {
		i->Draw();
	}

	if (AUX.paused) {
		RND.PrintText(pauseL.rect, pauseL.text);
		RND.PrintText(resume.rect, resume.text);		
		RND.PrintText(mainMenu.rect, mainMenu.text);
		RND.PrintText(exit.rect, exit.text);
	}

	RND.CleanRenderer();
}