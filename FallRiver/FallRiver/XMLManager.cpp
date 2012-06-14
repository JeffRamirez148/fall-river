#include <Windows.h>
#include <string>
using namespace std;

#include "XMLManager.h"
#include "PauseMenuState.h"
#include "MainMenuState.h"
#include "WinMenuState.h"
#include "DefeatMenuState.h"
#include "OptionsMenuState.h"
#include "GamePlayState.h"
#include "LoadMenuState.h"
#include "ViewManager.h"
#include "Level.h"
#include "Emitter.h"
XMLManager* XMLManager::GetInstance(void)
{
	static XMLManager s_Instance;
	return &s_Instance;
}

Level* XMLManager::Parse(string aFile) 
{
	return NULL;
}

float* XMLManager::ParseSound(string aFile) 
{
	return 0;
}

void ParseAnim(char* aFile, Animation& anim)
{

}

Emitter* XMLManager::ParseEmitter(string aFile)
{
	return NULL;
}
