#include <Windows.h>
#include <vector>
using namespace std;

#include "ViewManager.h"
#include "GamePlayState.h"
#include "HighScoresMenuState.h"
#include "WinMenuState.h"
#include "DefeatMenuState.h"
#include "CreditsMenuState.h"
#include "LoadMenuState.h"
#include "PauseMenuState.h"
#include "MainMenuState.h"
#include "HowToPlayMenuState.h"
#include "Texture.h"
#include "Font.h"
#include "Animation.h"
#include "AnimInfo.h"
#include "HUD.h"
#include "CutScene.h"

ViewManager* ViewManager::GetInstance() 
{
	static ViewManager s_Instance;

	return &s_Instance;
}

int ViewManager::RegisterTexture(char* aFilePath)
{
	return 1;
}

int ViewManager::RegisterAnimation(char* aFilePath) 
{
	return 2;
}

int ViewManager::RegisterFont(char* aFilePath)
{
	return 3;
}

void ViewManager::Update(float aFElapsedTime) 
{
	
}

void ViewManager::RenderAnimation(AnimInfo* aAnimInfo, int aPositionX, int aPositionY)
{
	
}
