#pragma once
#include <SDL.h>

#define WIN_NAME "Test"

class Window {
private:
	SDL_Window* m_window = nullptr;
public:
	Window(int, int);
	SDL_Window* GetWindow() { return m_window; }

};

Window::Window(int w, int h) {

	m_window = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
}
