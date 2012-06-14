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
<<<<<<< HEAD
	void ParseAnim(char* aFile, Animation& anim);
=======
	static XMLManager* GetInstance(void);
	Emitter* ParseEmitter(string aFile);

>>>>>>> 4834037b554bbbd2afc2e6f78cc2faf1ce119c2f
};

#endif
