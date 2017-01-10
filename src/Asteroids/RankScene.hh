#pragma once
#include "Scene.hh"
#include "AuxLib.hh"
#include <set>

#define RANK_LEN 10

//Struct to store the score and the name of the player
struct PlayerData {
	int scr;
	std::string name;
};

//Operator overload to sort PlayerData objects by score
inline bool operator< (const PlayerData &a, const PlayerData &b) {
	if (a.scr < b.scr) return true; 
	else return false;
}

class RankScene : public Scene {

private:
	const char* path = "../../res/ariblk.ttf";		//Path to open the font
	std::vector<PlayerData> data;					//Vector to read and write on the binary file
	std::multiset<PlayerData> set;					//Set to sort the ranking
	RTexture button, title;							//Button displayed in the bottom of the screen and the title at the top
public:
	PlayerData current;								//Stores the player's current data

	//Array which saves the path to the binary files of the ranking
	char* dif[3]{ "rankSavesE.bin" ,"rankSavesM.bin", "rankSavesH.bin" };

	RankScene() {									//Constructor of the class RankScene
		OnEntry();									//Calls the OnEntry method when created
	}
	//Declaration of the methods of the class
	void OnEntry();
	void Update();
	void Draw();
	void OnExit();
	void LoadRank(difficulties difficult);
	void UpdateRank(char *path);
	void AddSetValue(PlayerData ply);
	void PrintRanking(int nameX, int y, int initial);
	std::string PlayerName();

 };