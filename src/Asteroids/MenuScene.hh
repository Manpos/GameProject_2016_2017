#pragma once
#include "Scene.hh"

class MenuScene : public Scene {
public:
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
};