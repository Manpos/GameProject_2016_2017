#pragma once
// Header to store global functions and elements
#define AUX AuxLib::Instance()

// Global enums for the type of the scene and the dificulties
enum SceneType { MENU, SELECTION, GAME, RANK };
enum difficulties { D_EASY, D_MEDIUM, D_HARD };
class AuxLib {
private:
public:

	static AuxLib& Instance(){				// Singleton of yhe class
		static AuxLib aux;
		return aux;
	}
	bool gameRunning;						// State bools of the class
	bool paused;
	bool inGame = false;
	SceneType current = MENU;				// Declaration of an object SceneType with initial value MENU

	//Window size
	int w, h;
	void SetWindowSize(int we, int he) {	// Set the window size
		w = we;
		h = he;
	}

	float degreesToRadians(double degs) {	// Conversor from degrees to radians
		return degs * 3.1416 / 180;
	}

};
