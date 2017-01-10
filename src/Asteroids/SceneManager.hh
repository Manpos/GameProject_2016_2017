#pragma once
#include "AuxLib.hh"
#include "MenuScene.hh"
#include "SelectionScene.hh"
#include "GameScene.hh"
#include "RankScene.hh"

#define SM SceneManager::Instance()

class SceneManager {
private:


public:
	MenuScene *menu = nullptr;
	SelectionScene *selection = nullptr;
	GameScene *game = nullptr;
	RankScene *rank = nullptr;
	SceneType curr;

	difficulties currDif;

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
			AUX.current = curr;
			switch (curr)
			{
			case MENU:
				if (game != nullptr) {
					game->OnExit();
					game = nullptr;
				}
				if (rank != nullptr) {
					//rank->OnExit();
					rank = nullptr;
				}
				menu->Update();
				menu->Draw();				
				break;
			case SELECTION:
				if (menu != nullptr) {
					menu->OnExit();
					menu = nullptr;
				}			
				selection->Update();
				selection->Draw();
				break;
			case GAME:
				if (selection != nullptr) {
					selection->OnExit();
					selection = nullptr;
				}				
				game->Update();
				game->Draw();
				break;
			case RANK:
				if (game != nullptr) {
					rank->LoadRank(currDif);
					rank->current.name = rank->PlayerName();
					rank->current.scr = game->ReturnScore();
					rank->AddSetValue(rank->current);
					rank->UpdateRank(rank->dif[currDif]);
					rank->PrintRanking(150, 40, 150);
					game->OnExit();
					game = nullptr;
				}
				if (menu != nullptr) {
					rank->LoadRank(currDif);
					rank->PrintRanking(150, 40, 150);
					menu->OnExit();
					menu = nullptr;
				}
				else {
					rank->Update();
				}
				break;

			}
				
	}
};
