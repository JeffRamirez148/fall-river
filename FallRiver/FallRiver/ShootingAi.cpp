#include "ShootingAi.h"
#include "ObjectFactory.h"
#include "DestroyEnemyS.h"
#include "ViewManager.h"
#include "Enemy.h"
#include "EventSystem.h"
#include "MessageSystem.h"
#include "DestroyEnemyS.h"
#include "GamePlayState.h"
#include "CreateBullet.h"
#include "Weapon.h"
#include "CGame.h"
#include "AudioManager.h"

ShootingAi::ShootingAi()
{
	m_cInTheWay = nullptr;
	m_nState = ESTATE_IDLE;
	m_pfDestination.x = 0;
	m_pfDestination.y = 0;
	m_dwIdleWait = 0;
	m_nVelX = 0;
	m_nVelY = 0;
	m_dwFireDelay = 0;
	m_pWeapon = nullptr;
	EventSystem::GetInstance()->RegisterClient( "target_hit", this );
	hitID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/hit.aiff");
	walkingID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/walking.aiff");
	notifyID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/notify.mp3");
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	AudioManager::GetInstance()->setSoundVel(hitID, sound1);
	AudioManager::GetInstance()->setSoundVel(walkingID, sound1);
	AudioManager::GetInstance()->setSoundVel(notifyID, sound1);
	sound1.x = m_nPosX;
	sound1.y = m_nPosY;
	AudioManager::GetInstance()->setSoundPos(walkingID, sound1);
	AudioManager::GetInstance()->setSoundLooping(walkingID, true);
	AudioManager::GetInstance()->setSoundPos(hitID, sound1);
	AudioManager::GetInstance()->setSoundLooping(hitID, false);
	AudioManager::GetInstance()->setSoundPos(notifyID, sound1);
	AudioManager::GetInstance()->setSoundLooping(notifyID, false);
	notified = false;
}

ShootingAi::~ShootingAi()
{
	EventSystem::GetInstance()->UnregisterClient( "target_hit", this );
}

void ShootingAi::Update(float fElapsedTime) 
{
	FMOD_VECTOR sound1 = { m_nPosX, m_nPosY, 0};
	AudioManager::GetInstance()->setSoundPos(walkingID, sound1);
	AudioManager::GetInstance()->setSoundPos(hitID, sound1);
	if(GetHealth() <= 0)
	{
		DestroyEnemyS* pMsg = new DestroyEnemyS(this);
		MessageSystem::GetInstance()->SendMsg(pMsg);
		pMsg = nullptr;
	}

	m_pWeapon->Update(fElapsedTime);
	
	if(m_nState == ESTATE_CHASING)
	{
		if( m_dwFireDelay == 0)
			m_dwFireDelay = GetTickCount() + 1000;
		if( m_dwFireDelay < GetTickCount() && m_nState == ESTATE_CHASING )
		{
			m_dwFireDelay = GetTickCount() + 1000;
			m_pWeapon->FireWeapon();
		}
	}

	float distanceX = ( m_pTarget->GetPosX() -  GetPosX() );
	float distanceY = ( m_pTarget->GetPosY() -  GetPosY() );

	if( distanceX < 0)
		distanceX = -distanceX;
	if( distanceY < 0)
		distanceY = -distanceY;

	if( (distanceX + distanceY >= 300) || m_pTarget->CheckHidden() )
	{
		m_nState = ESTATE_IDLE;
		notified = true;
	}
	else
	{
		if(notified)
			AudioManager::GetInstance()->playSound(notifyID);		
		notified = false;
		m_nState = ESTATE_CHASING;
	}

	if( m_nState == ESTATE_IDLE )
	{
		float fDistX = m_pfDestination.x - GetPosX();
		float fDistY = m_pfDestination.y - GetPosY();

		if(fDistX < 0)
			fDistX = -fDistX;
		if(fDistY < 0)
			fDistY = -fDistY;

		if( ((m_pfDestination.x == 0 && m_pfDestination.y == 0) || (fDistX  <= 10 || fDistY <= 10)) && m_dwIdleWait < GetTickCount()  )
		{
			m_pfDestination.x = GetPosX()+rand()%200-100; 
			m_pfDestination.y = GetPosY()+rand()%200-100;
			m_dwIdleWait = GetTickCount() + 1000;
		}
		if( fDistX  > 10 && fDistY > 10 )
		{
			MoveTo(m_pfDestination.x, m_pfDestination.y, 50);
			BaseCharacter::Update(fElapsedTime);
		}
		else
			AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();
	}
	else if( m_nState == ESTATE_CHASING)
	{
		if( ((distanceX < 300 && distanceX >= 150) || (distanceY < 300 && distanceY >= 150 )) && distanceX+distanceY < 300  )
		{
			MoveTo(m_pTarget->GetPosX(), m_pTarget->GetPosY(), 80 );
			BaseCharacter::Update(fElapsedTime);
		}
		else if( distanceY < 50 || distanceX < 50 )
		{
			if(m_pTarget->GetPosX() < GetPosX()+5 )
			{
				MoveTo(GetPosX()+100, GetPosY(), 80);
				if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);
			}
			else if(m_pTarget->GetPosX() > GetPosX()-5 )
			{
				MoveTo(GetPosX() - 100, GetPosY(), 80);
				if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);
			}
			else
				AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();

			BaseCharacter::Update(fElapsedTime);

			if(m_pTarget->GetPosY() < GetPosY()+5 )
			{
				MoveTo(GetPosX(), GetPosY()+100, 80);
				if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);
			}
			else if(m_pTarget->GetPosY() > GetPosY()-5 )
			{
				MoveTo(GetPosX(), GetPosY()-100, 80);
				if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);
			}
			else
				AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();

			BaseCharacter::Update(fElapsedTime);
		}
		else
			AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();
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

	ViewManager* pVM = ViewManager::GetInstance();

	RECT reRect = {long(GetPosX() - GamePlayState::GetInstance()->GetCamera().x), long(GetPosY() - GamePlayState::GetInstance()->GetCamera().y), long(reRect.left+GetWidth()), long(reRect.top + GetHeight())};

	pVM->DrawRect(reRect, 255, 255, 0);
}

bool ShootingAi::CheckCollision(IObjects* pBase)
{
	if(Enemy::CheckCollision(pBase))
	{
		if(pBase != m_pTarget && pBase->GetObjectType() == OBJ_CHARACTER)
		{
			m_cInTheWay = (BaseObject*)pBase;
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
			AudioManager::GetInstance()->playSound(hitID);
		}
	}
}

