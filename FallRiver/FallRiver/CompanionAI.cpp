#include "CompanionAI.h"
#include "Weapon.h"
#include "Enemy.h"
#include "ViewManager.h"

CompanionAI::CompanionAI()
{
	SetVelX(0);
	SetVelY(0);
	m_nStages = 0;
}

CompanionAI::~CompanionAI()
{

}

void CompanionAI::Update(float fElapsedTime)
{
	switch(m_nStages)
	{
	// Using Flashlight
	case 0:
		{

			break;
		}
	// Attracting a zombies attention
	case 1:
		{
			break;
		}
	// Firing guns
	case 2:
		{
			break;
		}
	}
}

void CompanionAI::Render()
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 100, 148, 100);

		switch(m_nStages)
	{
	// Using Flashlight
	case 0:
		{

			break;
		}
	// Attracting a zombies attention
	case 1:
		{
			break;
		}
	// Firing guns
	case 2:
		{
			break;
		}
	}

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

