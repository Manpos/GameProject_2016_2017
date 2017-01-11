#pragma once
#include "Scene.hh"

//Class which Inherits from Scene.hh
class MenuScene : public Scene {
private:
	//Displayed text variables
	const char* path = "../../res/ariblk.ttf";
	bool rankSelection;
	RTexture start, rank, exit, easy, medium, hard, title, selectDif;
	
public:
	MenuScene() {
		OnEntry();
	}
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
};