#include "GameScene.hh"

void GameScene::OnEntry() {
	RND.SetClips();
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
	ply.Update();
	EnemySpawn();
	EnemiesUpdate();
	Score();
}

void GameScene::Draw() {
	EnemiesDraw();
	ply.Draw();
	RND.CleanRenderer();
}