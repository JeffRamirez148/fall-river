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
	m_bIsMoving = false;
	m_cInTheWay = nullptr;
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

	//float distance = ( m_pTarget->GetPosX() + m_pTarget->GetPosY() ) - ( GetPosX() + GetPosY() );

	//if( distance < 0)
	//	distance = -distance;

	//if( distance < 300 && distance > 2 && !m_bIsMoving)
	//{
	//	MoveTo(m_pTarget->GetPosX(), m_pTarget->GetPosY(), 80 );
	//	BaseCharacter::Update(fElapsedTime);
	//}
}

void ShootingAi::Render()
{
	// Do Rendering here
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 100, 148, 100);
}

bool ShootingAi::CheckCollision(IObjects* pBase)
{
	if(Enemy::CheckCollision(pBase))
	{
		if(pBase != m_pTarget && pBase->GetObjectType() == OBJ_CHARACTER)
		{
			m_cInTheWay = (BaseObject*)pBase;
			m_bIsMoving = true;
		}
		return true;
	}
	return false;
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

