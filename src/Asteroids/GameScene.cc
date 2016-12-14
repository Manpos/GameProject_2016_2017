#include <iostream>
#include "GameScene.hh"


void GameScene::OnEntry() {

	font = TTF_OpenFont("../../res/ariblk.ttf", 35);
	firstBoxMs = TTF_RenderText_Solid(font, "Level 1", textColor);
	secondBoxMs = TTF_RenderText_Solid(font, "Level 2", textColor);

	msgRect = { 45, 45, firstBoxMs->w, secondBoxMs->h };
	firstBox = RND.SurfToText(firstBoxMs);

	msgRect2 = { 300,45, secondBoxMs->w, secondBoxMs->h };
	secondBox = RND.SurfToText(secondBoxMs);

	IM.Start();
}

void GameScene::OnExit() {
}

void GameScene::Update() {
	IM.Update();

	if (IM.GetMouseCoords().x > msgRect.x && IM.GetMouseCoords().x < (msgRect.x + msgRect.w) &&
		IM.GetMouseCoords().y > msgRect.y && IM.GetMouseCoords().y < (msgRect.y + msgRect.h) &&
		IM.buttonPressed && IM.resetButton) { 
		std::cout << "Ara vols entrar al nivell 1" << std::endl;

		// TODO code per canviar de menu

		IM.resetButton = false;
		IM.buttonPressed = false;
	}

	else if (IM.GetMouseCoords().x > msgRect2.x && IM.GetMouseCoords().x < (msgRect2.x + msgRect2.w) &&
		IM.GetMouseCoords().y > msgRect2.y && IM.GetMouseCoords().y < (msgRect2.y + msgRect2.h) &&
		IM.buttonPressed && IM.resetButton) {
		std::cout << "Te la jugues amb el nivell 2?" << std::endl;

		IM.resetButton = false;
		IM.buttonPressed = false;
	}

}

void GameScene::Draw() {
	RND.PrintText(msgRect, firstBox);
	RND.PrintText(msgRect2, secondBox);
	RND.CleanRenderer();
}