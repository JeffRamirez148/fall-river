#include "CreditsMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "CGame.h"

CreditsMenuState::CreditsMenuState()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	fontID = -1;
	creditsBGID = -1;
	logoID = -1;
}

CreditsMenuState::~CreditsMenuState()
{

}

CreditsMenuState* CreditsMenuState::GetInstance()
{
	static CreditsMenuState s_Instance;

	return &s_Instance;
}

void CreditsMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();

	fontID = m_pVM->RegisterFont("resource/graphics/FallRiver_0.png");
	creditsBGID = m_pVM->RegisterTexture("resource/graphics/bg_credits.png");
	logoID = m_pVM->RegisterTexture("resource/graphics/logo_game_1024.png");
	
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

void CreditsMenuState::ReEnter()
{
	audio->playMusic(musicID2);
	audio->playMusic(musicID);
}

void CreditsMenuState::Exit() 
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	fontID = -1;
	logoID = -1;
	creditsBGID = -1;
}

bool CreditsMenuState::Input() 
{
	if(m_pDI->KeyPressed(DIK_ESCAPE) )
	{
		CGame::GetInstance()->RemoveState();
		return false;
	}
	if(m_pDI->KeyPressed(DIK_RETURN))
	{
		if(CGame::GetInstance()->m_vStates.size() == 2)
			CGame::GetInstance()->RemoveState();
		else
		{
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->RemoveState();
		}
	}

	return true;
}

void CreditsMenuState::Update(float fElapsedTime) 
{
	fTime += fElapsedTime * 20;
	if( fTime > 800)
		fTime = 0;
}

void CreditsMenuState::Render() 
{
	

	m_pVM->GetSprite()->Flush();
	m_pVM->Clear();

	m_pVM->DrawStaticTexture(creditsBGID,0.0f,0.0f,1.0f,1.0f,0,0,0,0);
	m_pVM->DrawStaticTexture(logoID,140.0f,CGame::GetInstance()->GetScreenHeight() - fTime,0.5f,0.5f,0,0,0,0);
	m_pVM->DrawFont(fontID,"Credits",320,(CGame::GetInstance()->GetScreenHeight() + 96) - fTime);
	m_pVM->DrawFont(fontID,"Executive Producer - John O'Leske\n\nAssociate Producer - Shawn Paris\n\n           Artist - Chris Jahosky\n\nProgrammer - Patrick Abiney\n\nProgrammer - Jeffery Ramirez\n\nProgrammer - Kamin Johnson\n\nProgrammer - Eric Moll\n\nProgrammer - Ian Alcid\n\n             Thanks for playing!",130,(CGame::GetInstance()->GetScreenHeight()+128) - fTime);
	

}

