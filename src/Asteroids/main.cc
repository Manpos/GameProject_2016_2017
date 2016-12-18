#include <SDL.h>
#include <SDL_ttf.h>
#include "Window.hh"
#include "MenuScene.hh"
#include "SelectionScene.hh"

int main(int, char*[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	Window win(800, 800);

	RND.SetWindow(win.GetWindow());

	MenuScene menu;
	SelectionScene selection;

	selection.OnEntry();
	menu.OnEntry();

	while (IM.isRunning) {
		// If the player is in the menu (false) the program will display the menu Scene
		if (!menu.isPlaying) {
			menu.Update();
			menu.Draw();
		}

		// When the bool is true, the game Scene will be running
		else if (menu.isPlaying) {
			selection.Update();
			selection.Draw();
		}
		
	}
	
	TTF_Quit();
	SDL_Quit();

	return 0;
}



