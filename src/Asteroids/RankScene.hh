#pragma once
#include "Scene.hh"
#include "AuxLib.hh"
#include <set>

#define RANK_LEN 10

struct PlayerData {
	int scr;
	std::string name;
};

inline bool operator< (const PlayerData &a, const PlayerData &b) {
	if (a.scr < b.scr) return true; 
	else if (a.scr == b.scr) { if (a.name < b.name) return true; else return false; }
	else return false;
}

class RankScene : public Scene {

private:
	const char* path = "../../res/ariblk.ttf";
	std::vector<PlayerData> data;
	std::multiset<PlayerData> set;
	RTexture button;
public:
	PlayerData current;
	RankScene() {
		OnEntry();
	}
	~RankScene() {
		delete &current.name;
	}

	void OnEntry();
	void Update();
	void Draw();
	void OnExit();

	char* dif[3]{ "..\\..\\saves\\rankSavesE.bin" ,"..\\..\\saves\\rankSavesM.bin", "..\\..\\saves\\rankSavesH.bin" };

	void LoadRank(difficulties difficult);
	void UpdateRank(char *path);
	void AddSetValue(PlayerData ply);
	void PrintRanking(int nameX, int y, int initial);
	std::string PlayerName();

	//Multiset + array/vector
 };