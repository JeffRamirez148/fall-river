#include "HighScoresMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "CGame.h"
#include "CreditsMenuState.h"

HighScoresMenuState::HighScoresMenuState()
{
	fontID = -1;
}

HighScoresMenuState::~HighScoresMenuState()
{

}

HighScoresMenuState* HighScoresMenuState::GetInstance() 
{
	static HighScoresMenuState s_Instance;

	return &s_Instance;
}

void HighScoresMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();
	
	fontID = m_pVM->RegisterFont("resource/graphics/FallRiver_0.png");

	FMOD_VECTOR tmp = {0,0,0};
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	audio->SetListenerPos(tmp);

	musicID = audio->registerMusic("resource/Sounds/background.mp3");
	audio->setMusicPos(musicID, sound1);

	audio->setMusicVel(musicID, tmp);
	audio->setMusicLooping(musicID, true);
	audio->playMusic(musicID);

}

void HighScoresMenuState::ReEnter()
{
	audio->playMusic(musicID);
}

void HighScoresMenuState::Exit() 
{
}

bool HighScoresMenuState::Input() 
{
	// Pressing Escape will End the Game
	if( m_pDI->KeyPressed(DIK_ESCAPE) )
		CGame::GetInstance()->RemoveState();
	if(m_pDI->KeyPressed(DIK_RETURN))
	{
		CGame::GetInstance()->RemoveState();
		CGame::GetInstance()->ChangeState(CreditsMenuState::GetInstance());
	}

	return true;
}

void HighScoresMenuState::Update(float fElapsedTime) 
{
}

void HighScoresMenuState::Render() 
{
	m_pVM->GetSprite()->Flush();
	m_pVM->Clear();

	m_pVM->DrawFont(fontID,"High Scores in progress",0,0);
	
}

void HighScoresMenuState::SetEnd(bool aEnd) 
{
}

void HighScoresMenuState::SetOldAttractMode(bool aMode)
{
}

