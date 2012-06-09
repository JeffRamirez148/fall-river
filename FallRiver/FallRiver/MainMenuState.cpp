#include "MainMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "XMLManager.h"
#include "GamePlayState.h"
#include "CGame.h"

MainMenuState::MainMenuState()
{
	m_pDI = nullptr;
	m_nCursPosY = 100;
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
}

void MainMenuState::Exit() 
{
	m_pDI = nullptr;
}

bool MainMenuState::Input() 
{
	if( m_pDI->KeyPressed(DIK_DOWNARROW) )
	{
		m_nCursPosY += 50;
		if( m_nCursPosY > 300 )
			m_nCursPosY = 100;
	}
	else if( m_pDI->KeyPressed(DIK_UPARROW) )
	{
		m_nCursPosY -= 50;
		if( m_nCursPosY < 100 )
			m_nCursPosY = 300;
	}

	if( m_pDI->KeyPressed(DIK_RETURN) )
	{
		CGame::GetInstance()->ChangeState(GamePlayState::GetInstance());
	}


	// Pressing Escape will End the Game
	if( m_pDI->KeyPressed(DIK_ESCAPE) )
		return false;

	return true;
}

void MainMenuState::Update(float fElapsedTime) 
{
}

void MainMenuState::Render() 
{
	// Do Rendering Here
}

MainMenuState* MainMenuState::GetInstance() 
{
	static MainMenuState s_Instance;

	return &s_Instance;
}

