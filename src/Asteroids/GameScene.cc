#include "GameScene.hh"
#include "SceneManager.hh"

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
	currEnemyNum = 0;
	isPlaying = true;
	level = 0;
	score = 0;
	prevScore = -1;
}

void GameScene::OnExit() {
	AUX.paused = false;
	delete this;
}

void GameScene::Update() {
	IM.Update();
	Score();

	if (AUX.paused) {
		if (IM.ButtonPress(resume.rect)) AUX.paused = false;
		else if (IM.ButtonPress(mainMenu.rect)) { SM.menu = new MenuScene; SM.curr = MENU; }
		else if (IM.ButtonPress(exit.rect)) AUX.gameRunning = false;
	}

	else
	{
		ply.Update();
		EnemySpawn();
		EnemiesUpdate();
	}


}

void GameScene::Draw() {
	EnemiesDraw();
	ply.Draw();

	if (AUX.paused) {
		RND.PrintText(pauseL.rect, pauseL.text);
		RND.PrintText(resume.rect, resume.text);		
		RND.PrintText(mainMenu.rect, mainMenu.text);
		RND.PrintText(exit.rect, exit.text);
	}

	RND.CleanRenderer();
}