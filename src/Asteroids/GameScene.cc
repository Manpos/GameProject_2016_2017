#include "GameScene.hh"

void GameScene::OnEntry() {
	if (once == 0) {
		std::cout << lifes << " " << initEnemies << " " << incremEnemiesNum << " " << enemInitialSpeed << std::endl;
		once++;
		ply.SetClipsValue();
	}
}

void GameScene::OnExit() {

}

void GameScene::Update() {
	IM.Update();
	/*for (i = 0; i < EnemySpawnNumber(); ++i) {

	}*/
}

void GameScene::Draw() {
	ply.Draw();
	RND.CleanRenderer();
}