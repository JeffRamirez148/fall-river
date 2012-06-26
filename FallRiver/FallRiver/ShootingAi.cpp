#include "ShootingAi.h"
#include "ObjectFactory.h"
#include "DestroyEnemyS.h"
#include "ViewManager.h"
#include "Enemy.h"
#include "EventSystem.h"
#include "MessageSystem.h"
#include "DestroyEnemyS.h"
#include "CreateBullet.h"
#include "Weapon.h"
#include "CGame.h"

ShootingAi::ShootingAi()
{
	m_bIsMoving = false;
	m_cInTheWay = nullptr;
	m_nVelX = 0;
	m_nVelY = 0;
	m_dwFireDelay = 0;
	m_pWeapon = nullptr;
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

	m_pWeapon->Update(fElapsedTime);

	if( m_dwFireDelay == 0)
		m_dwFireDelay = GetTickCount() + 1000;
	if( m_dwFireDelay < GetTickCount() && m_bIsChasing )
	{
		m_dwFireDelay = GetTickCount() + 1000;
		m_pWeapon->FireWeapon();
	}

	Enemy::Update(fElapsedTime);

	float distanceX = ( m_pTarget->GetPosX() -  GetPosX() );
	float distanceY = ( m_pTarget->GetPosY() -  GetPosY() );

	if( distanceX < 0)
		distanceX = -distanceX;
	if( distanceY < 0)
		distanceY = -distanceY;

	if( (distanceX < 200 && distanceX >= 50) || (distanceY < 200 && distanceY >= 50 ) )
	{
		m_bIsChasing = true;
		MoveTo(m_pTarget->GetPosX(), m_pTarget->GetPosY(), 80 );
		BaseCharacter::Update(fElapsedTime);
	}
	else if( distanceY < 50 || distanceX < 50 )
	{
		if(m_pTarget->GetPosX() < GetPosX()+5 )
			MoveTo(GetPosX()+100, GetPosY(), 80);
		else if(m_pTarget->GetPosX() > GetPosX()-5 )
			MoveTo(GetPosX() - 100, GetPosY(), 80);
		BaseCharacter::Update(fElapsedTime);

		if(m_pTarget->GetPosY() < GetPosY()+5 )
			MoveTo(GetPosX(), GetPosY()+100, 80);
		else if(m_pTarget->GetPosY() > GetPosY()-5 )
			MoveTo(GetPosX(), GetPosY()-100, 80);

		BaseCharacter::Update(fElapsedTime);
	}

	if(m_pTarget->GetPosX() > GetPosX()+10)
	{
		if(m_pTarget->GetPosY() > GetPosY()+10)
			SetDirection(DIRE_DOWNRIGHT);
		else if(m_pTarget->GetPosY() < GetPosY()-10)
			SetDirection(DIRE_UPRIGHT);
		else
			SetDirection(DIRE_RIGHT);
	}
	else if(m_pTarget->GetPosX() < GetPosX()-10)
	{
		if(m_pTarget->GetPosY() > GetPosY()+10)
			SetDirection(DIRE_DOWNLEFT);
		else if(m_pTarget->GetPosY() < GetPosY()-10)
			SetDirection(DIRE_UPLEFT);
		else
			SetDirection(DIRE_LEFT);
	}
	else if(m_pTarget->GetPosY() > GetPosY())
		SetDirection(DIRE_DOWN);
	else if(m_pTarget->GetPosY() < GetPosY())
		SetDirection(DIRE_UP);
}

void ShootingAi::Render()
{
	// Do Rendering here
	if(GetPosX()+GetWidth() < 0 || GetPosY()+GetHeight() < 0 || GetPosX() > CGame::GetInstance()->GetScreenWidth() || GetPosY() > CGame::GetInstance()->GetScreenHeight() )
		return;
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

