#include "OptionsMenuState.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "CGame.h"
#include "ViewManager.h"
#include "IMenuState.h"
#include "XMLManager.h"

OptionsMenuState::OptionsMenuState()
{
	m_nCursPosY = 200;
	m_pAM = nullptr;
	musicVolume = 0.10f;
	sfxVolume = 0.10f;
	m_bIsWindowed = false;
	m_nOptionID = -1;
	musicID = -1;
	soundID = -1;
	m_nOptionSpriteID = -1;
	m_nSelection = 1;

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
	m_nOptionSpriteID = m_pVM->RegisterFont("resource/graphics/sprites_options.png");

	FMOD_VECTOR tmp = {0,0,0};
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	m_pAM->SetListenerPos(tmp);
	soundID = m_pAM->RegisterSound("resource/Sounds/KCJ_MenuClick.wav");
	m_pAM->setSoundPos(soundID, sound1);

	m_pAM->setSoundVel(soundID, tmp);
	m_pAM->setSoundLooping(soundID, false);

	soundID2 = m_pAM->RegisterSound("resource/Sounds/thunder.wav");
	m_pAM->setSoundPos(soundID2, sound1);

	m_pAM->setSoundVel(soundID2, tmp);
	m_pAM->setSoundLooping(soundID2, false);

	musicID = m_pAM->registerMusic("resource/Sounds/rainroof.wav");
	m_pAM->setMusicPos(musicID, sound1);

	m_pAM->setMusicVel(musicID, tmp);
	m_pAM->setMusicLooping(musicID, true);
	m_pAM->playMusic(musicID);

	musicID2 = m_pAM->registerMusic("resource/Sounds/background.mp3");
	m_pAM->setMusicPos(musicID2, sound1);

	m_pAM->setMusicVel(musicID2, tmp);
	m_pAM->setMusicLooping(musicID2, true);
	m_pAM->playMusic(musicID2);

	m_bIsWindowed = CGame::GetInstance()->IsWindowed();

	musicVolume = m_pAM->getMusicVolume();
	sfxVolume = m_pAM->getSoundVolume();
}

void OptionsMenuState::ReEnter()
{
	m_pAM->playMusic(musicID);
	m_pAM->playMusic(musicID2);
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
	if( m_pDI->KeyPressed(DIK_DOWN) || m_pDI->JoystickGetLStickDirPressed(DIR_DOWN,0))
	{
		m_pAM->playSound(soundID);
		//m_nCursPosY += 25;
		--m_nSelection;
		if(m_nSelection < 0)
			m_nSelection = 3;
		
	}
	else if( m_pDI->KeyPressed(DIK_UP) || m_pDI->JoystickGetLStickDirPressed(DIR_UP,0) )
	{
		m_pAM->playSound(soundID);
		//m_nCursPosY -= 25;
		++m_nSelection;
		if(m_nSelection > 3)
			m_nSelection = 0;
	}

	sfxVolume = m_pAM->getSoundVolume();
	musicVolume = m_pAM->getMusicVolume();

	if( m_pDI->KeyPressed(DIK_RIGHT) || m_pDI->JoystickGetLStickDirPressed(DIR_RIGHT,0))
	{
		m_pAM->playSound(soundID);
		if( m_nSelection == 1 && sfxVolume < 1.0f)
		{
			sfxVolume += 0.05f;
			if(sfxVolume > 1)
				sfxVolume = 1;
		}
		else if(m_nSelection == 2 && musicVolume < 1.0f)
		{
			musicVolume += 0.05f;
			if(musicVolume > 1)
				musicVolume = 1;
		}
	}
	else if( m_pDI->KeyPressed(DIK_LEFT) || m_pDI->JoystickGetLStickDirPressed(DIR_LEFT,0))
	{
		m_pAM->playSound(soundID);
		if(m_nSelection == 1 && sfxVolume > 0.0f)
		{
			sfxVolume -= 0.05f;
			if(sfxVolume < 0)
				sfxVolume = 0;
		}
		else if( m_nSelection == 2 && musicVolume > 0.0f)
		{
			musicVolume -= 0.05f;
			if(musicVolume < 0)
				musicVolume = 0;
		}
	}

	m_pAM->setMusicVolume(musicVolume);
	m_pAM->setSoundVolume(sfxVolume);


	if( m_pDI->KeyPressed(DIK_RETURN)  || m_pDI->JoystickButtonPressed(0,0))
	{
		if( m_nSelection == 3 )
		{
			m_bIsWindowed = !m_bIsWindowed;
			CGame::GetInstance()->SetWindowed(m_bIsWindowed);
		}
		else if( m_nSelection == 0 )
		{
			vector<int> volume;
			volume.push_back(int(musicVolume*100.0f));
			volume.push_back(int(sfxVolume*100.0f));
			if( CGame::GetInstance()->IsWindowed() == true )
			{
				volume.push_back(1);
			}
			else
			{
				volume.push_back(0);
			}

			XMLManager::GetInstance()->SaveSettings( "settings.xml", volume);
			CGame::GetInstance()->RemoveState();
		}
		return true;
	}

	// Pressing Escape will End the Game
	if( m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1,0) )
		m_nSelection = 0;

	return true;
}

