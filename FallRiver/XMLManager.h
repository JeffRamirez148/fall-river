#include <Windows.h>
#include <string>
using namespace std;

#ifndef __XMLManager_h__
#define __XMLManager_h__

// #include "PauseMenuState.h"
// #include "MainMenuState.h"
// #include "WinMenuState.h"
// #include "DefeatMenuState.h"
// #include "OptionsMenuState.h"
// #include "GamePlayState.h"
// #include "LoadMenuState.h"

class PauseMenuState;
class MainMenuState;
class WinMenuState;
class DefeatMenuState;
class OptionsMenuState;
class GamePlayState;
class LoadMenuState;
class XMLManager;
class Level;

class XMLManager
{

public: 
	Level* Parse(string aFile);
	float* ParseSound(string aFile);

};

#endif
