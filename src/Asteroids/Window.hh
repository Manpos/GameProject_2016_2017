#pragma once
#include <SDL.h>

#define WIN_NAME "Test"
struct WinDim {
	int w, h;
};
class Window {
private:
	WinDim size;
	SDL_Window* m_window = nullptr;
public:
	Window(int, int);
	SDL_Window* GetWindow() { return m_window; }
	WinDim getWindowSize() {
		return size;
	}
};

Window::Window(int w, int h) {
	size.w = w;
	size.h = h;
	m_window = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.w, size.h, SDL_WINDOW_SHOWN);
}
