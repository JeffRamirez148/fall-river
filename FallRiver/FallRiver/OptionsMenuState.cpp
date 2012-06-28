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
	musicID = -1;
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

	m_nOptionID = m_pVM->RegisterTexture("resource/graphics/bg_options.png");
	m_nFontID	= m_pVM->RegisterFont("resource/graphics/FallRiver_0.png");

	FMOD_VECTOR tmp = {0,0,0};
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	m_pAM->SetListenerPos(tmp);
	soundID = m_pAM->RegisterSound("resource/Sounds/KCJ_MenuClick.wav");
	m_pAM->setSoundPos(soundID, sound1);

	m_pAM->setSoundVel(soundID, tmp);
	m_pAM->setSoundLooping(soundID, false);

	musicID = m_pAM->registerMusic("resource/Sounds/shot.mp3");
	m_pAM->setMusicPos(musicID, sound1);

	m_pAM->setMusicVel(musicID, tmp);
	m_pAM->setMusicLooping(musicID, true);
	m_pAM->playMusic(musicID);

	m_bIsWindowed = CGame::GetInstance()->IsWindowed();

	musicVolume = m_pAM->getMusicVolume();
	sfxVolume = m_pAM->getSoundVolume();
}

void OptionsMenuState::Exit() 
{
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

	sfxVolume = m_pAM->getSoundVolume();
	musicVolume = m_pAM->getMusicVolume();

	if( m_pDI->KeyPressed(DIK_RIGHT) )
	{
		if( m_nCursPosY == 200 && sfxVolume < 1.0f)
		{
			sfxVolume += 0.05f;
			if(sfxVolume > 1)
				sfxVolume = 1;
			m_pAM->playSound(soundID);
		}
		else if( m_nCursPosY == 225 && musicVolume < 1.0f)
		{
			musicVolume += 0.05f;
			if(musicVolume > 1)
				musicVolume = 1;
			m_pAM->playSound(soundID);
		}
	}
	else if( m_pDI->KeyPressed(DIK_LEFT) )
	{
		if( m_nCursPosY == 200 && sfxVolume > 0.0f)
		{
			sfxVolume -= 0.05f;
			if(sfxVolume < 0)
				sfxVolume = 0;
			m_pAM->playSound(soundID);
		}
		else if( m_nCursPosY == 225 && musicVolume > 0.0f)
		{
			musicVolume -= 0.05f;
			if(musicVolume < 0)
				musicVolume = 0;
			m_pAM->playSound(soundID);
		}
	}

	m_pAM->setMusicVolume(musicVolume);
	m_pAM->setSoundVolume(sfxVolume);


	if( m_pDI->KeyPressed(DIK_RETURN) )
	{
		if( m_nCursPosY == 250 )
		{
			m_bIsWindowed = !m_bIsWindowed;
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

	//m_pVM->DrawStaticTexture(m_nOptionID, 0, 0,  0.4f, 0.6f);

	m_pVM->GetSprite()->Flush();
	m_pVM->Clear();

	m_pVM->DrawFont(m_nFontID, "OPTIONS", 100, 100, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255,255));

	RECT cursRect= { 275, m_nCursPosY, 285, m_nCursPosY+10 };
	m_pVM->DrawRect( cursRect, 255, 0, 0 );

	char buff[100];

	_itoa_s(int(sfxVolume*100), buff, 10);
	m_pVM->DrawFont(m_nFontID, "Sound fx Volume", 300, 200);
	m_pVM->DrawFont(m_nFontID, buff, 600, 200);

	_itoa_s(int(musicVolume*100), buff, 10);
	m_pVM->DrawFont(m_nFontID, "Music Volume", 300, 225);
	m_pVM->DrawFont(m_nFontID,buff, 600, 225);

	m_pVM->DrawFont(m_nFontID, "Full Screen", 300, 250);

	RECT check = { 600, 250, 630, 280 };

	if( !m_bIsWindowed )
		m_pVM->DrawRect(check, 0, 200, 255);
	else
		m_pVM->DrawUnfilledRect(check, 0, 200, 255);
	

	m_pVM->DrawFont(m_nFontID, "Exit", 300, 300);
}

