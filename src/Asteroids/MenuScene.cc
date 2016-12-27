#include <iostream>
#include "MenuScene.hh"
#include "SceneManager.hh"
#include "transform.hh"

//Content of the class MenuScene.hh
void MenuScene::OnEntry() {

	////Font load and positioning
	start = RND.LPFont(path, 24, "START", 255, 255, 255);
	transform.position(start.rect, 50, 50);

	exit = RND.LPFont(path, 24, "EXIT", 255, 255, 255);
	transform.position(exit.rect, 50, 100);

	IM.Start();								//Call to the inicialization of the elements in InputManager::Start()
}

void MenuScene::OnExit() {
}

void MenuScene::Update() {
	IM.Update();							//Call to the update of the input manager

	//Conditions to determinate the zone where the input of the user should make effect
	if (IM.ButtonPress(start.rect)) {
		std::cout << "HOLOS" << std::endl;

		//Change the condition of the main
		SM.curr = SELECTION;


	}

	else if (IM.ButtonPress(exit.rect)) {
		std::cout << "ADEU" << std::endl;
		AUX.gameRunning = false;				//This ends the main loop and ends the program
	}

	IM.ResetButton();
}

void MenuScene::Draw() {
	//The textures are drown and the Renderer is cleared
	RND.PrintText(start.rect,start.text);
	RND.PrintText(exit.rect, exit.text);
	RND.CleanRenderer();

}