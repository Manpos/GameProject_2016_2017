#include <iostream>
#include "MenuScene.hh"
#include "SceneManager.hh"
#include "transform.hh"

//Content of the class MenuScene.hh
void MenuScene::OnEntry() {

	////Font load and positioning
	start = RND.LPFont(path, 24, "START", 255, 255, 255);
	transform.position(start.rect, 0, -50, CENTERED);

	rank = RND.LPFont(path, 24, "RANK", 255, 255, 255);
	transform.position(rank.rect, 0, 0, CENTERED);

	exit = RND.LPFont(path, 24, "EXIT", 255, 255, 255);
	transform.position(exit.rect, 0, 50, CENTERED);

	easy = RND.LPFont(path, 24, "EASY", 255, 255, 255);
	transform.position(easy.rect, 0, -50, CENTERED);

	medium = RND.LPFont(path, 24, "MEDIUM", 255, 255, 255);
	transform.position(medium.rect, 0, 0, CENTERED);

	hard = RND.LPFont(path, 24, "HARD", 255, 255, 255);
	transform.position(hard.rect, 0, 50, CENTERED);

	IM.Start();								//Call to the inicialization of the elements in InputManager::Start()
}

void MenuScene::OnExit() {
	delete this;
}

void MenuScene::Update() {
	IM.Update();							//Call to the update of the input manager

	if (rankSelection) {
		if (IM.ButtonPress(easy.rect)) {
			SM.currDif = D_EASY;
			SM.rank = new RankScene;
			SM.curr = RANK;
		}
		else if (IM.ButtonPress(medium.rect)) {			
			SM.currDif = D_MEDIUM;
			SM.rank = new RankScene;
			SM.curr = RANK;
		}
		else if (IM.ButtonPress(hard.rect)) {
			SM.currDif = D_HARD;
			SM.rank = new RankScene;
			SM.curr = RANK;
		}
		IM.ResetButton();
	}
	else {
		//Conditions to determinate the zone where the input of the user should make effect
		if (IM.ButtonPress(start.rect)) {
			std::cout << "HOLOS" << std::endl;

			//Change the condition of the main
			SM.selection = new SelectionScene;
			SM.curr = SELECTION;


		}

		else if (IM.ButtonPress(exit.rect)) {
			std::cout << "ADEU" << std::endl;
			AUX.gameRunning = false;				//This ends the main loop and ends the program
		}

		else if (IM.ButtonPress(rank.rect)) {
			rankSelection = true;
		}
		IM.ResetButton();
	}
	

}

void MenuScene::Draw() {
	//The textures are drown and the Renderer is cleared
	if (rankSelection) {
		RND.PrintText(easy.rect, easy.text);
		RND.PrintText(medium.rect, medium.text);
		RND.PrintText(hard.rect, hard.text);
	}
	else {
		RND.PrintText(start.rect, start.text);
		RND.PrintText(exit.rect, exit.text);
		RND.PrintText(rank.rect, rank.text);
	}
	
	RND.CleanRenderer();
	
	

}
