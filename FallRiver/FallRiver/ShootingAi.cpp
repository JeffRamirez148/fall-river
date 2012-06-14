#include "ShootingAi.h"
#include "ObjectFactory.h"
#include "DestroyEnemyS.h"
#include "ViewManager.h"
#include "Enemy.h"

ShootingAi::ShootingAi()
{
	m_nVelX = 0;
	m_nVelY = 0;
}

ShootingAi::~ShootingAi()
{

}

void ShootingAi::Update(float fElapsedTime) 
{
	Enemy::Update(fElapsedTime);
}

void ShootingAi::Render()
{
	// Do Rendering here
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 100, 148, 100);
}

bool ShootingAi::CheckCollision(BaseCharacter* aPBase)
{
	return true;
}

void ShootingAi::HandleEvent(Event* aPEvent)
{
	
}

