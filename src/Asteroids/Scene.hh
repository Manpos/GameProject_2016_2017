#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "InputManager.hh"
#include "Renderer.hh"
#include <iostream>
#include <string>
#include <SDL_surface.h>
#include "transform.hh"


class Scene {
public:
	virtual void OnEntry() {};		// Called when entering a new Scene
	virtual void OnExit() {};		// Called when leaving a Scene
	virtual void Update() {};		// The main update of the scene in game loop
	virtual void Draw() {};			// The main draw of the scene in game loop

};