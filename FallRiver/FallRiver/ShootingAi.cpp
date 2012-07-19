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
#include "Level.h"
#include "Weapon.h"
#include "Bullet.h"
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
	m_dwGunReset = 0;
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
	boss = false;
	//AnimInfo startup
	m_playerAnim.curAnimation = 0;
	m_playerAnim.curAnimID = 0;
	m_playerAnim.curFrame = 0;
	m_playerAnim.fTime = 0;
	autoBotsRollOut = 0;
}

ShootingAi::~ShootingAi()
{
	EventSystem::GetInstance()->UnregisterClient( "target_hit", this );
}

void ShootingAi::Update(float fElapsedTime) 
{
	++autoBotsRollOut;
	if( autoBotsRollOut > 1 )
	{
	BaseCharacter::Update(fElapsedTime);

	FMOD_VECTOR sound1 = { m_nPosX, m_nPosY, 0};
	AudioManager::GetInstance()->setSoundPos(walkingID, sound1);
	AudioManager::GetInstance()->setSoundPos(hitID, sound1);
	if(GetHealth() <= 0)
	{
		DestroyEnemyS* pMsg = new DestroyEnemyS(this);
		MessageSystem::GetInstance()->SendMsg(pMsg);
		pMsg = nullptr;
	}
	if(  m_pTarget->CheckHidden() )
		m_nState = ESTATE_IDLE;

	m_pWeapon->Update(fElapsedTime);
	
	if(m_nState == ESTATE_CHASING)
	{
		if( m_dwFireDelay == 0)
		{
			m_dwFireDelay = GetTickCount() + 1000;
			m_dwGunReset = GetTickCount() + 100;
			m_nState = ESTATE_SHOOT;
		}
		if( m_dwFireDelay < GetTickCount() && m_nState == ESTATE_CHASING )
		{
			m_dwFireDelay = GetTickCount() + 1000;
			m_pWeapon->FireWeapon();
			m_nState = ESTATE_SHOOT;
			m_dwGunReset = GetTickCount() + 100;
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
			m_pfDestination.x = GetPosX()+rand()%25-12; 
			m_pfDestination.y = GetPosY()+rand()%25-12;
			m_dwIdleWait = GetTickCount() + 1000;
		}
		if( fDistX  > 10 && fDistY > 10 )
		{
			float savex = GetPosX();
			float savey = GetPosY();

			MoveTo(m_pfDestination.x, m_pfDestination.y, 50);
			BaseCharacter::Update(fElapsedTime);

			if( GamePlayState::GetInstance()->GetLevel()->CheckCollision(this) )
			{
				SetPosX(savex);
				SetPosY(savey);
			}
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

	if(m_pTarget->GetPosX() > GetPosX()+30)
	{
		if(m_pTarget->GetPosY() > GetPosY()+30)
			SetDirection(DIRE_DOWNRIGHT);
		else if(m_pTarget->GetPosY() < GetPosY()-30)
			SetDirection(DIRE_UPRIGHT);
		else
			SetDirection(DIRE_RIGHT);
	}
	else if(m_pTarget->GetPosX() < GetPosX()-30)
	{
		if(m_pTarget->GetPosY() > GetPosY()+30)
			SetDirection(DIRE_DOWNLEFT);
		else if(m_pTarget->GetPosY() < GetPosY()-30)
			SetDirection(DIRE_UPLEFT);
		else
			SetDirection(DIRE_LEFT);
	}
	else if(m_pTarget->GetPosY() > GetPosY())
		SetDirection(DIRE_DOWN);
	else if(m_pTarget->GetPosY() < GetPosY())
		SetDirection(DIRE_UP);

	if(m_nState == ESTATE_SHOOT)
	{
		if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && m_playerAnim.curAnimation != 4)
		{
			m_playerAnim.curAnimation = 4;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && m_playerAnim.curAnimation != 6)
		{
			m_playerAnim.curAnimation = 6;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 5)
		{
			m_playerAnim.curAnimation = 5;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 7)
		{
			m_playerAnim.curAnimation = 7;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}

	}
	else
	{
		if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && GetVelY() == 0)
		{
			m_playerAnim.curAnimation = 0;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && m_playerAnim.curAnimation != 4 && GetVelY() < 0)
		{
			m_playerAnim.curAnimation = 0;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && GetVelY() == 0)
		{
			m_playerAnim.curAnimation = 2;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && m_playerAnim.curAnimation != 2 && GetVelY() > 0)
		{
			m_playerAnim.curAnimation = 2;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_RIGHT && GetVelX() == 0)
		{
			m_playerAnim.curAnimation = 1;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 1 && GetVelX() > 0)
		{
			m_playerAnim.curAnimation = 1;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_LEFT  && GetVelX() == 0)
		{
			m_playerAnim.curAnimation = 3;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 3 && GetVelX() < 0)
		{
			m_playerAnim.curAnimation = 3;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
	}

	//Updating the ShootingAi's frame and timer for animations
	Animation* thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	m_playerAnim.fTime += fElapsedTime;

	if(m_playerAnim.fTime >= thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].duration)
	{
		m_playerAnim.fTime -= thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].duration;
		m_playerAnim.curFrame++;
		if(m_playerAnim.curFrame < (int)thisAnim->frames[m_playerAnim.curAnimation].size())
		{
			if(strcmp(thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].eventMsg,"none") != 0)
				EventSystem::GetInstance()->SendEvent(thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].eventMsg, this);
		}
		if((m_playerAnim.curFrame == thisAnim->frames[m_playerAnim.curAnimation].size()) && thisAnim->looping[m_playerAnim.curAnimation])
			m_playerAnim.curFrame = 0;
		else if(m_playerAnim.curFrame == thisAnim->frames[m_playerAnim.curAnimation].size() && !thisAnim->looping[m_playerAnim.curAnimation])
			m_playerAnim.curFrame--;
	}
	}
}

void ShootingAi::Render()
{
	// Do Rendering here

	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.0f, 1.0f);
	BaseCharacter::Render();

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
			AudioManager::GetInstance()->playSound(hitID);
			this->SetBleeding(true);

		}
	}
}

