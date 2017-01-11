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
	bool mouseBlocked = false;
public:

	//Control bools
	bool buttonPressed;
	bool resetButton;
	bool shooting = false;

	bool test = false;

	bool moveUp = false, moveLeft = false, moveRight = false, noMove = true;

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
	//This function checks at every moment if there is any input of the mouse or the keyboard
	void Update() {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: AUX.gameRunning = false; break;	//This event happens when the cross of the window is cilcked
			case SDL_MOUSEBUTTONDOWN:						// It detects if the mouse button has been pressed
				buttonPressed = true;   
				if (AUX.gameRunning) {
					shooting = true;
				}
				break;
			case SDL_MOUSEBUTTONUP:							// It detects if the mouse button has been released
				resetButton = true; 
				if (AUX.gameRunning) {
					shooting = false;
				}
				break;
			case SDL_MOUSEMOTION:							// It detects the motion of the mouse inside the window
				g_mouseCoords.x = event.motion.x; 
				g_mouseCoords.y = event.motion.y;
				mouseBlocked = false;
				break;
			case SDL_KEYDOWN:								// It detects if a key has been pressed
				if (event.key.keysym.sym == SDLK_ESCAPE && AUX.inGame) {
					AUX.paused = !AUX.paused;
				}
				if (event.key.keysym.sym == SDLK_w) {
					moveUp = true;
					noMove = false;
				}
				if (event.key.keysym.sym == SDLK_a) {
					mouseBlocked = true;
					moveLeft = true;
				}
				if (event.key.keysym.sym == SDLK_d) {
					mouseBlocked = true;
					moveRight = true;
				}
				if (event.key.keysym.sym == SDLK_SPACE) {
					shooting = true;
				}

				break;
			case SDL_KEYUP:									// It detects if the key has been released
				if (event.key.keysym.sym == SDLK_w) {
					noMove = true;
					moveUp = false;
				}
				if (event.key.keysym.sym == SDLK_a) {
					moveLeft = false;
				}
				if (event.key.keysym.sym == SDLK_d) {
					moveRight = false;
				}

				shooting = false; 
				break;
			}
			}
		}

	bool IsShooting() {
		return shooting;
	}

	// It creates a pushonable button for a SDL_Rect
	bool ButtonPress(SDL_Rect rect) {
		if (IM.GetMouseCoords().x > rect.x && IM.GetMouseCoords().x < (rect.x + rect.w) &&
			IM.GetMouseCoords().y > rect.y && IM.GetMouseCoords().y < (rect.y + rect.h) &&
			IM.buttonPressed && IM.resetButton) {
			return true;
		}
		else return false;
	}
	void ResetButton() {									// Resets the state of the buttons or keys
		if (IM.buttonPressed && IM.resetButton) {
			IM.resetButton = false;
			IM.buttonPressed = false;
		}
	}

	bool TestKey() {
		return test;
	}

	bool ReturnMouseBlock() {								// Return if the mouse is blocked when using leys
		return mouseBlocked;
	}
};