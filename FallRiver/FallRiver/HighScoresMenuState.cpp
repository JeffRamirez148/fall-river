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
	m_bNameEntered = false;
	keytimer = 0;
	m_cName['\0'];
	m_nSpace = 0;
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
	bgID = m_pVM->RegisterTexture("resource/graphics/bg_credits.png");

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

	if(CGame::GetInstance()->scoreCatch > 0)
		m_bNameEntered = false;
	keytimer = 0;
	m_nScore = CGame::GetInstance()->scoreCatch;

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
	XMLManager::GetInstance()->SaveHighScores("highscore.xml",m_vHighscore);

	CGame::GetInstance()->scoreCatch = 0;

	for(int i = 0; i < 9; ++i)
		m_cName[i] = '\0';

	m_bNameEntered = false;
	keytimer = 0;
	m_nScore = 100;
	m_nSpace = 0;
}

bool HighScoresMenuState::Input() 
{
	CGame* pGame = CGame::GetInstance();

	if( m_pDI->KeyPressed(DIK_ESCAPE) || m_pDI->JoystickButtonPressed(1,0) )
		CGame::GetInstance()->RemoveState();
	if(m_pDI->KeyPressed(DIK_RETURN)|| m_pDI->JoystickButtonPressed(0,0))
	{
		if(m_bNameEntered == true)
		{
		CGame::GetInstance()->RemoveState();
		CGame::GetInstance()->ChangeState(CreditsMenuState::GetInstance());
		}
	}

	if(m_bNameEntered == false)
	{
		if(m_pDI->KeyPressed(DIK_BACKSPACE))
		{
			if(m_nSpace > 0)
			{
				m_nSpace--;
				m_cName[m_nSpace] = '\0';
			}
			else
			{
				m_cName[0] = '\0';
			}
		}
		else if(((m_pDI->CheckKeys() <= 'z' && m_pDI->CheckKeys() >= 'a') || (m_pDI->CheckKeys() <= 'Z' && m_pDI->CheckKeys() >= 'A')) && keytimer == 0)
		{
			m_cName[m_nSpace] = m_pDI->CheckKeys();

			if(m_nSpace < 9)
				m_nSpace++;

			keytimer += .15f;
		}
		if(m_pDI->KeyPressed(DIK_RETURN) && (m_cName[0] != ' ' || m_cName != '\0'))
		{
			tHighscore player;
			player.nScore = m_nScore;
			strcpy_s(player.szName, m_cName);
			m_vHighscore.push_back(player);

			vector<tHighscore> newHS;

			for(int i = 0; i < 5; ++i)
			{
				vector<tHighscore>::iterator iter;
				vector<tHighscore>::iterator iter2;
				iter = m_vHighscore.begin();
				tHighscore test = *iter;
				iter2 = iter;
				++iter;

				for( ;iter != m_vHighscore.end(); ++iter)
				{
					if((*iter).nScore > test.nScore)
					{
						test = *iter;
						iter2 = iter;
					}
					
				}
				newHS.push_back(test);
				m_vHighscore.erase(iter2);
			}

			m_vHighscore = newHS;
			m_bNameEntered = true;
		}
	}

	// Pressing Escape will End the Gam

	return true;
}

void HighScoresMenuState::Update(float fElapsedTime) 
{
	if(keytimer > 0)
		keytimer -= fElapsedTime;
	if(keytimer <= 0)
		keytimer = 0;
}

void HighScoresMenuState::Render() 
{

	m_pVM->GetSprite()->Flush();
	m_pVM->Clear();

	m_pVM->DrawStaticTexture(bgID,0, 0);

	if(m_bNameEntered == false)
	{
		m_pVM->DrawFont(fontID, "Enter your name", 50, 300);
		m_pVM->DrawFont(fontID, m_cName, 460, 300);
	}
	else
	{

		m_pVM->DrawFont(fontID,"HIGH SCORES",200,0, 2.0f, 2.0f, 0, 0, 0 , D3DCOLOR_XRGB(255, 0, 0));

	
		for(unsigned int i = 0; i < m_vHighscore.size(); i++ )
		{

			//TCHAR buffer[100];

			TCHAR sBuffer[10] = {};
			char vBuffer[10] = {};

			_stprintf_s( sBuffer, 10, _T("%i"), m_vHighscore[i].nScore);
			wcstombs_s( nullptr, vBuffer, 10, sBuffer, _TRUNCATE );
			//mbstowcs_s( nullptr, buffer, 100, m_vPlayer[i].szName, _TRUNCATE );

			m_pVM->DrawFont(fontID,m_vHighscore[i].szName,75.0f,float(70+10+10*i*3),1.0f,1.0f,0,0,0, D3DCOLOR_XRGB(255,255,255));
			m_pVM->DrawFont(fontID,"Score",75+300,float(70+10+10*i*3),1.0f,1.0f,0,0,0,D3DCOLOR_XRGB(255,255,255));
			m_pVM->DrawFont(fontID,vBuffer,75+420,float(70+10+10*i*3),1.0f,1.0f,0,0,0, D3DCOLOR_XRGB(255,255,255));
		}
	}
}

void HighScoresMenuState::SetEnd(bool aEnd) 
{
}

void HighScoresMenuState::SetOldAttractMode(bool aMode)
{
}

