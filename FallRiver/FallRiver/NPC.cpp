#include "NPC.h"
#include "ViewManager.h"
#include "DestroyNPC.h"
#include "DirectInput.h"
#include "GamePlayState.h"
#include "CGame.h"

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


	BaseCharacter::Update(fElapsedTime);
}

void NPC::Render() 
{
	// Render this NPC
	ViewManager* pVM = ViewManager::GetInstance();

	RECT reRect = {long(GetPosX() - GamePlayState::GetInstance()->GetCamera().x), long(GetPosY() - GamePlayState::GetInstance()->GetCamera().y), long(reRect.left+GetWidth()), long(reRect.top + GetHeight())};

	pVM->DrawRect(reRect, 0, 255, 0);
}

void NPC::SaySomething() 
{
}

bool NPC::CheckCollision(IObjects* pBase) 
{
	return false;
}

