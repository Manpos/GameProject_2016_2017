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
		while (AUX.gameRunning) {
			AUX.current = curr;
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
				if (game != nullptr) {
					rank->LoadRank(currDif);
					rank->current.name = rank->PlayerName();
					rank->current.scr = game->score;
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
				rank->Update();
				rank->Draw();
				break;

			default:
				break;
			}
		}		
	}
};

