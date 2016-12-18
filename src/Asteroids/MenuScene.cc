#include <iostream>
#include "MenuScene.hh"
#include "SceneManager.hh"

//Content of the class MenuScene.hh
void MenuScene::OnEntry() {

	//Font load
	font = TTF_OpenFont("../../res/ariblk.ttf", 24);
	startMs = TTF_RenderText_Solid(font, "START", textColor);
	exitMs = TTF_RenderText_Solid(font, "EXIT", textColor);

	//Rectangles for Textures
	msgRect = { 45,45, startMs->w, startMs->h };
	start = RND.SurfToText(startMs);

	msgRect2 = { 45,90, exitMs->w, exitMs->h };
	exit = RND.SurfToText(exitMs);

	IM.Start();								//Call to the inicialization of the elements in InputManager::Start()
}

void MenuScene::OnExit() {
}

void MenuScene::Update() {
	IM.Update();							//Call to the update of the input manager

	//Conditions to determinate the zone where the input of the user should make effect
	if (IM.ButtonPress(msgRect)) {
		std::cout << "HOLOS" << std::endl;

		isPlaying = true; //Change the condition of the main
		//Here goes the code to show the next menu (dificulties in this case)
		SM.curr = SELECTION;

		IM.resetButton = false;
		IM.buttonPressed = false;
	}

	else if (IM.ButtonPress(msgRect2)) {
		std::cout << "ADEU" << std::endl;

		AUX.gameRunning = false;				//This ends the main loop and ends the program
	}
}

void MenuScene::Draw() {
	//The textures are drown and the Renderer is cleared
	RND.PrintText(msgRect, start);
	RND.PrintText(msgRect2, exit);
	RND.CleanRenderer();

}