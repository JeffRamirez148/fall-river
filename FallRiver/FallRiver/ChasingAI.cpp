#include "ChasingAI.h"
#include "DestroyEnemyC.h"
#include "MessageSystem.h"
#include "BaseCharacter.h"
#include "ViewManager.h"
#include "Event.h"
#include "EventSystem.h"
#include "Enemy.h"
#include "GamePlayState.h"

ChasingAI::ChasingAI()
{
	m_bIsMoving = false;
	m_bIsChasing = false;
	m_cInTheWay = nullptr;
	EventSystem::GetInstance()->RegisterClient( "target_hit", this );
}

ChasingAI::~ChasingAI()
{
	EventSystem::GetInstance()->UnregisterClient( "target_hit", this );
}

void ChasingAI::Update(float fElapsedTime)
{
	if(GetHealth() <= 0)
	{
		DestroyEnemyC* pMsg = new DestroyEnemyC(this);
		MessageSystem::GetInstance()->SendMsg(pMsg);
		pMsg = nullptr;
	}


	Enemy::Update(fElapsedTime);

	float distance = ( m_pTarget->GetPosX() + m_pTarget->GetPosY() ) - ( GetPosX() + GetPosY() );

	if( distance < 0)
		distance = -distance;

	if( distance < 200 && distance > 2 && CanMove() )
	{
		m_bIsChasing = true;
		MoveTo(m_pTarget->GetPosX(), m_pTarget->GetPosY(), 80 );
		BaseCharacter::Update(fElapsedTime);
	}
	else if( m_bIsChasing )
	{
		if(m_pTarget->GetPosX() < GetPosX() && !CanMove() )
		{
			RECT fRect = m_cInTheWay->GetRect();
			if( fRect.right <= GetRect().left)
			{

			}
		}
		else if(m_pTarget->GetPosX() > GetPosX())
		{

		}
	}
}

void ChasingAI::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 255, 0, 0);
}

bool ChasingAI::CheckCollision(IObjects* pBase) 
{
	if(Enemy::CheckCollision(pBase))
	{
		if(pBase != m_pTarget)
			m_cInTheWay = (BaseObject*)pBase;
		return true;
	}
	return false;
}

void ChasingAI::HandleEvent(Event* pEvent)
{
	if(pEvent->GetEventID() == "target_hit")
	{
		if( pEvent->GetParam() == this )
		{
			SetHealth(GetHealth()-30);
		}
	}
}



