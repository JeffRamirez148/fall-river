#include "HighScoresMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "CGame.h"
#include "CreditsMenuState.h"
#include "XMLManager.h"

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

	

	if( XMLManager::GetInstance()->LoadHighScores("highscore.xml",m_vHighscore) == false )
	{
		XMLManager::GetInstance()->GeneratePlayers(m_vHighscore);
		XMLManager::GetInstance()->SaveHighScores("highscore.xml",m_vHighscore);
	}
	



}

void HighScoresMenuState::ReEnter()
{
	audio->playMusic(musicID);
	audio->playMusic(musicID2);
}

void HighScoresMenuState::Exit() 
{
}

bool HighScoresMenuState::Input() 
{
	// Pressing Escape will End the Game
	if( m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1,0) )
		CGame::GetInstance()->RemoveState();
	if(m_pDI->KeyPressed(DIK_RETURN)|| m_pDI->JoystickButtonPressed(0,0))
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

	
	for(unsigned int i = 0; i < m_vHighscore.size(); i++ )
	{

		//TCHAR buffer[100];

		TCHAR sBuffer[10] = {};
		char vBuffer[10] = {};

		_stprintf_s( sBuffer, 10, _T("%i"), m_vHighscore[i].nScore);
		wcstombs_s( nullptr, vBuffer, 10, sBuffer, _TRUNCATE );
		//mbstowcs_s( nullptr, buffer, 100, m_vPlayer[i].szName, _TRUNCATE );

		m_pVM->DrawFont(fontID,m_vHighscore[i].szName,75.0f,float(70+10+10*i*2),0.5f,0.5f,0,0,0, D3DCOLOR_XRGB(255,255,255));
		m_pVM->DrawFont(fontID,"Score",75+200,float(70+10+10*i*2),0.5f,0.5f,0,0,0,D3DCOLOR_XRGB(255,255,255));
		m_pVM->DrawFont(fontID,vBuffer,75+300,float(70+10+10*i*2),0.5f,0.5f,0,0,0, D3DCOLOR_XRGB(255,255,255));
	}


	
}

void HighScoresMenuState::SetEnd(bool aEnd) 
{
}

void HighScoresMenuState::SetOldAttractMode(bool aMode)
{
}

