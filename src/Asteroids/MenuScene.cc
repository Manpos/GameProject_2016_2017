#include <iostream>
#include "MenuScene.hh"

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
	if (IM.GetMouseCoords().x > msgRect.x && IM.GetMouseCoords().x < (msgRect.x + msgRect.w) &&
		IM.GetMouseCoords().y > msgRect.y && IM.GetMouseCoords().y < (msgRect.y + msgRect.h) &&
		IM.buttonPressed && IM.resetButton) {
		std::cout << "HOLOS" << std::endl;

		//Here goes the code to show the next menu (dificulties in this case)

		IM.resetButton = false;
		IM.buttonPressed = false;
	}

	else if (IM.GetMouseCoords().x > msgRect2.x && IM.GetMouseCoords().x < (msgRect2.x + msgRect2.w) &&
		IM.GetMouseCoords().y > msgRect2.y && IM.GetMouseCoords().y < (msgRect2.y + msgRect2.h) &&
		IM.buttonPressed && IM.resetButton) {
		std::cout << "ADEU" << std::endl;

		IM.isRunning = false;				//This ends the main loop and ends the program
	}
}

void MenuScene::Draw() {
	//The textures are drown and the Renderer is cleared
	RND.PrintText(msgRect, start);
	RND.PrintText(msgRect2, exit);
	RND.CleanRenderer();

}