#include "SaveMenuState.h"
#include "XMLManager.h"
#include "DirectInput.h"
#include "CGame.h"
#include "GamePlayState.h"
#include "ViewManager.h"
#include "AudioManager.h"

SaveMenuState* SaveMenuState::GetInstance()
{
	static SaveMenuState m_sInstance;

	return &m_sInstance;
}

SaveMenuState::SaveMenuState(void)
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nCursPosY = 0;
	m_nCursPosX = 0;
	m_nFontID	= 0;
	m_bSure = false;
	m_bCheck = false;
}


SaveMenuState::~SaveMenuState(void)
{
}

void SaveMenuState::Enter()
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();

	m_nFontID = m_pVM->RegisterFont("resource/graphics/FallRiver_0.png");

	m_nCursPosY = 200;
	m_nCursPosX = 280;
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

void SaveMenuState::ReEnter()
{
	audio->playMusic(musicID);
	audio->playMusic(musicID2);
}

void SaveMenuState::Exit()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nCursPosY = 0;
	m_nCursPosX = 0;
	m_bSure = false;
	m_bCheck = false;
}

bool SaveMenuState::Input()
{
	if( m_pDI->KeyPressed(DIK_S) || m_pDI->JoystickGetLStickDirPressed(DIR_DOWN,0))
	{
		m_nCursPosY += 50;
		if( m_nCursPosY == 350 )
			m_nCursPosY = 400;
		else if( m_nCursPosY > 400 )
			m_nCursPosY = 200;
		audio->playSound(soundID);
	}
	else if( m_pDI->KeyPressed(DIK_W) || m_pDI->JoystickGetLStickDirPressed(DIR_UP,0) )
	{
		m_nCursPosY -= 50;
		if( m_nCursPosY == 350 )
			m_nCursPosY = 300;
		else if( m_nCursPosY < 200 )
			m_nCursPosY = 400;
		audio->playSound(soundID);
	}

	if( (m_pDI->KeyPressed(DIK_D) && m_bCheck) || (m_pDI->JoystickGetLStickDirPressed(DIR_RIGHT,0) && m_bCheck) )
	{
		m_nCursPosX += 100;
		if( m_nCursPosX > 380 )
			m_nCursPosX = 280;
		audio->playSound(soundID);
	}
	else if( (m_pDI->KeyPressed(DIK_A) && m_bCheck) || (m_pDI->JoystickGetLStickDirPressed(DIR_RIGHT,0) && m_bCheck) )
	{
		m_nCursPosX -= 100;
		if( m_nCursPosX < 280 )
			m_nCursPosX = 380;
		audio->playSound(soundID);
	}

	if(m_pDI->KeyPressed(DIK_RETURN) || m_pDI->JoystickButtonPressed(0,0))
	{
		audio->playSound(soundID);
		if(m_bCheck)
		{
			if(m_nCursPosX == 280)
			{
				m_bSure = true;
				m_bCheck = false;
			}
			else if(m_nCursPosX == 380)
			{
				m_bCheck = false;
				m_bSure = false;
				return true;
			}
		}

		if( m_nCursPosY == 200 )
		{
			if( XMLManager::GetInstance()->CheckSlot("save1.xml") && !m_bSure ) 
				m_bCheck = true;
			else
			{
				XMLManager::GetInstance()->SaveProgress("save1.xml", *GamePlayState::GetInstance()->GetPlayer());
				CGame::GetInstance()->RemoveState();
				m_bSure = false;
			}
		}
		else if(m_nCursPosY == 250)
		{
			if( XMLManager::GetInstance()->CheckSlot("save2.xml") && !m_bSure ) 
				m_bCheck = true;
			else
			{
				XMLManager::GetInstance()->SaveProgress("save2.xml", *GamePlayState::GetInstance()->GetPlayer());
				CGame::GetInstance()->RemoveState();
			}
		}
		else if( m_nCursPosY == 300 )
		{
			if( XMLManager::GetInstance()->CheckSlot("save3.xml") && !m_bSure ) 
				m_bCheck = true;
			else
			{
				XMLManager::GetInstance()->SaveProgress("save3.xml", *GamePlayState::GetInstance()->GetPlayer());
				CGame::GetInstance()->RemoveState();
			}
		}
		else if( m_nCursPosY == 400 )
			CGame::GetInstance()->RemoveState();

		return true;
	}

	if((m_pDI->KeyDown(DIK_ESCAPE) && !m_bCheck ) ||  (m_pDI->JoystickButtonPressed(1,0) && !m_bCheck))
	{
		audio->playSound(soundID);
		CGame::GetInstance()->RemoveState();
	}

	return true;
}

void SaveMenuState::Update(float fElapsedTime)
{

}

void SaveMenuState::Render()
{

	m_pVM->GetSprite()->Flush();
	m_pVM->Clear();

	m_pVM->DrawFont(m_nFontID, "Save Progress", 20, 20);

	if( m_bCheck )
	{
		RECT cRect = {200, 200, 600, 350};

		m_pVM->DrawRect(cRect, 0, 100, 100, 100);

		m_pVM->DrawFont(m_nFontID, "You are about to overwrite a previous save...", 200, 200, 0.5f, 0.5f);
		m_pVM->DrawFont(m_nFontID, "Do you want to continue", 260, 220, 0.5f, 0.5f);
		m_pVM->DrawFont(m_nFontID, "Yes", 300, 280, 0.5f, 0.5f);
		m_pVM->DrawFont(m_nFontID, "No", 400, 280, 0.5f, 0.5f);

		RECT xRect = {m_nCursPosX, 280, m_nCursPosX+10, 290};

		m_pVM->DrawRect(xRect, 0, 255, 255, 100);
	}
	else
	{
		m_pVM->DrawFont(m_nFontID, "Save 1", 250, 200);
		m_pVM->DrawFont(m_nFontID, "Save 2", 250, 250);
		m_pVM->DrawFont(m_nFontID, "Save 3", 250, 300);
		m_pVM->DrawFont(m_nFontID, "Exit Game", 300, 400);

		RECT rRect = {225, m_nCursPosY, 235, m_nCursPosY+10};

		m_pVM->DrawRect(rRect, 0, 255, 255, 100);
	}
}
