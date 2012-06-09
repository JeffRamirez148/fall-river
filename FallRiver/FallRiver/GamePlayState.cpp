#include "GamePlayState.h"
#include "ViewManager.h"
#include "AudioManager.h"
#include "ObjectManager.h"
#include "OptionsMenuState.h"
#include "Level.h"
#include "CGame.h"
#include "DirectInput.h"
#include "Enemy.h"
#include "Player.h"
#include "MessageSystem.h"
#include "Particle_Manager.h"
#include "HUD.h"
#include "XMLManager.h"

void GamePlayState::Enter()
{
	m_pDI = DirectInput::GetInstance();


}

void GamePlayState::Exit() 
{
}

bool GamePlayState::Input() 
{
	if( m_pDI->KeyPressed(DIK_ESCAPE) )
		CGame::GetInstance()->RemoveState();

	return true;
}

void GamePlayState::Update(float fElapsedTime) 
{
}

void GamePlayState::Render() 
{
}

GamePlayState* GamePlayState::GetInstance() 
{
	static GamePlayState s_Instance;

	return &s_Instance;
}

