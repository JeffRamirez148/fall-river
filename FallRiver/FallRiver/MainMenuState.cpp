#include "MainMenuState.h"
#include "HowToPlayMenuState.h"
#include "OptionsMenuState.h"
#include "GamePlayState.h"
#include "ViewManager.h"
#include "DirectInput.h"
#include "HighScoresMenuState.h"
#include "CreditsMenuState.h"
#include "CGame.h"

MainMenuState::MainMenuState()
{
	m_pDI = nullptr;
	m_nCursPosY = 175;
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();
}

void MainMenuState::Exit() 
{
	m_pDI = nullptr;
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
			CGame::GetInstance()->ChangeState(GamePlayState::GetInstance());
		else if( m_nCursPosY == 200 )
			CGame::GetInstance()->ChangeState(HighScoresMenuState::GetInstance());
		else if( m_nCursPosY == 225 )
			CGame::GetInstance()->ChangeState(OptionsMenuState::GetInstance());
		else if( m_nCursPosY == 250 )
			CGame::GetInstance()->ChangeState(HowToPlayMenuState::GetInstance());
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
	// Do Rendering Here
	m_pVM->DrawTextW("FALL RIVER", 100, 100, 255, 0, 0);

	RECT cursRect= { 275, m_nCursPosY, 285, m_nCursPosY+10 };
	m_pVM->DrawRect( cursRect, 255, 0, 0 );

	m_pVM->DrawTextW("Play", 300, 175, 255, 255, 0);
	m_pVM->DrawTextW("HighScores", 300, 200, 255, 255, 0);
	m_pVM->DrawTextW("Options", 300, 225, 255, 255, 0);
	m_pVM->DrawTextW("How To Play", 300, 250, 255, 255, 0);
	m_pVM->DrawTextW("Credits", 300, 275, 255, 255, 0);
	m_pVM->DrawTextW("Exit", 300, 300, 255, 255, 0);

}

MainMenuState* MainMenuState::GetInstance() 
{
	static MainMenuState s_Instance;

	return &s_Instance;
}

