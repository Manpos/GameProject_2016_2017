#pragma once
#include <rapidxml.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Scene.hh"
#include <vector>
#include <stdlib.h>
#include "GameScene.hh"


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

	GameScene* easy = nullptr, *medium = nullptr, *hard = nullptr;

public:
	std::vector<float> gameModeArr;
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
	void FromXmlToVector(rapidxml::xml_node<> *mode, std::vector<float> &vector) {
		while (mode != nullptr) {
			vector.push_back(float(strtod(mode->value(), nullptr)));
			mode = mode->next_sibling();
		}
	}

};
