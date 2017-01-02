#pragma once
#include "Scene.hh"
#include "RankScene.hh"

//Class which Inherits from Scene.hh
class MenuScene : public Scene {
private:
	//FONTS
	const char* path = "../../res/ariblk.ttf";
	bool rankSelection;
	RTexture start, rank, exit, easy, medium, hard;
	
public:
	MenuScene() {
		OnEntry();
	}
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
};