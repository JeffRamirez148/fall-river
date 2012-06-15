#include "OptionsMenuState.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "CGame.h"
#include "ViewManager.h"
#include "IMenuState.h"

OptionsMenuState::OptionsMenuState()
{
	m_nCursPosY = 200;
	m_pAM = nullptr;
	musicVolume = 1.0f;
	sfxVolume = 1.0f;
	m_bIsWindowed = false;
	changingres = false;

	possRes[0] = 640;
	possRes[1] = 480;
	possRes[2] = 1280;
	possRes[3] = 1204;
}

OptionsMenuState::~OptionsMenuState()
{

}

OptionsMenuState* OptionsMenuState::GetInstance() 
{
	static OptionsMenuState stuff;

	return &stuff;
}

void OptionsMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();
	m_pAM = AudioManager::GetInstance();

	resolution[0] = CGame::GetInstance()->GetScreenWidth();
	resolution[1] = CGame::GetInstance()->GetScreenHeight();
	m_bIsWindowed = CGame::GetInstance()->IsWindowed();

	m_pAM->setMusicVolume(1.0f);
	m_pAM->setSoundVolume(1.0f);
}

void OptionsMenuState::Exit() 
{
	m_pVM = nullptr;
	m_pDI = nullptr;
	m_pAM = nullptr;
	changingres = false;
	m_nCursPosY = 200;
}

bool OptionsMenuState::Input()
{
	if( m_pDI->KeyPressed(DIK_DOWN) && !changingres )
	{
		m_nCursPosY += 25;
		if(m_nCursPosY == 275)
			m_nCursPosY += 25;
		if( m_nCursPosY > 300 )
			m_nCursPosY = 200;
	}
	else if( m_pDI->KeyPressed(DIK_UP) && !changingres )
	{
		m_nCursPosY -= 25;
		if(m_nCursPosY == 275)
			m_nCursPosY -= 25;
		if( m_nCursPosY < 200 )
			m_nCursPosY = 300;
	}

	if( changingres )
	{
		if(m_pDI->KeyPressed(DIK_RIGHT))
		{
			if(resolution[0] == possRes[2] )
			{
				resolution[0] = possRes[0];
				resolution[1] = possRes[1];
			}
			else
			{
				resolution[0] = possRes[2];
				resolution[1] = possRes[3];
			}
		}
	}

	if( m_pDI->KeyPressed(DIK_RETURN) )
	{
		if( m_nCursPosY == 250 && !changingres )
			changingres = true;
		else if( m_nCursPosY == 250 && changingres )
		{
			m_pVM->ChangeDisplayParam(resolution[0], resolution[1], m_bIsWindowed);
			changingres = false;
		}
		else if( m_nCursPosY == 300 )
			CGame::GetInstance()->RemoveState();
		return true;
	}

	// Pressing Escape will End the Game
	if( m_pDI->KeyPressed(DIK_ESCAPE) )
		m_nCursPosY = 300;

	return true;
}

void OptionsMenuState::Update(float fElapsedTime)
{
	if( m_pDI->KeyDown(DIK_RIGHT) )
	{
		if( m_nCursPosY == 200 && sfxVolume < 1.0f)
			sfxVolume += 0.1f*fElapsedTime;
		else if( m_nCursPosY == 225 && musicVolume < 1.0f)
			musicVolume += 0.1f*fElapsedTime;
	}
	else if( m_pDI->KeyDown(DIK_LEFT) )
	{
		if( m_nCursPosY == 200 && sfxVolume > 0.0f)
			sfxVolume -= 0.1f*fElapsedTime;
		else if( m_nCursPosY == 225 && musicVolume > 0.0f)
			musicVolume -= 0.1f*fElapsedTime;
	}

	m_pAM->setMusicVolume(musicVolume);
	m_pAM->setSoundVolume(sfxVolume);
}

void OptionsMenuState::Render()
{
	// Do Rendering Here

	m_pVM->DrawTextW("OPTIONS", 100, 100, 255, 0, 0);

	RECT cursRect= { 275, m_nCursPosY, 285, m_nCursPosY+10 };
	m_pVM->DrawRect( cursRect, 255, 0, 0 );

	char buff[100];

	itoa(sfxVolume*100, buff, 10);
	m_pVM->DrawTextW("Sound fx Volume", 300, 200, 255, 255, 0);
	m_pVM->DrawTextW(buff, 450, 200, 255, 255, 255);

	itoa(musicVolume*100, buff, 10);
	m_pVM->DrawTextW("Music Volume", 300, 225, 255, 255, 0);
	m_pVM->DrawTextW(buff, 450, 225, 255, 255, 255);

	m_pVM->DrawTextW("Set Screen Resolution", 300, 250, 255, 255, 0);

	itoa(resolution[0], buff, 10);
	m_pVM->DrawTextW(buff, 450, 250, 255, 255, 255);
	m_pVM->DrawTextW(" x ", 480, 250, 255, 255, 255);
	itoa(resolution[1], buff, 10);
	m_pVM->DrawTextW(buff, 500, 250, 255, 255, 255);

	m_pVM->DrawTextW("Exit", 300, 300, 255, 255, 0);
}

