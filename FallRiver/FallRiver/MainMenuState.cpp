#include "MainMenuState.h"
#include "HowToPlayMenuState.h"
#include "OptionsMenuState.h"
#include "GamePlayState.h"
#include "ViewManager.h"
#include "DirectInput.h"
#include "HighScoresMenuState.h"
#include "LoadMenuState.h"
#include "CreditsMenuState.h"
#include "CGame.h"

MainMenuState::MainMenuState()
{
	m_pVM = nullptr;
	m_pDI = nullptr;
	m_nCursPosY = 175;
	m_nMenuPlayID = -1;
	m_nMenuHowToID = -1;
	m_nMenuOptionsID = -1;
	m_dwFlash1 = 0;
	m_dwFlash2 = 0;
	m_dwFlash3 = 0;
	m_dwReset = 0;
	m_nMenuHighScoresID = -1;
	m_nMenuCreditsID	= -1;
	m_nMenuExitID		= -1;
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();

	m_nMenuPlayID		= m_pVM->RegisterTexture("resource/graphics/main_play.png");
	m_nMenuHowToID		= m_pVM->RegisterTexture("resource/graphics/main_howTo.png");
	m_nMenuOptionsID	= m_pVM->RegisterTexture("resource/graphics/main_options.png");
	m_nFallRiverID		= m_pVM->RegisterTexture("resource/graphics/logo_game_1024.png");
	m_nMenuHighScoresID = m_pVM->RegisterTexture("resource/graphics/main_highScores.png");
	m_nMenuCreditsID	= m_pVM->RegisterTexture("resource/graphics/main_credits.png");
	m_nMenuExitID		= m_pVM->RegisterTexture("resource/graphics/main_exit.png");

}

void MainMenuState::Exit() 
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nCursPosY = 175;
	m_nMenuPlayID = -1;
	m_nMenuHowToID = -1;
	m_nMenuOptionsID = -1;
	m_dwFlash1 = 0;
	m_dwFlash2 = 0;
	m_dwFlash3 = 0;
	m_dwReset = 0;
	
}

bool MainMenuState::Input() 
{
	if( m_pDI->KeyPressed(DIK_DOWNARROW) )
	{
		m_nCursPosY += 25;
		if( m_nCursPosY > 300 )
			m_nCursPosY = 175;
	}
	else if( m_pDI->KeyPressed(DIK_UPARROW) )
	{
		m_nCursPosY -= 25;
		if( m_nCursPosY < 175 )
			m_nCursPosY = 300;
	}

	if( m_pDI->KeyPressed(DIK_RETURN) )
	{
		if( m_nCursPosY == 175 )
			CGame::GetInstance()->ChangeState(LoadMenuState::GetInstance());
		else if( m_nCursPosY == 200 )
			CGame::GetInstance()->ChangeState(OptionsMenuState::GetInstance());
		else if( m_nCursPosY == 225 )
			CGame::GetInstance()->ChangeState(HowToPlayMenuState::GetInstance());
		else if( m_nCursPosY == 250 )
			CGame::GetInstance()->ChangeState(HighScoresMenuState::GetInstance());
		else if( m_nCursPosY == 275 )
			CGame::GetInstance()->ChangeState(CreditsMenuState::GetInstance());
		else if( m_nCursPosY == 300 )
			return false;
		return true;
	}


	// Pressing Escape will End the Game
	if( m_pDI->KeyPressed(DIK_ESCAPE) )
		m_nCursPosY = 300;

	return true;
}

void MainMenuState::Update(float fElapsedTime) 
{
}

