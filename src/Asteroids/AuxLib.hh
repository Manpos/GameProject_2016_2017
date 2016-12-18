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
};
