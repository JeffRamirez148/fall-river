#include <Windows.h>
#include <string>
using namespace std;

#ifndef __XMLManager_h__
#define __XMLManager_h__

class Emitter;
class Level;
class Animation;

#include "tinystr.h"
#include "tinyxml.h"

class XMLManager
{

public:
	Level* Parse(string aFile);
	float* ParseSound(string aFile);
	void ParseAnim(char* aFile, Animation& anim);
	static XMLManager* GetInstance(void);
	Emitter* ParseEmitter(string aFile);
};

#endif