void MainMenuState::Render() 
{
	if(m_dwFlash1 == 0)
		m_dwFlash1 = GetTickCount() + 3000;

	if(m_dwFlash2 == 0)
		m_dwFlash2 = GetTickCount() + 3800;

	if(m_dwFlash3 == 0)
		m_dwFlash3 = GetTickCount() + 4000;

	// Do Rendering Here
	if(m_nCursPosY == 175)
	{
		if(m_dwFlash1 <= GetTickCount() || m_dwFlash2 <= GetTickCount() || m_dwFlash3 <= GetTickCount())
			m_pVM->DrawStaticTexture(m_nMenuPlayID, 0, 0, 0.33f, 0.5f, 0, 0, 0, 0, D3DCOLOR_ARGB(255, 230, 255, 255));
		else
			m_pVM->DrawStaticTexture(m_nMenuPlayID, 0, 0, 0.33f, 0.5f);
	}
	else if(m_nCursPosY == 200)
	{
		if(m_dwFlash1 <= GetTickCount() || m_dwFlash2 <= GetTickCount() || m_dwFlash3 <= GetTickCount())
			m_pVM->DrawStaticTexture(m_nMenuOptionsID, 0, 0, 0.33f, 0.5f, 0, 0, 0, 0, D3DCOLOR_ARGB(255, 230, 255, 255));
		else
			m_pVM->DrawStaticTexture(m_nMenuOptionsID, 0, 0, 0.33f, 0.5f);
	}
	else if(m_nCursPosY == 225)
	{
		if(m_dwFlash1 <= GetTickCount() || m_dwFlash2 <= GetTickCount() || m_dwFlash3 <= GetTickCount())
			m_pVM->DrawStaticTexture(m_nMenuHowToID, 0, 0, 0.33f, 0.5f, 0, 0, 0, 0, D3DCOLOR_ARGB(255, 230, 255, 255));
		else
			m_pVM->DrawStaticTexture(m_nMenuHowToID, 0, 0, 0.33f, 0.5f);
	}
	else if(m_nCursPosY == 250)
	{
		if(m_dwFlash1 <= GetTickCount() || m_dwFlash2 <= GetTickCount() || m_dwFlash3 <= GetTickCount())
			m_pVM->DrawStaticTexture(m_nMenuHighScoresID, 0, 0, 0.33f, 0.5f, 0, 0, 0, 0, D3DCOLOR_ARGB(255, 230, 255, 255));
		else
			m_pVM->DrawStaticTexture(m_nMenuHighScoresID, 0, 0, 0.33f, 0.5f);
	}
	else if(m_nCursPosY == 275)
	{
		if(m_dwFlash1 <= GetTickCount() || m_dwFlash2 <= GetTickCount() || m_dwFlash3 <= GetTickCount())
			m_pVM->DrawStaticTexture(m_nMenuCreditsID, 0, 0, 0.33f, 0.5f, 0, 0, 0, 0, D3DCOLOR_ARGB(255, 230, 255, 255));
		else
			m_pVM->DrawStaticTexture(m_nMenuCreditsID, 0, 0, 0.33f, 0.5f);
	}
	else if(m_nCursPosY == 300)
	{
		if(m_dwFlash1 <= GetTickCount() || m_dwFlash2 <= GetTickCount() || m_dwFlash3 <= GetTickCount())
			m_pVM->DrawStaticTexture(m_nMenuExitID, 0, 0, 0.33f, 0.5f, 0, 0, 0, 0, D3DCOLOR_ARGB(255, 230, 255, 255));
		else
			m_pVM->DrawStaticTexture(m_nMenuExitID, 0, 0, 0.33f, 0.5f);
	}

	m_pVM->DrawStaticTexture(m_nFallRiverID, -50, 10, 0.5f, 0.5f);

	if((m_dwFlash1 <= GetTickCount() || m_dwFlash2 <= GetTickCount() || m_dwFlash3 <= GetTickCount()) && m_dwReset == 0)
		m_dwReset = GetTickCount() + 200;

	if(m_dwReset <= GetTickCount())
	{
		m_dwReset = 0;
		if(m_dwFlash1 <= GetTickCount())
			m_dwFlash1 = 0;

		if(m_dwFlash2 <= GetTickCount())
			m_dwFlash2 = 0;

		if(m_dwFlash3 <= GetTickCount())
			m_dwFlash3 = 0;
	}

	//m_pVM->DrawTextW("FALL RIVER", 100, 100, 255, 0, 0);

	//RECT cursRect= { 275, m_nCursPosY, 285, m_nCursPosY+10 };
	//m_pVM->DrawRect( cursRect, 255, 0, 0 );

	//m_pVM->DrawTextW("Play", 300, 175, 255, 255, 0);
	////m_pVM->DrawFont(m_nFontID, "Play", 300, 175);
	//m_pVM->DrawTextW("HighScores", 300, 200, 255, 255, 0);
	//m_pVM->DrawTextW("Options", 300, 225, 255, 255, 0);
	//m_pVM->DrawTextW("How To Play", 300, 250, 255, 255, 0);
	//m_pVM->DrawTextW("Credits", 300, 275, 255, 255, 0);
	//m_pVM->DrawTextW("Exit", 300, 300, 255, 255, 0);

}

MainMenuState* MainMenuState::GetInstance() 
{
	static MainMenuState s_Instance;

	return &s_Instance;
}

