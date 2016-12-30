#pragma once
#include "MenuScene.hh"
#include "SelectionScene.hh"
#include "AuxLib.hh"
#include "GameScene.hh"

#define SM SceneManager::Instance()

enum SceneType {MENU, SELECTION, GAME, RANK};

class SceneManager {
private:


public:
	MenuScene *menu = nullptr;
	SelectionScene *selection = nullptr;
	GameScene *game = nullptr;
	SceneType curr;

	static SceneManager& Instance() {
		static SceneManager a;
		return a;
	}

	void Start() {
		curr = MENU;
		AUX.gameRunning = true;
		menu = new MenuScene;
	}

	void Update() {
		while (AUX.gameRunning) {
			switch (curr)
			{
			case MENU:
				if (game != nullptr) {
					game->OnExit();
					game = nullptr;
				}
				menu->Update();
				menu->Draw();
				break;
			case SELECTION:
				menu->OnExit();
				menu = nullptr;
				selection->Update();
				selection->Draw();
				break;
			case GAME:
				selection->OnExit();
				selection = nullptr;
				game->Update();
				game->Draw();
				break;
			case RANK:

				break;

			default:
				break;
			}
		}		
	}
};

