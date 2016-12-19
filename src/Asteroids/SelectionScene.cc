#include "SelectionScene.hh"
#include "SceneManager.hh"

void SelectionScene::OnEntry() {

	font = TTF_OpenFont("../../res/ariblk.ttf", 21);
	firstBoxMs = TTF_RenderText_Solid(font, "Easy", textColor);
	secondBoxMs = TTF_RenderText_Solid(font, "Medium", textColor);
	thirdBoxMs = TTF_RenderText_Solid(font, "Hard", textColor);

	msgRect = { 45, 45, firstBoxMs->w, secondBoxMs->h };
	firstBox = RND.SurfToText(firstBoxMs);

	msgRect2 = { 45,85, secondBoxMs->w, secondBoxMs->h };
	secondBox = RND.SurfToText(secondBoxMs);

	msgRect3 = { 45,125, thirdBoxMs->w, thirdBoxMs->h };
	thirdBox = RND.SurfToText(thirdBoxMs);

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

	if (IM.ButtonPress(msgRect)) { 
		gameModeArr.resize(0);
		mode = mode->first_node();
		FromXmlToVector(mode, gameModeArr);
		for (auto it = gameModeArr.begin(); it != gameModeArr.end(); ++it) {
			std::cout << *it << std::endl;
		}
		// TODO code per canviar de menu
		easy = new GameScene(gameModeArr[0], gameModeArr[1], gameModeArr[2], gameModeArr[3]);
		SM.game = easy;
		SM.curr = GAME;
	}

	else if (IM.ButtonPress(msgRect2)) {
		gameModeArr.resize(0);
		std::cout << mode->next_sibling()->first_attribute()->value() << std::endl;
		mode = mode->next_sibling()->first_node();
		FromXmlToVector(mode, gameModeArr);
		for (auto it = gameModeArr.begin(); it != gameModeArr.end(); ++it) {
			std::cout << *it << std::endl;
		}
		// TODO code per canviar de menu
		medium = new GameScene(gameModeArr[0], gameModeArr[1], gameModeArr[2], gameModeArr[3]);
		SM.game = medium;
		SM.curr = GAME;
	}

	else if (IM.ButtonPress(msgRect3)) {
		gameModeArr.resize(0);
		std::cout << mode->next_sibling()->next_sibling()->first_attribute()->value() << std::endl;
		mode = mode->next_sibling()->next_sibling()->first_node();
		FromXmlToVector(mode, gameModeArr);
		for (auto it = gameModeArr.begin(); it != gameModeArr.end(); ++it) {
			std::cout << *it << std::endl;
		}
		// TODO code per canviar de menu
		hard = new GameScene(gameModeArr[0], gameModeArr[1], gameModeArr[2], gameModeArr[3]);
		SM.game = hard;
		SM.curr = GAME;
	}
	IM.ResetButton();
}

void SelectionScene::Draw() {
	RND.PrintText(msgRect, firstBox);
	RND.PrintText(msgRect2, secondBox);
	RND.PrintText(msgRect3, thirdBox);
	RND.CleanRenderer();
}