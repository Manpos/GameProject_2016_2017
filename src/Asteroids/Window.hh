#pragma once
#include <SDL.h>

#define WIN_NAME "Test"

class Window {
private:
	int screenW, screenH;
	SDL_Window* m_window = nullptr;
public:
	Window(int, int);
	SDL_Window* GetWindow() { return m_window; }
};

Window::Window(int w, int h) : screenW(w), screenH(h) {
	m_window = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, SDL_WINDOW_SHOWN);
}
