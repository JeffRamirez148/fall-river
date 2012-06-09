#include "MainMenuState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "DirectInput.h"
#include "XMLManager.h"
#include "IMenuState.h"
#include "CGame.h"

void MainMenuState::Enter() 
{
	m_pDI = DirectInput::GetInstance();
}

void MainMenuState::Exit() 
{
}

bool MainMenuState::Input() 
{
	if( m_pDI->KeyPressed(DIK_ESCAPE) )
		return false;

	return true;
}

void MainMenuState::Update(float fElapsedTime) 
{
}

void MainMenuState::Render() 
{
}

MainMenuState* MainMenuState::GetInstance() 
{
	static MainMenuState s_Instance;

	return &s_Instance;
}

