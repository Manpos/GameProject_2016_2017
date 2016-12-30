#pragma once
#include "Scene.hh"

//Class which Inherits from Scene.hh
class MenuScene : public Scene {
private:
	//FONTS
	const char* path = "../../res/ariblk.ttf";

	RTexture start;
	RTexture exit;

public:
	MenuScene() {
		OnEntry();
	}
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
};