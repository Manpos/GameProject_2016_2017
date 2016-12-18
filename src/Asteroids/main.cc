#include <SDL.h>
#include <SDL_ttf.h>
#include "Window.hh"
#include "MenuScene.hh"
#include "SelectionScene.hh"
#include "SceneManager.hh"

int main(int, char*[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	Window win(800, 800);

	RND.SetWindow(win.GetWindow());

	SM.Start();

	while (AUX.gameRunning) {
		SM.Update();
				
	}
	
	TTF_Quit();
	SDL_Quit();

	return 0;
}



