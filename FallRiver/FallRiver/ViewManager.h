#include <Windows.h>
#include <vector>
using namespace std;

#ifndef __ViewManager_h__
#define __ViewManager_h__

// #include "GamePlayState.h"
// #include "HighScoresMenuState.h"
// #include "WinMenuState.h"
// #include "DefeatMenuState.h"
// #include "CreditsMenuState.h"
// #include "LoadMenuState.h"
// #include "PauseMenuState.h"
// #include "MainMenuState.h"
// #include "HowToPlayMenuState.h"
// #include "Texture.h"
// #include "Font.h"
// #include "Animation.h"
// #include "AnimInfo.h"
// #include "HUD.h"
// #include "CutScene.h"

class GamePlayState;
class HighScoresMenuState;
class WinMenuState;
class DefeatMenuState;
class CreditsMenuState;
class LoadMenuState;
class PauseMenuState;
class MainMenuState;
class HowToPlayMenuState;
class Texture;
class Font;
class Animation;
class AnimInfo;
class HUD;
class CutScene;
class ViewManager;

class ViewManager
{
private: 
	vector<Animation*> animations;
	vector<Texture*> textures;
	vector<Font*> fonts;

public: 
	static ViewManager* GetInstance();
	int RegisterTexture(char* aFilePath);
	int RegisterAnimation(char* aFilePath);
	int RegisterFont(char* aFilePath);
	void Update(float aFElapsedTime);
	void RenderAnimation(AnimInfo* aAnimInfo, int aPositionX, int aPositionY);
};

#endif
