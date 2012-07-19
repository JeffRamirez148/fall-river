#include "LoadMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "XMLManager.h"
#include "DirectInput.h"
#include "CGame.h"
#include "GamePlayState.h"
#include "IMenuState.h"

LoadMenuState* LoadMenuState::GetInstance() 
{
	static LoadMenuState s_Instance;

	return &s_Instance;
}

LoadMenuState::LoadMenuState()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nCursPosY = 0;
	m_nCursPosX = 0;
	m_nFontID = -1;
	m_bSure = false;
	m_bCheck = false;
	m_bIsLoading = false;

	m_nNewID = -1;
	m_nLoadID = -1;
	m_nExitID = -1;
}

LoadMenuState::~LoadMenuState()
{

}

void LoadMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();

	m_nNewID	= m_pVM->RegisterTexture("resource/graphics/bg_loadMenu_newGame.png");
	m_nLoadID	= m_pVM->RegisterTexture("resource/graphics/bg_loadMenu_loadGame.png");
	m_nExitID	= m_pVM->RegisterTexture("resource/graphics/bg_loadMenu_exit.png");
	m_nFontID	= m_pVM->RegisterFont("resource/graphics/FallRiver_0.png");

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

void LoadMenuState::ReEnter()
{
	audio->playMusic(musicID);
	audio->playMusic(musicID2);
}

void LoadMenuState::Exit() 
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nCursPosY = 0;
	m_nCursPosX = 0;
	m_bSure = false;
	m_bCheck = false;
	m_bIsLoading = false;
}

bool LoadMenuState::Input() 
{
	if( m_pDI->KeyPressed(DIK_DOWN) || m_pDI->KeyPressed(DIK_S) || m_pDI->JoystickGetLStickDirPressed(DIR_DOWN,0))
	{
		if(!m_bIsLoading)
			m_nCursPosY += 100;
		else
			m_nCursPosY += 50;
		if( m_nCursPosY == 350 && m_bIsLoading )
			m_nCursPosY = 400;
		else if( m_nCursPosY > 400 )
			m_nCursPosY = 200;

		audio->playSound(soundID);
	}
	else if( m_pDI->KeyPressed(DIK_UP) || m_pDI->KeyPressed(DIK_W) || m_pDI->JoystickGetLStickDirPressed(DIR_UP,0) )
	{
		if(!m_bIsLoading)
			m_nCursPosY -= 100;
		else
			m_nCursPosY -= 50;
		if( m_nCursPosY == 350 )
			m_nCursPosY = 300;
		else if( m_nCursPosY < 200 )
			m_nCursPosY = 400;

		audio->playSound(soundID);
	}

	if( ( ( m_pDI->KeyPressed(DIK_D) || m_pDI->KeyPressed(DIK_RIGHT) ) && m_bCheck) || ( m_pDI->JoystickGetLStickDirPressed(DIR_RIGHT,0) && m_bCheck ))
	{
		m_nCursPosX += 100;
		if( m_nCursPosX > 380 )
			m_nCursPosX = 280;

		audio->playSound(soundID);
	}
	else if( ( ( m_pDI->KeyPressed(DIK_A) || m_pDI->KeyPressed(DIK_LEFT) ) && m_bCheck ) || ( m_pDI->JoystickGetLStickDirPressed(DIR_LEFT,0) && m_bCheck ))
	{
		m_nCursPosX -= 100;
		if( m_nCursPosX < 280 )
			m_nCursPosX = 380;

		audio->playSound(soundID);
	}

	if( m_pDI->KeyPressed(DIK_RETURN)  || m_pDI->JoystickButtonPressed(0,0))
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
				m_bCheck = false;
		}

		if(!m_bIsLoading)
		{
			if( m_nCursPosY == 200 )
			{
				CGame::GetInstance()->RemoveState();
				CGame::GetInstance()->ChangeState(GamePlayState::GetInstance());
			}
			else if(m_nCursPosY == 300 )
			{
				m_bIsLoading = true;
				m_nCursPosY = 200;
			}
			else if(m_nCursPosY == 400 )
				CGame::GetInstance()->RemoveState();
			return true;
		}

		if( m_nCursPosY == 200 )
		{
			GamePlayState::GetInstance()->SetPlayer(XMLManager::GetInstance()->LoadProgress("save1.xml"));
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->ChangeState(GamePlayState::GetInstance());
		}
		else if(m_nCursPosY == 250)
		{
			GamePlayState::GetInstance()->SetPlayer(XMLManager::GetInstance()->LoadProgress("save2.xml"));
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->ChangeState(GamePlayState::GetInstance());
		}
		else if( m_nCursPosY == 300 )
		{
			GamePlayState::GetInstance()->SetPlayer(XMLManager::GetInstance()->LoadProgress("save3.xml"));
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->ChangeState(GamePlayState::GetInstance());
		}
		else if( m_nCursPosY == 400 )
			m_bIsLoading = false;

		Player* testingstuff = GamePlayState::GetInstance()->GetPlayer();
		return true;
	}

	if((m_pDI->KeyDown(DIK_ESCAPE) && !m_bCheck) || (m_pDI->JoystickButtonPressed(1,0) && !m_bCheck) )
	{
		audio->playSound(soundID);
		CGame::GetInstance()->RemoveState();
	}

	return true;
}

void LoadMenuState::Update(float fElapsedTime) 
{
}

void LoadMenuState::Render() 
{
	if(m_bIsLoading)
	{
		m_pVM->DrawStaticTexture(m_nLoadID, 0, 0,  0.4f, 0.6f);

		m_pVM->GetSprite()->Flush();

		RECT backRect = {100, 150, 500, 450};
		m_pVM->DrawRect(backRect, 100, 100, 100);

		m_pVM->DrawFont(m_nFontID,"Load Progress", 200, 150);

		//m_pVM->DrawTextW("Save 1", 250, 200, 255, 255, 0);
		m_pVM->DrawFont(m_nFontID, "Save 1", 250, 200);
		m_pVM->DrawFont(m_nFontID,"Save 2", 250, 250);
		m_pVM->DrawFont(m_nFontID, "Save 3", 250, 300);
		m_pVM->DrawFont(m_nFontID,"Back", 300, 400);

		RECT rRect = {225, m_nCursPosY, 235, m_nCursPosY+10};

		m_pVM->DrawRect(rRect, 0, 255, 255, 100);
	}
	else
	{
		if(m_nCursPosY == 200)
			m_pVM->DrawStaticTexture(m_nNewID, 0, 0,  0.4f, 0.6f);
		else if(m_nCursPosY == 300)
			m_pVM->DrawStaticTexture(m_nLoadID, 0, 0, 0.4f, 0.6f);
		else if(m_nCursPosY == 400)
			m_pVM->DrawStaticTexture(m_nExitID, 0, 0,  0.4f, 0.6f);
	}

}

