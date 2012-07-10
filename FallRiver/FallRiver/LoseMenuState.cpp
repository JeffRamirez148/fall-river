#include <Windows.h>

#include "LoseMenuState.h"
#include "WinMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "XMLManager.h"
#include "IMenuState.h"
#include "CGame.h"
#include "GamePlayState.h"
#include "LoadMenuState.h"
#include "MainMenuState.h"

using namespace std;

LoseMenuState* LoseMenuState::GetInstance()
{
	static LoseMenuState s_Instance;

	return &s_Instance;
}
void LoseMenuState::Enter()
{
	pVM = ViewManager::GetInstance();
	pDI = DirectInput::GetInstance();

	LMS_ID =	pVM->RegisterTexture("resource/graphics/youLose.png");
	tempLoseID = pVM->RegisterTexture("resource/graphics/sprites_pauseMenu.png");
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

void LoseMenuState::ReEnter()
{
	audio->playMusic(musicID);
}

void LoseMenuState::Exit()
{
	pVM	= nullptr;
	pDI	= nullptr;
	audio	= nullptr;

	GamePlayState::GetInstance()->SetWinLose(true);
}
bool LoseMenuState::Input()
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
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->ChangeState(LoadMenuState::GetInstance());
			//CGame::GetInstance()->ChangeState(LoadMenuState::GetInstance());
		}
		else if( curPos == 300 )
		{
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->ChangeState(MainMenuState::GetInstance());
		
		}
	}
	return true;
}
void LoseMenuState::Update(float aFElapsedTime)
{

}
void LoseMenuState::Render()
{
	pVM->GetSprite()->Flush();
	pVM->Clear();
	RECT backRect = { 0, 0,1024, 1024};
	pVM->DrawStaticTexture(LMS_ID, 0, 0,  0.8f, 0.5f, &backRect);

	/*RECT resumeRect = {1219, 13, resumeRect.left+287, resumeRect.top+44};
	RECT saveRect = { 1219, 83, saveRect.left+287, saveRect.top+44};
	RECT optionsRect = {1219, 153, optionsRect.left+287, optionsRect.top+44};
	RECT ExitRect = {1219, 223, ExitRect.left+287, ExitRect.top+44};

	if(curPos == 150)
	{resumeRect.left = 1535; resumeRect.right = resumeRect.left+287;}
	else if(curPos == 200)
	{saveRect.left = 1535; saveRect.right = saveRect.left+287;}
	else if(curPos == 250)
	{optionsRect.left = 1535; optionsRect.right = optionsRect.left+287;}
	else if(curPos == 300)
	{ExitRect.left = 1535; ExitRect.right = ExitRect.left+287;}

	pVM->DrawStaticTexture(tempLoseID, 320, 200,  0.7f, 0.9f, &resumeRect);
	pVM->DrawStaticTexture(tempLoseID, 330, 300,  0.7f, 0.9f, &saveRect);
	pVM->DrawStaticTexture(tempLoseID, 350, 400,  0.7f, 0.9f, &optionsRect);
	pVM->DrawStaticTexture(tempLoseID, 370, 500,  0.7f, 0.9f, &ExitRect);*/

	RECT resumeRect = {1219, 13, resumeRect.left+287, resumeRect.top+44};
	RECT ExitRect = {1219, 223, ExitRect.left+287, ExitRect.top+44};

	if(curPos == 250)
	{resumeRect.left = 1535; resumeRect.right = resumeRect.left+287;}
	else if(curPos == 300)
	{ExitRect.left = 1535; ExitRect.right = ExitRect.left+287;}

	pVM->DrawStaticTexture(tempLoseID, 350, 400,  0.5f, 0.9f, &resumeRect);
	pVM->DrawStaticTexture(tempLoseID, 370, 500,  0.5f, 0.9f, &ExitRect);
}
	