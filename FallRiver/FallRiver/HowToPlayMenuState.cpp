#include "HowToPlayMenuState.h"
#include "ViewManager.h"
#include "DirectInput.h"
#include "IMenuState.h"
#include "CGame.h"

HowToPlayMenuState::HowToPlayMenuState()
{
	m_pDI = nullptr;
	m_pVM = nullptr;
	m_nHowToKeyID = -1;
	m_nHowToJoyID = -1;
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

	m_nHowToKeyID = m_pVM->RegisterTexture("resource/graphics/bg_howTo_keyboard.png");
	m_nHowToJoyID = m_pVM->RegisterTexture("resource/graphics/bg_howTo_arcade.png");
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
	if(m_pDI->JoystickIsUnplugged(0) )
		m_pVM->DrawStaticTexture(m_nHowToKeyID, 0, 0, 0.4f, 0.6f);
	else
		m_pVM->DrawStaticTexture(m_nHowToJoyID, 0, 0, 0.4f, 0.6f);
}