void OptionsMenuState::Update(float fElapsedTime)
{
}

void OptionsMenuState::Render()
{
	// Do Rendering Here

	RECT src_NotPressed = {16,40,72,16};
	RECT src_Pressed = {74,40,110,16};
	RECT src_PowerNotPressed = {160,55,200,16};
	RECT src_PowerPressed = {220,55,260,16};
	RECT src_SFX = {238,93,263,80};
	RECT src_Music = {225,128,264,115};
	RECT src_Res = {188,164,264,150};
	RECT src_Exit = {234,201,262,187};
	m_pVM->DrawStaticTexture(m_nOptionID, 0, 0,  0.4f, 0.6f);

	// image 1280x1024
	// screen 800x600
	// ratio 1.6 : 1.7

	// Exit Buttons
	if( m_nSelection == 0)
	{
		m_pVM->DrawFont(m_nFontID,"Exit",386.5f,200.8f,0.8f,0.8f,0,0,0,D3DCOLOR_ARGB(255,0,255,0));
	}
	
	m_pVM->DrawStaticTexture(m_nOptionSpriteID,402.875f,98.0f,0.7f,0.7f,&src_Exit);
	m_pVM->DrawStaticTexture(m_nOptionSpriteID,400,85.3f,0.6f,0.6f,&src_PowerNotPressed);

	// SFX Buttons
	m_pVM->DrawStaticTexture(m_nOptionSpriteID,352.875f,125,0.7f,0.7f,&src_SFX);

	m_pVM->DrawStaticTexture(m_nOptionSpriteID,385,130,0.6f,0.6f,&src_NotPressed,0,0,-(3.14f/2));
	m_pVM->DrawStaticTexture(m_nOptionSpriteID,388,107.5,0.6f,0.6f,&src_NotPressed,0,0,3.14f/2);

	if( m_nSelection == 1)
	{
		m_pVM->DrawFont(m_nFontID,"SFX",386.5f,185.8f,0.8f,0.8f,0,0,0,D3DCOLOR_ARGB(255,0,255,0));
		char buff[100];
		_itoa_s(int(sfxVolume*100), buff, 10);
		m_pVM->DrawFont(m_nFontID, buff, 386.5f, 205.8f);

		
		if( m_pDI->KeyDown(DIK_A) || m_pDI->JoystickGetLStickDirDown(DIR_LEFT,0))
		{
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,385,130,0.6f,0.6f,&src_Pressed,0,0,-(3.14f/2));			
		}
		else
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,385,130,0.6f,0.6f,&src_NotPressed,0,0,-(3.14f/2));

		if( m_pDI->KeyDown(DIK_D) || m_pDI->JoystickGetLStickDirDown(DIR_RIGHT,0))
		{
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,388,107.5,0.6f,0.6f,&src_Pressed,0,0,3.14f/2);
		}
		else
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,388,107.5,0.6f,0.6f,&src_NotPressed,0,0,3.14f/2);
		
		
	}
	
	
	
	// Music Buttons
	m_pVM->DrawStaticTexture(m_nOptionSpriteID,402.875f,125,0.7f,0.7f,&src_Music);
	m_pVM->DrawStaticTexture(m_nOptionSpriteID,453,130,0.6f,0.6f,&src_NotPressed,0,0,-(3.14f/2));
	m_pVM->DrawStaticTexture(m_nOptionSpriteID,456,107.5,0.6f,0.6f,&src_NotPressed,0,0,3.14f/2);
	if( m_nSelection == 2)
	{
		m_pVM->DrawFont(m_nFontID,"Music",376.5f,185.8f,0.8f,0.8f,0,0,0,D3DCOLOR_ARGB(255,0,255,0));
		char buff[100];
		_itoa_s(int(musicVolume*100), buff, 10);
		m_pVM->DrawFont(m_nFontID, buff, 376.5f, 205.8f);

		if( m_pDI->KeyDown(DIK_A) || m_pDI->JoystickGetLStickDirDown(DIR_LEFT,0))
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,453,130,0.6f,0.6f,&src_Pressed,0,0,-(3.14f/2));
		else
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,453,130,0.6f,0.6f,&src_NotPressed,0,0,-(3.14f/2));

		if( m_pDI->KeyDown(DIK_D) || m_pDI->JoystickGetLStickDirDown(DIR_RIGHT,0))
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,456.555f,107.5,0.6f,0.6f,&src_Pressed,0,0,3.14f/2);
		else
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,456.555f,107.5,0.6f,0.6f,&src_NotPressed,0,0,3.14f/2);
	}
	
	
	
	// Resolution Buttons
	m_pVM->DrawStaticTexture(m_nOptionSpriteID,350.875f,160,0.7f,0.7f,&src_Res);

	m_pVM->DrawStaticTexture(m_nOptionSpriteID,419.555f,164.5,0.6f,0.6f,&src_NotPressed,0,0,-(3.14f/2));
	m_pVM->DrawStaticTexture(m_nOptionSpriteID,420.555f,143,0.6f,0.6f,&src_NotPressed,0,0,3.14f/2);

	if( m_nSelection == 3)
	{
		m_pVM->DrawFont(m_nFontID,"Resolution",346.5f,185.8f,0.7f,0.7f,0,0,0,D3DCOLOR_ARGB(255,0,255,0));

		if(m_bIsWindowed)
			m_pVM->DrawFont(m_nFontID, "FullScreen Off", 346.5f, 215.8f,0.5f,0.5f);
		else
			m_pVM->DrawFont(m_nFontID, "FullScreen On", 346.5f, 215.8f,0.5f,0.5f);

		if( m_pDI->KeyDown(DIK_A) || m_pDI->JoystickGetLStickDirDown(DIR_LEFT,0))
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,419.555f,164.5,0.6f,0.6f,&src_Pressed,0,0,-(3.14f/2));
		else
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,419.555f,164.5,0.6f,0.6f,&src_NotPressed,0,0,-(3.14f/2));

		if( m_pDI->KeyDown(DIK_D) || m_pDI->JoystickGetLStickDirDown(DIR_RIGHT,0))
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,420.555f,143,0.6f,0.6f,&src_Pressed,0,0,3.14f/2);
		else
			m_pVM->DrawStaticTexture(m_nOptionSpriteID,420.555f,143,0.6f,0.6f,&src_NotPressed,0,0,3.14f/2);

	}
	
	
	//m_pVM->DrawStaticTexture(m_nOptionSpriteID,450,105,1.0f,1.0f,&src_Pressed);

	//////m_pVM->DrawFont(m_nFontID, "OPTIONS", 100, 100, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255,255));
	//m_pVM->DrawStaticTexture(m_nOptionSpriteID,545,105,1.0f,1.0f,&src_NotPressed);
	//m_pVM->DrawStaticTexture(m_nOptionSpriteID,450,105,1.0f,1.0f,&src_Pressed);
	//m_pVM->DrawStaticTexture(m_nOptionSpriteID,545,200,1.0f,1.0f,&src_NotPressed,0,0,3.14f);
	//m_pVM->DrawStaticTexture(m_nOptionSpriteID,450,200,1.0f,1.0f,&src_Pressed,0,0,3.14f);
	
	//m_pVM->DrawStaticTexture(m_nOptionSpriteID,550,150,1.0f,1.0f,&src_PowerPressed);

	/*RECT cursRect= { 275, m_nCursPosY, 285, m_nCursPosY+10 };
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
	

	m_pVM->DrawFont(m_nFontID, "Exit", 300, 300);*/
}



//pDI->KeyDown(DIK_A) || pDI->JoystickGetLStickDirDown(DIR_LEFT,0))
//pDI->KeyDown(DIK_D) || pDI->JoystickGetLStickDirDown(DIR_RIGHT,0))
//pDI->KeyDown(DIK_W) || pDI->JoystickGetLStickDirDown(DIR_UP,0) )
//pDI->KeyDown(DIK_S) || pDI->JoystickGetLStickDirDown(DIR_DOWN,0))
