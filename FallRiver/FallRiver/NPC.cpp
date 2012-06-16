#include "NPC.h"
#include "ViewManager.h"
#include "DestroyNPC.h"
#include "DirectInput.h"
#include "GamePlayState.h"

NPC::NPC()
{
	m_nCharacterType = CHA_NPC;
	m_nVelX = 0;
	m_nVelY = 0;
}

NPC::~NPC()
{

}

void NPC::Update(float fElapsedTime) 
{
	DirectInput* pDI = DirectInput::GetInstance();

	if( pDI->KeyDown(DIK_RIGHT) && GamePlayState::GetInstance()->CanMoveRight() )
		SetVelX(-100);
	else if( pDI->KeyDown(DIK_LEFT)  && GamePlayState::GetInstance()->CanMoveLeft() )
		SetVelX(100);
	else
		SetVelX(0);

	if( pDI->KeyDown(DIK_UP)  && GamePlayState::GetInstance()->CanMoveUp() )
		SetVelY(100);
	else if( pDI->KeyDown(DIK_DOWN)  && GamePlayState::GetInstance()->CanMoveDown() )
		SetVelY(-100);
	else
		SetVelY(0);

	BaseCharacter::Update(fElapsedTime);
}

void NPC::Render() 
{
	// Render this NPC
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 0, 255, 0);
}

void NPC::SaySomething() 
{
}

bool NPC::CheckCollision(IObjects* pBase) 
{
	return false;
}

