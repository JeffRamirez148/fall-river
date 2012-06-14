#include "NPC.h"
#include "ViewManager.h"
#include "DestroyNPC.h"
#include "DirectInput.h"

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

	if( pDI->KeyDown(DIK_RIGHT) )
		SetVelX(-100);
	else if( pDI->KeyDown(DIK_LEFT) )
		SetVelX(150);
	else
		SetVelX(0);

	if( pDI->KeyDown(DIK_UP) )
		SetVelY(150);
	else if( pDI->KeyDown(DIK_DOWN) )
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

bool NPC::CheckCollision(BaseCharacter* pBase) 
{
	return false;
}

