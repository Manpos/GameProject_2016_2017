#include "GameScene.hh"

void GameScene::OnEntry() {
	RND.SetClips();

}

void GameScene::OnExit() {

}

void GameScene::Update() {
	IM.Update();
	ply.Update();

	/*for (i = 0; i < EnemySpawnNumber(); ++i) {
	}*/
}

void GameScene::Draw() {
	ply.Draw();
	RND.CleanRenderer();
}