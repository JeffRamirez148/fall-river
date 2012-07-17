#include <Windows.h>

#include "WinMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "XMLManager.h"
#include "IMenuState.h"
#include "HighScoresMenuState.h"
#include "CGame.h"

using namespace std;

void WinMenuState::Enter()
{
	pVM = ViewManager::GetInstance();
	pDI = DirectInput::GetInstance();

	WMS_ID =	pVM->RegisterTexture("resource/graphics/youWin.png");
	tempWinID = pVM->RegisterTexture("resource/graphics/sprites_pauseMenu.png");
	curPos = 400;

	audio = AudioManager::GetInstance();

	FMOD_VECTOR tmp = {0,0,0};
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	audio->SetListenerPos(tmp);
	soundID = audio->RegisterSound("resource/Sounds/KCJ_MenuClick.wav");
	audio->setSoundPos(soundID, sound1);

	audio->setSoundVel(soundID, tmp);
	audio->setSoundLooping(soundID, false);

	soundID2 = audio->RegisterSound("resource/Sounds/thunder.wav");
	audio->setSoundPos(soundID2, sound1);

	audio->setSoundVel(soundID2, tmp);
	audio->setSoundLooping(soundID2, false);

	musicID = audio->registerMusic("resource/Sounds/rainroof.wav");
	audio->setMusicPos(musicID, sound1);

	audio->setMusicVel(musicID, tmp);
	audio->setMusicLooping(musicID, true);
	audio->playMusic(musicID);

	musicID2 = audio->registerMusic("resource/Sounds/background.mp3");
	audio->setMusicPos(musicID2, sound1);

	audio->setMusicVel(musicID2, tmp);
	audio->setMusicLooping(musicID2, true);
	audio->playMusic(musicID2);
}

void WinMenuState::ReEnter()
{
	audio->playMusic(musicID);
	audio->playMusic(musicID2);
}

void WinMenuState::Exit() 
{
	pVM = nullptr;
	pDI = nullptr;
	audio = nullptr;
	WMS_ID = -1;
	tempWinID = -1;
}

bool WinMenuState::Input() 
{
	if(  pDI->KeyPressed(DIK_DOWN) || pDI->KeyPressed(DIK_S) || pDI->JoystickGetLStickDirPressed(DIR_DOWN,0) )
	{
		audio->playSound(soundID);
		curPos += 100;
		if( curPos > 500 )
			curPos = 400;
	}
	else if( pDI->KeyPressed(DIK_UP) || pDI->KeyPressed(DIK_W) || pDI->JoystickGetLStickDirPressed(DIR_UP,0) )
	{
		audio->playSound(soundID);
		curPos -= 100;
		if( curPos < 400 )
			curPos = 500;
	}

	if(pDI->KeyPressed(DIK_ESCAPE) ||  pDI->JoystickButtonPressed(1,0))
	{
		audio->playSound(soundID);
		curPos = 500;
	}

	if(pDI->KeyPressed(DIK_RETURN) || pDI->JoystickButtonPressed(0,0))
	{
		audio->playSound(soundID);
		if( curPos == 400 )
		{
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->ChangeState(HighScoresMenuState::GetInstance());
		}
		else if( curPos == 500 )
		{
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->RemoveState();
		}
	}
	return true;
}

void WinMenuState::Update(float aFElapsedTime) 
{
	
}

void WinMenuState::Render()
{
	pVM->GetSprite()->Flush();
	pVM->Clear();

	RECT backRect = { 12, 12, backRect.left+1200, backRect.top+700};
	pVM->DrawStaticTexture(WMS_ID, 0, 0,  0.8f, 0.9f, &backRect);

	RECT resumeRect = {1219, 13, resumeRect.left+287, resumeRect.top+44};
	RECT ExitRect = {1219, 223, ExitRect.left+287, ExitRect.top+44};
	RECT BloodRect = { 343, 789, BloodRect.left+526, BloodRect.top+144};

	if(curPos == 400)
	{resumeRect.left = 1535; resumeRect.right = resumeRect.left+287;}
	else if(curPos == 500)
	{ExitRect.left = 1535; ExitRect.right = ExitRect.left+287;}

	pVM->DrawStaticTexture(tempWinID, 170, curPos-50, 1.0f, 1.0f, &BloodRect);

	pVM->DrawStaticTexture(tempWinID, 350, 400,  0.5f, 0.9f, &resumeRect);
	pVM->DrawStaticTexture(tempWinID, 370, 500,  0.5f, 0.9f, &ExitRect);

}

WinMenuState* WinMenuState::GetInstance() 
{
	static WinMenuState s_Instance;

	return &s_Instance;
}

