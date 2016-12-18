#pragma once
#include "Scene.hh"
#include <rapidxml.hpp>
#include <fstream>
#include <sstream>
#include <iostream>



class SelectionScene : public Scene {
private:
	SDL_Surface *firstBoxMs, *secondBoxMs, *thirdBoxMs= NULL;
	TTF_Font *font = NULL;
	SDL_Color textColor = { 255,255,255 };

	SDL_Rect msgRect, msgRect2, msgRect3;
	SDL_Texture *firstBox, *secondBox, *thirdBox;

	rapidxml::xml_document <> doc;
	rapidxml::xml_node<> *root;
	rapidxml::xml_node<> *mode;
	std::stringstream buffer;

public:
	SelectionScene() = default;
	void OnEntry();
	void OnExit();
	void Update();
	void Draw();
	void LoadXml() {
		std::ifstream file("difCnfg.xml");
		buffer << file.rdbuf();
		file.close();

	};
};
