#include "SelectionScene.hh"

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
		
		std::cout << mode->first_attribute()->value() << std::endl;
		// TODO code per canviar de menu

		IM.resetButton = false;
		IM.buttonPressed = false;
	}

	else if (IM.ButtonPress(msgRect2)) {
		std::cout << mode->next_sibling()->first_attribute()->value() << std::endl;

		IM.resetButton = false;
		IM.buttonPressed = false;
	}

	else if (IM.ButtonPress(msgRect3)) {
		std::cout << mode->next_sibling()->next_sibling()->first_attribute()->value() << std::endl;

		IM.resetButton = false;
		IM.buttonPressed = false;
	}

}

void SelectionScene::Draw() {
	RND.PrintText(msgRect, firstBox);
	RND.PrintText(msgRect2, secondBox);
	RND.PrintText(msgRect3, thirdBox);
	RND.CleanRenderer();
}