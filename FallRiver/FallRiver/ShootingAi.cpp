#include "ShootingAi.h"
#include "ObjectFactory.h"
#include "DestroyEnemyS.h"
#include "ViewManager.h"
#include "Enemy.h"
#include "EventSystem.h"
#include "MessageSystem.h"
#include "DestroyEnemyS.h"

ShootingAi::ShootingAi()
{
	m_nVelX = 0;
	m_nVelY = 0;
	EventSystem::GetInstance()->RegisterClient( "target_hit", this );
}

ShootingAi::~ShootingAi()
{
	EventSystem::GetInstance()->UnregisterClient( "target_hit", this );
}

void ShootingAi::Update(float fElapsedTime) 
{
	if(GetHealth() <= 0)
	{
		DestroyEnemyS* pMsg = new DestroyEnemyS(this);
		MessageSystem::GetInstance()->SendMsg(pMsg);
		pMsg = nullptr;
	}

	Enemy::Update(fElapsedTime);
}

void ShootingAi::Render()
{
	// Do Rendering here
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 100, 148, 100);
}

bool ShootingAi::CheckCollision(IObjects* pBase)
{
	return Enemy::CheckCollision(pBase);
}

void ShootingAi::HandleEvent(Event* pEvent)
{
	if(pEvent->GetEventID() == "target_hit")
	{
		if( pEvent->GetParam() == this )
		{
			SetHealth(GetHealth()-30);
		}
	}
}

