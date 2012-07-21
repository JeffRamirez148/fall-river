#include "PauseMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "XMLManager.h"
#include "DirectInput.h"
#include "OptionsMenuState.h"
#include "SaveMenuState.h"
#include "XMLManager.h"
#include "CGame.h"
#include "MainMenuState.h"

PauseMenuState::PauseMenuState()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nPauseID = -1;
	m_nCursPosY = 200;
}

PauseMenuState::~PauseMenuState()
{

}

PauseMenuState* PauseMenuState::GetInstance() 
{
	static PauseMenuState m_sInstance;

	return &m_sInstance;
}

void PauseMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();

	m_nPauseID = m_pVM->RegisterTexture("resource/graphics/sprites_pauseMenu.png");
	m_pVM->SetAmbientLight(0,0,.1f);

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

//	musicID = audio->registerMusic("resource/Sounds/rainroof.wav");
//	audio->setMusicPos(musicID, sound1);

//	audio->setMusicVel(musicID, tmp);
//	audio->setMusicLooping(musicID, true);
//	audio->playMusic(musicID);

//	musicID2 = audio->registerMusic("resource/Sounds/background.mp3");
//	audio->setMusicPos(musicID2, sound1);

//	audio->setMusicVel(musicID2, tmp);
//	audio->setMusicLooping(musicID2, true);
//	audio->playMusic(musicID2);

}

void PauseMenuState::ReEnter()
{
//	audio->playMusic(musicID);
//	audio->playMusic(musicID2);
}

void PauseMenuState::Exit()
{
	m_pVM->SetAmbientLight(1,1,1);

	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nCursPosY = 200;
}

bool PauseMenuState::Input() 
{
	if( m_pDI->KeyPressed(DIK_DOWN) || m_pDI->KeyPressed(DIK_S) || m_pDI->JoystickGetLStickDirPressed(DIR_DOWN,0))
	{
		m_nCursPosY += 100;
		if( m_nCursPosY > 500 )
			m_nCursPosY = 200;
		audio->playSound(soundID);
	}
	else if( m_pDI->KeyPressed(DIK_UP) || m_pDI->KeyPressed(DIK_W) || m_pDI->JoystickGetLStickDirPressed(DIR_UP,0) )
	{
		m_nCursPosY -= 100;
		if( m_nCursPosY < 200 )
			m_nCursPosY = 500;
		audio->playSound(soundID);
	}

	if( m_pDI->KeyPressed(DIK_RETURN)  || m_pDI->JoystickButtonPressed(0,0))
	{
		audio->playSound(soundID);
		if( m_nCursPosY == 200 )
			CGame::GetInstance()->RemoveState();
		else if(m_nCursPosY == 300)
			CGame::GetInstance()->ChangeState(SaveMenuState::GetInstance());
		else if( m_nCursPosY == 400 )
			CGame::GetInstance()->ChangeState(OptionsMenuState::GetInstance());
		else if( m_nCursPosY == 500 )
		{
			CGame::GetInstance()->RemoveState(2);
			CGame::GetInstance()->ChangeState(MainMenuState::GetInstance());
		}

		return true;
	}

	if( m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1,0) )
	{
		audio->playSound(soundID);
		m_nCursPosY = 500;
	}

	return true;
}

void PauseMenuState::Update(float fElapsedTime) 
{

}

void PauseMenuState::Render() 
{
	//526 x 144
	// Do Rendering here
	RECT backRect = { 12, 12, backRect.left+1200, backRect.top+700};
	m_pVM->DrawStaticTexture(m_nPauseID, 0, 0,  0.7f, 0.9f, &backRect);

	RECT resumeRect = {1219, 13, resumeRect.left+287, resumeRect.top+44};
	RECT saveRect = { 1219, 83, saveRect.left+287, saveRect.top+44};
	RECT optionsRect = {1219, 153, optionsRect.left+287, optionsRect.top+44};
	RECT ExitRect = {1219, 223, ExitRect.left+287, ExitRect.top+44};
	RECT BloodRect = { 343, 789, BloodRect.left+526, BloodRect.top+144};

	if(m_nCursPosY == 200)
	{resumeRect.left = 1535; resumeRect.right = resumeRect.left+287;}
	else if(m_nCursPosY == 300)
	{saveRect.left = 1535; saveRect.right = saveRect.left+287;}
	else if(m_nCursPosY == 400)
	{optionsRect.left = 1535; optionsRect.right = optionsRect.left+287;}
	else if(m_nCursPosY == 500)
	{ExitRect.left = 1535; ExitRect.right = ExitRect.left+287;}

	m_pVM->DrawStaticTexture(m_nPauseID, (float)170, m_nCursPosY-50, 1.0f, 1.0f, &BloodRect);

	m_pVM->DrawStaticTexture(m_nPauseID, (float)320, (float)200,  0.7f, 0.9f, &resumeRect);
	m_pVM->DrawStaticTexture(m_nPauseID, (float)330, (float)300,  0.7f, 0.9f, &saveRect);
	m_pVM->DrawStaticTexture(m_nPauseID, (float)350, (float)400,  0.7f, 0.9f, &optionsRect);
	m_pVM->DrawStaticTexture(m_nPauseID, (float)370, (float)500,  0.7f, 0.9f, &ExitRect);

	//RECT cRect = { 100, 100, 500, 400 };
	//RECT cursRect = { 225, m_nCursPosY, 235, m_nCursPosY+10 };
	//m_pVM->DrawRect(cRect, 100, 100, 100, 255);
	//m_pVM->DrawRect(cursRect, 255, 0, 0);

	//m_pVM->DrawTextW("Resume", 250, 150, 255, 255, 0);
	//m_pVM->DrawTextW("Save Game", 250, 200, 255, 255, 0);
	//m_pVM->DrawTextW("Optons", 250, 250, 255, 255, 0);
	//m_pVM->DrawTextW("Back To Main Menu", 250, 300, 255, 255, 0);
}

