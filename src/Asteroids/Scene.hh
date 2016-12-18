#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "InputManager.hh"
#include "Renderer.hh"
#include <iostream>
#include <SDL_surface.h>

class Scene {
	friend class SceneManager;
public:
	void OnEntry();		// Called when entering a new Scene
	void OnExit();		// Called when leaving a Scene
	void Update();		// The main update of the scene in game loop
	void Draw();		// The main draw of the scene in game loop

};