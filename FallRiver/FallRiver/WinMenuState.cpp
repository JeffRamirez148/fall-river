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
	curPos = 250;

	audio = AudioManager::GetInstance();

	FMOD_VECTOR tmp = {0,0,0};
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	audio->SetListenerPos(tmp);
	soundID = audio->RegisterSound("resource/Sounds/KCJ_MenuClick.wav");
	audio->setSoundPos(soundID, sound1);

	audio->setSoundVel(soundID, tmp);
	audio->setSoundLooping(soundID, false);

	musicID = audio->registerMusic("resource/Sounds/background.mp3");
	audio->setMusicPos(musicID, sound1);

	audio->setMusicVel(musicID, tmp);
	audio->setMusicLooping(musicID, true);
	audio->playMusic(musicID);
}

void WinMenuState::ReEnter()
{
	audio->playMusic(musicID);
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
	if( pDI->KeyPressed(DIK_DOWNARROW) )
	{
		audio->playSound(soundID);
		curPos += 50;
		if( curPos > 300 )
			curPos = 250;
	}
	else if( pDI->KeyPressed(DIK_UPARROW) )
	{
		audio->playSound(soundID);
		curPos -= 50;
		if( curPos < 250 )
			curPos = 300;
	}

	if(pDI->KeyPressed(DIK_ESCAPE) )
	{
		audio->playSound(soundID);
		curPos = 300;
	}

	if(pDI->KeyPressed(DIK_RETURN))
	{
		audio->playSound(soundID);
		if( curPos == 250 )
		{
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->ChangeState(HighScoresMenuState::GetInstance());
		}
		else if( curPos == 300 )
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

	if(curPos == 250)
	{resumeRect.left = 1535; resumeRect.right = resumeRect.left+287;}
	else if(curPos == 300)
	{ExitRect.left = 1535; ExitRect.right = ExitRect.left+287;}

	pVM->DrawStaticTexture(tempWinID, 350, 400,  0.5f, 0.9f, &resumeRect);
	pVM->DrawStaticTexture(tempWinID, 370, 500,  0.5f, 0.9f, &ExitRect);

}

WinMenuState* WinMenuState::GetInstance() 
{
	static WinMenuState s_Instance;

	return &s_Instance;
}

