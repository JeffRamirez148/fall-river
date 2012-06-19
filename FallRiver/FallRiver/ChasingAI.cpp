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

	if( (distance < 200 && distance > 2 || m_bIsChasing) && !m_bIsMoving )
	{
		m_bIsChasing = true;
		MoveTo(m_pTarget->GetPosX(), m_pTarget->GetPosY(), 80 );
		BaseCharacter::Update(fElapsedTime);
	}
	else if(m_bIsMoving)
	{
		SetCanMove(true);
		if(BaseCharacter::CheckCollision(m_cInTheWay) == false)
			m_bIsMoving = false;
		else if(m_cInTheWay->GetRect().left - GetRect().right <= 5)
		{
			float distToTop = float(GetRect().bottom - m_cInTheWay->GetRect().top);
			float distToBot = float(m_cInTheWay->GetRect().bottom -GetRect().top);

			if(distToTop <= distToBot)
				MoveTo(GetPosX(), (float)m_cInTheWay->GetRect().top-GetHeight(), 80);
			else
				MoveTo(GetPosX(), (float)m_cInTheWay->GetRect().bottom+5, 80);
		}
		else if(GetRect().left - m_cInTheWay->GetRect().right <= 5)
		{
			float distToTop = float(GetRect().bottom - m_cInTheWay->GetRect().top);
			float distToBot = float(m_cInTheWay->GetRect().bottom -GetRect().top);

			if(distToTop <= distToBot)
				MoveTo(GetPosX(), (float)m_cInTheWay->GetRect().top-GetHeight(), 80);
			else
				MoveTo(GetPosX(), (float)m_cInTheWay->GetRect().bottom+5, 80);

		}
		BaseCharacter::Update(fElapsedTime);

		if(GetRect().top - m_cInTheWay->GetRect().bottom <= 3)
			MoveTo(GetPosX(), GetPosY(), 80);
		else if(m_cInTheWay->GetRect().top - GetRect().bottom <= 3)
			MoveTo(GetPosX(), GetPosY(), 80);
		BaseCharacter::Update(fElapsedTime);
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
		if(pBase != m_pTarget && pBase->GetObjectType() == OBJ_CHARACTER)
		{
			m_cInTheWay = (BaseObject*)pBase;
			m_bIsMoving = true;
		}
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



