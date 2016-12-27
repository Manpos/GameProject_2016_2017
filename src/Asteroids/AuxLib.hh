#pragma once

#define AUX AuxLib::Instance()
class AuxLib {
private:
public:
	static AuxLib& Instance(){
		static AuxLib aux;
		return aux;
	}
	bool gameRunning;
	bool paused;

	//Window size
	int w, h;
	void SetWindowSize(int we, int he) {
		w = we;
		h = he;
	}
};
