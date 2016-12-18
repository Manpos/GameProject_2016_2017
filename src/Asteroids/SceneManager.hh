#pragma once
#include <unordered_map>
#include "MenuScene.hh"
#include "SelectionScene.hh"
#include "AuxLib.hh"

#define SM SceneManager::Instance()

enum SceneType {MENU, SELECTION, GAME, RANK};

class SceneManager {
private:
	std::unordered_map<SceneType, Scene> scMap;
	MenuScene menu;
	SelectionScene selection;

public:

	SceneType curr;

	static SceneManager& Instance() {
		static SceneManager a;
		return a;
	}

	void Start() {
		curr = MENU;
		AUX.gameRunning = true;
		selection.OnEntry();
		menu.OnEntry();
	}

	void Update() {
		while (AUX.gameRunning) {
			switch (curr)
			{
			case MENU:
				menu.Update();
				menu.Draw();
				break;
			case SELECTION:
				selection.Update();
				selection.Draw();
				break;
			case GAME:

				break;
			case RANK:

				break;

			default:
				break;
			}
		}		
	}
};

