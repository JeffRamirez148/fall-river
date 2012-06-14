#include <Windows.h>
#include <string>
using namespace std;

#ifndef __XMLManager_h__
#define __XMLManager_h__

class Emitter;
class Level;

class XMLManager
{

public: 
	Level* Parse(string aFile);
	float* ParseSound(string aFile);
	static XMLManager* GetInstance(void);
	Emitter* ParseEmitter(string aFile);

};

#endif
