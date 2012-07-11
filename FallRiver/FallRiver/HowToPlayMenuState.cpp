#include "HowToPlayMenuState.h"
#include "ViewManager.h"
#include "DirectInput.h"
#include "IMenuState.h"
#include "CGame.h"
#include "AudioManager.h"

HowToPlayMenuState::HowToPlayMenuState()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nHowToKeyID = -1;
	m_nHowToJoyID = -1;
	m_nHowToXboxID = -1;
}

HowToPlayMenuState::~HowToPlayMenuState()
{

}

HowToPlayMenuState* HowToPlayMenuState::GetInstance() 
{
	static HowToPlayMenuState s_Instance;

	return &s_Instance;
}

void HowToPlayMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();

	m_nHowToKeyID = m_pVM->RegisterTexture("resource/graphics/bg_howTo_keyboard.png");
	m_nHowToJoyID = m_pVM->RegisterTexture("resource/graphics/bg_howTo_arcade.png");
	m_nHowToXboxID = m_pVM->RegisterTexture("resource/graphics/bg_howTo_xBox.png");
	audio = AudioManager::GetInstance();

	FMOD_VECTOR tmp = {0,0,0};
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	audio->SetListenerPos(tmp);

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

void HowToPlayMenuState::ReEnter()
{
	audio->playMusic(musicID);
	audio->playMusic(musicID2);
}

void HowToPlayMenuState::Exit() 
{

}

bool HowToPlayMenuState::Input() 
{
	// Pressing Escape will End the Game
	if( m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1,0) )
		CGame::GetInstance()->RemoveState();
	return true;
}

void HowToPlayMenuState::Update(float fElapsedTime) 
{
}

void HowToPlayMenuState::Render() 
{
	if(m_pDI->JoystickIsUnplugged(0) )
		m_pVM->DrawStaticTexture(m_nHowToKeyID, 0, 0, 0.4f, 0.6f);
	else if (!(m_pDI->JoystickIsUnplugged(0)))
	{
		m_pVM->DrawStaticTexture(m_nHowToXboxID, 0, 0, 0.4f, 0.6f);
	}
	else
		m_pVM->DrawStaticTexture(m_nHowToJoyID, 0, 0, 0.4f, 0.6f);
}

