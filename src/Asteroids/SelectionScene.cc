#include "SelectionScene.hh"
#include "SceneManager.hh"

#define EASY mode->first_node()
#define MEDIUM mode->next_sibling()->first_node()
#define HARD mode->next_sibling()->next_sibling()->first_node()

void SelectionScene::OnEntry() {

	easyT = RND.LPFont(path, 21, "Easy", 255, 255, 255);
	mediumT = RND.LPFont(path, 21, "Medium", 255, 255, 255);
	hardT = RND.LPFont(path, 21, "Hard", 255, 255, 255);

	transform.position(easyT.rect, 50, 50);
	transform.position(mediumT.rect, 50, 100);
	transform.position(hardT.rect, 50, 150);

	LoadXml();

	IM.Start();
}

void SelectionScene::OnExit() {
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
		for (auto it = gameModeArr.begin(); it != gameModeArr.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		// TODO code per canviar de menu
		easy = new GameScene(gameModeArr);
		SM.game = easy;
		SM.curr = GAME;
	}

	else if (IM.ButtonPress(mediumT.rect)) {
		gameModeArr.resize(0);
		mode = MEDIUM;
		FromXmlToVector(mode, gameModeArr);
		for (auto it = gameModeArr.begin(); it != gameModeArr.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		// TODO code per canviar de menu
		medium = new GameScene(gameModeArr);
		SM.game = medium;
		SM.curr = GAME;
	}

	else if (IM.ButtonPress(hardT.rect)) {
		gameModeArr.resize(0);
		mode = HARD;
		FromXmlToVector(mode, gameModeArr);
		for (auto it = gameModeArr.begin(); it != gameModeArr.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		// TODO code per canviar de menu
		hard = new GameScene(gameModeArr);
		SM.game = hard;
		SM.curr = GAME;
	}
	IM.ResetButton();
}

void SelectionScene::Draw() {
	RND.PrintText(easyT.rect, easyT.text);
	RND.PrintText(mediumT.rect, mediumT.text);
	RND.PrintText(hardT.rect, hardT.text);
	RND.CleanRenderer();
}