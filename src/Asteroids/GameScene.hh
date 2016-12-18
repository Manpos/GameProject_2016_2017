#pragma once
#include "Scene.hh"

class GameScene : public Scene {
private:

public:
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
};