#include "RankScene.hh"
#include <string>
#include <iostream>
#include "SceneManager.hh"
#include "transform.hh"

 //Definition of the methods of RankScene class
void RankScene::OnEntry() {
	//Creation and positioning of the button and title

	title = RND.LPFont(path, 40, "RANKING", 255, 255, 255);
	transform.position(title.rect, 0, -300, CENTERED);

	button = RND.LPFont(path, 30, "MAIN MENU", 255, 255, 255);
	transform.position(button.rect, 0, 300, CENTERED);
}

void RankScene::OnExit() {
						
}

void RankScene::Update() {
	IM.Update();

	if (IM.ButtonPress(button.rect)){
		SM.menu = new MenuScene;
		SM.curr = MENU;
	}

	IM.ResetButton();
}

void RankScene::Draw() {
	RND.PrintText(button.rect, button.text);
	RND.CleanRenderer();
}

//Loads a binary file depending on the difficultty, if it doesn't exists it's created
void RankScene::LoadRank(difficulties difficult) {
	char *path = dif[difficult];					//Copies the path from dif depending on the parameter introduced
	data.resize(RANK_LEN);							//Resizes the lenght of the vector to avoid having it longer than the lenght specified
	SDL_RWops* file = SDL_RWFromFile(path, "r+b");	//Opens the file to read
	//Check if the files exists
	if (file == nullptr) {
		file = SDL_RWFromFile(path, "w+b");
		//Creates the file
		if (file != nullptr) {
			//Initialize data
			for (int i = 0; i < RANK_LEN; ++i) {
				data[i] = { 0, " "};
				SDL_RWwrite(file, &data[i], sizeof(PlayerData), 1);
				set.insert(data[i]);
			}
		}
		//Close file
		SDL_RWclose(file);
	}

	else {
		//Load data
		for (int i = 0; i < RANK_LEN; ++i) {
			SDL_RWread(file, &data[i], sizeof(PlayerData), 1, RANK_LEN);
			set.insert(data[i]);
			
		}
		//Close file
		SDL_RWclose(file);
	}

}

//Udates Ranking data
void RankScene::UpdateRank(char * path) {
	SDL_RWops* file = SDL_RWFromFile(path , "w+b");
	auto it = set.begin();
	for (int i = 0; i < RANK_LEN; ++i)	{
		data[i] = *(it); ++it;
		SDL_RWwrite(file, &data[i], sizeof(PlayerData), 1);
	}
	SDL_RWclose(file);
}

//Adds a value to the multiset changing the last one if its full
void RankScene::AddSetValue(PlayerData ply) {
	if (set.size() >= RANK_LEN) {
		set.erase(set.begin());
	}
	set.insert(ply);

}

//Listens to user text input and shows it on screen
std::string RankScene::PlayerName() {

	TTF_Font *font = RND.LoadFont("../../res/ariblk.ttf", 15);
	RTexture textRec, info;

	info = RND.PrepareFont(font, "Introduce a name of maximum 6 characters:", 255, 255, 255);
	transform.position(info.rect, 0, -40, CENTERED);

	RND.PrintText(info.rect, info.text);
	RND.CleanRenderer();

	font = RND.LoadFont("../../res/ariblk.ttf", 20);

	std::string text = "";
	bool done = false;
	SDL_StartTextInput();
	while (!done) {
		bool renderText = false;
		SDL_Event event;

		while (SDL_PollEvent(&event) > 0){
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0) {
					text.pop_back();
					renderText = true;
				}
				else if (event.key.keysym.sym == SDLK_RETURN) {
					done = true;
				}
			}
			else if (event.type == SDL_TEXTINPUT && text.length() < 6) {
				text += event.text.text;
				renderText = true;
			}
			else renderText = false;
		}

		if (renderText) {			
			if (text != "") {
				textRec = RND.PrepareFont(font, text.c_str(), 255, 255, 255);
			}
			else textRec = RND.PrepareFont(font, " ", 255, 255, 255);

			transform.position(textRec.rect, 0, 0, CENTERED);
			RND.PrintText(info.rect, info.text);
			RND.PrintText(textRec.rect, textRec.text);
			RND.CleanRenderer();
		}

	}
	SDL_StopTextInput();

	return text;
}

//Prints the current content of the ranking
void RankScene::PrintRanking(int nameX, int sep, int initial) {
	TTF_Font *font = RND.LoadFont(path, 25);
	std::vector<SDL_Surface*> surf(RANK_LEN);
	std::string tmp;
	RTexture rankName[RANK_LEN];
	RTexture rankScore[RANK_LEN];
	
	int scoreX = AUX.w - nameX - 50;
	auto it = set.end();	

	for (int i = 0; i < RANK_LEN; ++i) {
		--it;
		tmp = std::to_string(it->scr);
		rankName[i] = RND.PrepareFont(font, it->name.c_str(), 255, 255, 255);
		rankScore[i] = RND.PrepareFont(font, tmp.c_str(), 255, 255, 255);

		transform.position(rankName[i].rect, nameX, sep*i + initial);
		transform.position(rankScore[i].rect, scoreX, sep*i + initial);		

		RND.PrintText(rankName[i].rect, rankName[i].text);
		RND.PrintText(rankScore[i].rect, rankScore[i].text);

	}
	RND.PrintText(button.rect, button.text);
	RND.PrintText(title.rect, title.text);
	RND.CleanRenderer();
}