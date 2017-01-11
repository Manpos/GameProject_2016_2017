#pragma once
#include "Window.hh"
#include <SDL.h>							
#include <SDL_ttf.h>
#include "SceneManager.hh"

void GameState(int win_w, int win_h) {

	SDL_Init(SDL_INIT_EVERYTHING);			// Starts the SDL_library
	TTF_Init();

	AUX.SetWindowSize(win_w, win_h);		// Pases the width and the height of the window to AUX

	Window win(win_w, win_h);				// Window object is created

	RND.SetWindow(win.GetWindow());			// Gives a window object to the renderer

	SM.Start();								// Calls the function Start() of the SceneManager

	while (AUX.gameRunning) {
		TM.Update([&] {	SM.Update(); });
	}

	

	TTF_Quit();
	SDL_Quit();								// Quits the SDL Library
};