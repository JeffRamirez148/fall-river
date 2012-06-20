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
	musicVolume = 0.10f;
	sfxVolume = 0.10f;
	m_bIsWindowed = false;
	m_nOptionID = -1;
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

	soundID = m_pAM->registerMusic("KCJ_MenuClick.wav");
	m_nOptionID = m_pVM->RegisterTexture("resource/graphics/bg_options.png");

	m_pAM->setMusicLooping(soundID, true);

	m_bIsWindowed = CGame::GetInstance()->IsWindowed();

	musicVolume = m_pAM->getMusicVolume();
	sfxVolume = m_pAM->getSoundVolume();

	m_pAM->playMusic(soundID);
}

void OptionsMenuState::Exit() 
{
	m_pAM->setMusicLooping(soundID, false);
	m_pAM->toggleMuteMusic();
	m_pVM = nullptr;
	m_pDI = nullptr;
	m_pAM = nullptr;
	m_nCursPosY = 200;
}

bool OptionsMenuState::Input()
{
	if( m_pDI->KeyPressed(DIK_DOWN) )
	{
		m_nCursPosY += 25;
		if(m_nCursPosY == 275)
			m_nCursPosY += 25;
		if( m_nCursPosY > 300 )
			m_nCursPosY = 200;
	}
	else if( m_pDI->KeyPressed(DIK_UP) )
	{
		m_nCursPosY -= 25;
		if(m_nCursPosY == 275)
			m_nCursPosY -= 25;
		if( m_nCursPosY < 200 )
			m_nCursPosY = 300;
	}

	if( m_pDI->KeyDown(DIK_RIGHT) )
	{
		if( m_nCursPosY == 200 && sfxVolume < 1.0f)
			sfxVolume += 0.1f;
		else if( m_nCursPosY == 225 && musicVolume < 1.0f)
			musicVolume += 0.1f;
	}
	else if( m_pDI->KeyDown(DIK_LEFT) )
	{
		if( m_nCursPosY == 200 && sfxVolume > 0.0f)
			sfxVolume -= 0.1f;
		else if( m_nCursPosY == 225 && musicVolume > 0.0f)
			musicVolume -= 0.1f;
	}

	m_pAM->setMusicVolume(musicVolume);
	m_pAM->setSoundVolume(sfxVolume);


	if( m_pDI->KeyPressed(DIK_RETURN) )
	{
		if( m_nCursPosY == 250 )
		{
			m_bIsWindowed = !m_bIsWindowed;
			m_pVM->ChangeDisplayParam(CGame::GetInstance()->GetScreenWidth(), CGame::GetInstance()->GetScreenHeight(), m_bIsWindowed);
			CGame::GetInstance()->SetWindowed(m_bIsWindowed);
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
}

void OptionsMenuState::Render()
{
	// Do Rendering Here

	m_pVM->DrawStaticTexture(m_nOptionID, 0, 0, 0.33f, 0.5f);

	m_pVM->GetSprite()->Flush();

	m_pVM->DrawTextW("OPTIONS", 100, 100, 255, 0, 0);

	RECT cursRect= { 275, m_nCursPosY, 285, m_nCursPosY+10 };
	m_pVM->DrawRect( cursRect, 255, 0, 0 );

	char buff[100];

	_itoa_s(int(sfxVolume*100), buff, 10);
	m_pVM->DrawTextW("Sound fx Volume", 300, 200, 255, 255, 0);
	m_pVM->DrawTextW(buff, 450, 200, 255, 255, 255);

	_itoa_s(int(musicVolume*100), buff, 10);
	m_pVM->DrawTextW("Music Volume", 300, 225, 255, 255, 0);
	m_pVM->DrawTextW(buff, 450, 225, 255, 255, 255);

	m_pVM->DrawTextW("Full Screen", 300, 250, 255, 255, 0);

	RECT check = { 450, 250, 460, 260 };

	if( !m_bIsWindowed )
		m_pVM->DrawRect(check, 0, 200, 255);
	else
		m_pVM->DrawUnfilledRect(check, 0, 200, 255);
	

	m_pVM->DrawTextW("Exit", 300, 300, 255, 255, 0);
}

