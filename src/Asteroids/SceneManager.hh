#pragma once
#include "AuxLib.hh"
#include "MenuScene.hh"
#include "SelectionScene.hh"
#include "GameScene.hh"
#include "RankScene.hh"

#define SM SceneManager::Instance()				// Singleton defdined, so we don't have to instatiate an SceneManager object everytime

class SceneManager {							// Class used to manage the different scenes in the game
private:
public:

	// The following pointers are used to create scenes when needed and also erase them 
	MenuScene *menu = nullptr;
	SelectionScene *selection = nullptr;
	GameScene *game = nullptr;
	RankScene *rank = nullptr;
	SceneType curr;								// It indicates the type of the current scene

	difficulties currDif;						// It indicates the current dificulty

	static SceneManager& Instance() {			// Declaration of the singleton
		static SceneManager a;
		return a;
	}

	void Start() {								// Declares initial values to some atributes
		curr = MENU;
		AUX.gameRunning = true;
		menu = new MenuScene;
	}

	void Update() {
			AUX.current = curr;

			// This switch checks the state of "curr" every itereation to display the correct scene
			switch (curr)
			{
			case MENU:							//Updates and prints selection and deletes the prevoius MenuScene
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
			case SELECTION:						//Updates and prints selection and deletes the prevoius MenuScene
				if (menu != nullptr) {
					menu->OnExit();
					menu = nullptr;
				}			
				selection->Update();
				selection->Draw();
				break;
			case GAME:							//Updates and prints game and deletes the prevoius SelectionScene
				if (selection != nullptr) {
					selection->OnExit();
					selection = nullptr;
				}				
				game->Update();
				game->Draw();
				break;
			case RANK:							//Updates and prints rank and deletes the prevoius MenuScene or GameScene
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
