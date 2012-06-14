#include "CreditsMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "CGame.h"

CreditsMenuState::CreditsMenuState()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
}

CreditsMenuState::~CreditsMenuState()
{

}

CreditsMenuState* CreditsMenuState::GetInstance()
{
	static CreditsMenuState s_Instance;

	return &s_Instance;
}

void CreditsMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
	m_pVM = ViewManager::GetInstance();
}

void CreditsMenuState::Exit() 
{
}

bool CreditsMenuState::Input() 
{
	if(m_pDI->KeyPressed(DIK_ESCAPE) )
		CGame::GetInstance()->RemoveState();

	return true;
}

void CreditsMenuState::Update(float fElapsedTime) 
{
}

void CreditsMenuState::Render() 
{
}

