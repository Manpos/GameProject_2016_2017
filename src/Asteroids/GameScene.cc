#include "GameScene.hh"

void GameScene::OnEntry() {
	RND.SetClips();
	pauseL = RND.CreateSolid(90, 70, 45, 255);
	font = RND.LoadFont(path, 20);
	currEnemyNum = 0;
	isPlaying = true;
	level = 0;
	score = 0;
	prevScore = -1;
}

void GameScene::OnExit() {

}

void GameScene::Update() {
	IM.Update();
	Score();
	if (AUX.paused) {

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
	}

	RND.CleanRenderer();
}