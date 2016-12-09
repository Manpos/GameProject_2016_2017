#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Renderer.hh"
#include "Window.hh"

int main(int, char*[]) {
	Window win(500, 500);
	Renderer rend(win.GetWindow());

	//SPRITES
	SDL_Texture *plTexture = IMG_LoadTexture(rend.GetRenderer(), "../../res/SpriteSheet.png");
	SDL_Rect plRect = { 250-(75/2),250-(50/2), 75, 50 };

	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type)	{
			case SDL_QUIT: isRunning = false; break;
			//case SDL_MOUSEBUTTONDOWN: break;
			default:;
			}
		}
		SDL_RenderCopy(rend.GetRenderer(), plTexture, nullptr, &plRect);
		SDL_RenderPresent(rend.GetRenderer());
		SDL_RenderClear(rend.GetRenderer());
	}
	SDL_DestroyWindow(win.GetWindow());
	SDL_DestroyTexture(plTexture);
	SDL_DestroyRenderer(rend.GetRenderer());

	IMG_Quit();
	SDL_Quit();

	return 0;
}




//SDL_Window* gWindow = NULL;
//SDL_Surface* gScreenSurface = NULL;
//SDL_Surface* gHelloWorld = NULL;
//
//bool init() {
//	//Initialization class
//	bool success = true;
//
//	//Initialize SDL
//	//SDL_Init() returns -1 if there's an error
//	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//		std::cout << SDL_GetError() << std::endl;
//		success = false;
//	}
//	else {
//		//Create window
//		gWindow = SDL_CreateWindow("Testing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//		if (gWindow == NULL) {
//			std::cout << SDL_GetError() << std::endl;
//			success = false;
//		}
//		else {
//			//Get Window surface
//			gScreenSurface = SDL_GetWindowSurface(gWindow);
//		}
//	}
//	return success;
//
//};
//bool loadMedia() {
//	//Loading success flag
//	bool success = true;
//
//	//Load splash image
//	RND.test();
//};
//void close();





/*SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
if (SDL_Init(SDL_INIT_VIDEO) < 0) {
std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
}
else {
(window = SDL_CreateWindow("SDL_TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
if (window == NULL) {
std::cout << "window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
}
else {
screenSurface = SDL_GetWindowSurface(window);
SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFA, 0xFB, 0xFC));
SDL_UpdateWindowSurface(window);
SDL_Delay(2000);
}
}
SDL_DestroyWindow(window);
SDL_Quit();*/


