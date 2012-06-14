#include "OptionsMenuState.h"
#include "DirectInput.h"
#include "CGame.h"
#include "ViewManager.h"
#include "IMenuState.h"

OptionsMenuState::OptionsMenuState()
{
	m_nCursPosY = 200;
}

OptionsMenuState::~OptionsMenuState()
{

}

OptionsMenuState* OptionsMenuState::GetInstance() 
{
	static OptionsMenuState stuff;

	return &stuff;
}

void OptionsMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();
}

void OptionsMenuState::Exit() 
{
	m_pVM = nullptr;
	m_pDI = nullptr;

	m_nCursPosY = 200;
}

bool OptionsMenuState::Input()
{
	if( m_pDI->KeyPressed(DIK_DOWNARROW) )
	{
		m_nCursPosY += 25;
		if(m_nCursPosY == 275)
			m_nCursPosY += 25;
		if( m_nCursPosY > 300 )
			m_nCursPosY = 200;
	}
	else if( m_pDI->KeyPressed(DIK_UPARROW) )
	{
		m_nCursPosY -= 25;
		if(m_nCursPosY == 275)
			m_nCursPosY -= 25;
		if( m_nCursPosY < 200 )
			m_nCursPosY = 300;
	}

	if( m_pDI->KeyPressed(DIK_RETURN) )
	{
		if( m_nCursPosY == 300 )
			CGame::GetInstance()->RemoveState();
		return true;
	}

	// Pressing Escape will End the Game
	if( m_pDI->KeyPressed(DIK_ESCAPE) )
		m_nCursPosY = 300;

	return true;
}

void OptionsMenuState::Update(float aFElapsedTime)
{
	
}

void OptionsMenuState::Render()
{
	// Do Rendering Here

	m_pVM->DrawTextW("OPTIONS", 100, 100, 255, 0, 0);

	RECT cursRect= { 275, m_nCursPosY, 285, m_nCursPosY+10 };
	m_pVM->DrawRect( cursRect, 255, 0, 0 );

	m_pVM->DrawTextW("Sound fx Volume", 300, 200, 255, 255, 0);
	m_pVM->DrawTextW("Music Volume", 300, 225, 255, 255, 0);
	m_pVM->DrawTextW("Set Screen Resolution", 300, 250, 255, 255, 0);
	m_pVM->DrawTextW("Exit", 300, 300, 255, 255, 0);
}

