#include <SDL.h>
#include <SDL_ttf.h>
#include "Window.hh"
#include "MenuScene.hh"

int main(int, char*[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	Window win(500, 500);

	RND.SetWindow(win.GetWindow());

	MenuScene menu;

	menu.OnEntry();

	while (IM.isRunning) {

		menu.Update();
		menu.Draw();		
	}
	
	TTF_Quit();
	SDL_Quit();

	return 0;
}



