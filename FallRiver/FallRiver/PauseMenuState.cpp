#include "PauseMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "XMLManager.h"
#include "DirectInput.h"
#include "OptionsMenuState.h"
#include "CGame.h"

PauseMenuState::PauseMenuState()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nCursPosY = 150;
}

PauseMenuState::~PauseMenuState()
{

}

PauseMenuState* PauseMenuState::GetInstance() 
{
	static PauseMenuState m_sInstance;

	return &m_sInstance;
}

void PauseMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();
}

void PauseMenuState::Exit()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nCursPosY = 150;
}

bool PauseMenuState::Input() 
{
	if( m_pDI->KeyPressed(DIK_DOWNARROW) )
	{
		m_nCursPosY += 50;
		if( m_nCursPosY > 300 )
			m_nCursPosY = 150;
	}
	else if( m_pDI->KeyPressed(DIK_UPARROW) )
	{
		m_nCursPosY -= 50;
		if( m_nCursPosY < 150 )
			m_nCursPosY = 300;
	}

	if(m_pDI->KeyPressed(DIK_RETURN) )
	{
		if( m_nCursPosY == 150 )
			CGame::GetInstance()->RemoveState();
		else if( m_nCursPosY == 250 )
			CGame::GetInstance()->ChangeState(OptionsMenuState::GetInstance());
		else if( m_nCursPosY == 300 )
		{
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->RemoveState();
		}

		return true;
	}

	if(m_pDI->KeyPressed(DIK_ESCAPE) )
		m_nCursPosY = 300;

	return true;
}

void PauseMenuState::Update(float fElapsedTime) 
{

}

void PauseMenuState::Render() 
{
	// Do Rendering here
	RECT cRect = { 100, 100, 500, 400 };
	RECT cursRect = { 225, m_nCursPosY, 235, m_nCursPosY+10 };
	m_pVM->DrawRect(cRect, 100, 100, 100, 255);
	m_pVM->DrawRect(cursRect, 255, 0, 0);

	m_pVM->DrawTextW("Resume", 250, 150, 255, 255, 0);
	m_pVM->DrawTextW("Save Game", 250, 200, 255, 255, 0);
	m_pVM->DrawTextW("Optons", 250, 250, 255, 255, 0);
	m_pVM->DrawTextW("Back To Main Menu", 250, 300, 255, 255, 0);
}

