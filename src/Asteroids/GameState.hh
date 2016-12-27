#pragma once
#include "Window.hh"
#include <SDL.h>
#include <SDL_ttf.h>
#include "SceneManager.hh"

void GameState(int win_w, int win_h) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	AUX.SetWindowSize(win_w, win_h);

	Window win(win_w, win_h);

	RND.SetWindow(win.GetWindow());

	SM.Start();

	while (AUX.gameRunning) {
		SM.Update();
	}

	TTF_Quit();
	SDL_Quit();
};