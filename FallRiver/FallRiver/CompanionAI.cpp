#include "CompanionAI.h"
#include "Weapon.h"
#include "Enemy.h"
#include "ViewManager.h"

CompanionAI::CompanionAI()
{
	SetVelX(0);
	SetVelY(0);
}

CompanionAI::~CompanionAI()
{

}

void CompanionAI::Update(float fElapsedTime)
{
	
}

void CompanionAI::Render()
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 100, 148, 100);
}

bool CompanionAI::CheckCollision(IObjects* pBase) 
{
	if( BaseCharacter::CheckCollision(pBase) )
		return true;
	return false;
}

void CompanionAI::HandleEvent(Event* aPEvent)
{
	
}

void CompanionAI::SaySomething() 
{
	
}

