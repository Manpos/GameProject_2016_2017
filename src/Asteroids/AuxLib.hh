#pragma once

#define AUX AuxLib::Instance()

enum SceneType { MENU, SELECTION, GAME, RANK };
enum difficulties { D_EASY, D_MEDIUM, D_HARD };
class AuxLib {
private:
public:
	static AuxLib& Instance(){
		static AuxLib aux;
		return aux;
	}
	bool gameRunning;
	bool paused;
	SceneType current = MENU;

	//Window size
	int w, h;
	void SetWindowSize(int we, int he) {
		w = we;
		h = he;
	}
};
