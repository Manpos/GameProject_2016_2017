#include "SelectionScene.hh"
#include "SceneManager.hh"

#define EASY mode->first_node()
#define MEDIUM mode->next_sibling()->first_node()
#define HARD mode->next_sibling()->next_sibling()->first_node()

void SelectionScene::OnEntry() {

	selectDif = RND.LPFont(path, 40, "SELECT DIFFICULTY", 255, 255, 255);
	transform.position(selectDif.rect, 0, -AUX.h / 4, CENTERED);

	easyT = RND.LPFont(path, 21, "EASY", 255, 255, 255);
	transform.position(easyT.rect, 0, -50, CENTERED);

	mediumT = RND.LPFont(path, 21, "MEDIUM", 255, 255, 255);
	transform.position(mediumT.rect, 0, 0, CENTERED);

	hardT = RND.LPFont(path, 21, "HARD", 255, 255, 255);
	transform.position(hardT.rect, 0, 50, CENTERED);

	LoadXml();

	IM.Start();
}

void SelectionScene::OnExit() {
	delete this;
}

void SelectionScene::Update() {
	IM.Update();
	
	//XML parsing
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	//XML Pointer values
	root = doc.first_node();
	mode = root->first_node("dif");

	if (IM.ButtonPress(easyT.rect)) { 
		gameModeArr.resize(0);
		mode = EASY;
		FromXmlToVector(mode, gameModeArr);
		easy = new GameScene(gameModeArr);
		SM.game = easy;
		SM.currDif = D_EASY;
		SM.curr = GAME;
	}

	else if (IM.ButtonPress(mediumT.rect)) {
		gameModeArr.resize(0);
		mode = MEDIUM;
		FromXmlToVector(mode, gameModeArr);
		medium = new GameScene(gameModeArr);
		SM.game = medium;
		SM.currDif = D_MEDIUM;
		SM.curr = GAME;
	}

	else if (IM.ButtonPress(hardT.rect)) {
		gameModeArr.resize(0);
		mode = HARD;
		FromXmlToVector(mode, gameModeArr);
		hard = new GameScene(gameModeArr);
		SM.game = hard;
		SM.currDif = D_HARD;
		SM.curr = GAME;
	}
	IM.ResetButton();
}

void SelectionScene::Draw() {
	RND.PrintText(selectDif.rect, selectDif.text);
	RND.PrintText(easyT.rect, easyT.text);
	RND.PrintText(mediumT.rect, mediumT.text);
	RND.PrintText(hardT.rect, hardT.text);
	RND.CleanRenderer();
}