#include "HowToPlayMenuState.h"
#include "ViewManager.h"
#include "DirectInput.h"
#include "IMenuState.h"
#include "CGame.h"

HowToPlayMenuState::HowToPlayMenuState()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
}

HowToPlayMenuState::~HowToPlayMenuState()
{

}

HowToPlayMenuState* HowToPlayMenuState::GetInstance() 
{
	static HowToPlayMenuState s_Instance;

	return &s_Instance;
}

void HowToPlayMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();
}

void HowToPlayMenuState::Exit() 
{
}

bool HowToPlayMenuState::Input() 
{
	// Pressing Escape will End the Game
	if( m_pDI->KeyPressed(DIK_ESCAPE) )
		CGame::GetInstance()->RemoveState();
	return true;
}

void HowToPlayMenuState::Update(float fElapsedTime) 
{
}

void HowToPlayMenuState::Render() 
{

}

