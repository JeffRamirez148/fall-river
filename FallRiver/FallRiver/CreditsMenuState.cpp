#include "CreditsMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "CGame.h"

CreditsMenuState::CreditsMenuState()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	fontID = -1;
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

	fontID = m_pVM->RegisterFont("resource/graphics/FallRiver_0.png");
}

void CreditsMenuState::Exit() 
{
}

bool CreditsMenuState::Input() 
{
	if(m_pDI->KeyPressed(DIK_ESCAPE) )
	{
		CGame::GetInstance()->RemoveState();
		return false;
	}
	if(m_pDI->KeyPressed(DIK_RETURN))
	{
		if(CGame::GetInstance()->m_vStates.size() == 2)
			CGame::GetInstance()->RemoveState();
		else
		{
			CGame::GetInstance()->RemoveState();
			CGame::GetInstance()->RemoveState();
		}
	}

	return true;
}

void CreditsMenuState::Update(float fElapsedTime) 
{
}

void CreditsMenuState::Render() 
{
	m_pVM->GetSprite()->Flush();
	m_pVM->Clear();

	m_pVM->DrawFont(fontID,"Credits in progress",0,0);
	

}

