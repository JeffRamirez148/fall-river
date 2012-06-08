#include <Windows.h>
#include <vector>
using namespace std;

#include "AudioManager.h"
#include "GamePlayState.h"
#include "HighScoresMenuState.h"
#include "WinMenuState.h"
#include "DefeatMenuState.h"
#include "CreditsMenuState.h"
#include "LoadMenuState.h"
#include "PauseMenuState.h"
#include "MainMenuState.h"
#include "HowToPlayMenuState.h"
#include "CutScene.h"
#include "sound.h"

AudioManager* AudioManager::GetInstance()
{
	static AudioManager s_Instance;

	return &s_Instance;
}
