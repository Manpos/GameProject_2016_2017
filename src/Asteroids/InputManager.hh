#pragma once
#include <queue>
#include <SDL.h>
#include <iostream>
#include "AuxLib.hh"

#define IM InputManager::Instance()			//Singleton defined, so we don't have to instantiate an InputManager object everytime

enum plMovement {FOWARD, RIGHT, LEFT, BACK, STATIC};

struct MouseCoords{							//Struct to save Mouse coordinates at any moment
	Sint32 x = 0, y = 0;
};

class InputManager {						//Class created to control the inputs of the user
private:
	SDL_Event event;						//SDL_Event which will get user's inputs
	MouseCoords g_mouseCoords;
public:

	//Control bools
	bool buttonPressed;
	bool resetButton;
	int plMove = 0;

	inline static InputManager& Instance() { //Singleton creation
		static InputManager a;
		return a;
	}

	MouseCoords GetMouseCoords (){			//Function which returns mouse coords at a certain moment
		return g_mouseCoords;
	}

	void Start() {							//Function which initializes the bools
		buttonPressed = false;
		resetButton = false;

	}
	//This function checks at every moment if there is any input of the mouse
	void Update() {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: AUX.gameRunning = false; break;	//This event happens when the cross of the window is cilcked
			case SDL_MOUSEBUTTONDOWN: buttonPressed = true;   std::cout << "1"; break;
			case SDL_MOUSEBUTTONUP: resetButton = true; std::cout << "0";  break;
			case SDL_MOUSEMOTION: g_mouseCoords.x = event.motion.x; g_mouseCoords.y = event.motion.y; break;
			case SDL_KEYDOWN: std::cout << "Has pitjat una tecla eh" << std::endl;
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: AUX.paused = !AUX.paused; break;
				case SDLK_w: plMove = 1; break;
				case SDLK_a: plMove = 2; break;
				case SDLK_s: plMove = 3; break;
				case SDLK_d: plMove = 4; break;
				} break;
			case SDL_KEYUP: plMove = 0;  break;
			}
			}
		}
	bool ButtonPress(SDL_Rect rect) {
		if (IM.GetMouseCoords().x > rect.x && IM.GetMouseCoords().x < (rect.x + rect.w) &&
			IM.GetMouseCoords().y > rect.y && IM.GetMouseCoords().y < (rect.y + rect.h) &&
			IM.buttonPressed && IM.resetButton) {
			return true;
		}
		else return false;
	}
	void ResetButton() {
		if (IM.buttonPressed && IM.resetButton) {
			IM.resetButton = false;
			IM.buttonPressed = false;
		}
	}

	int returnMovement() {
		return plMove;
	}
};