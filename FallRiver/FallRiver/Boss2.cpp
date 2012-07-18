#include <Windows.h>

#include "Boss2.h"
#include "ObjectFactory.h"
#include "BaseCharacter.h"
#include "Enemy.h"
#include "GamePlayState.h"
#include "EventSystem.h"
#include "Level.h"
#include "ObjectManager.h"
#include "DestroyEnemy.h"

Boss2::Boss2()
{

	m_nState = ESTATE_IDLE;
	m_pfDestination.x = 0;
	m_pfDestination.y = 0;
	m_dwIdleWait = 0;
	m_nVelX = 0;
	m_nVelY = 0;
	m_dwFireDelay = 0;
	m_pWeapon = nullptr;
	EventSystem::GetInstance()->RegisterClient( "bossWall_hit", this );
	EventSystem::GetInstance()->RegisterClient( "target_hit", this );

	//AnimInfo startup
	m_playerAnim.curAnimation = 0;
	m_playerAnim.curAnimID = 0;
	m_playerAnim.curFrame = 0;
	m_playerAnim.fTime = 0;
	m_pTarget = GamePlayState::GetInstance()->GetPlayer();
	chargeDestination.x =  m_pTarget->GetPosX();
	chargeDestination.y = m_pTarget->GetPosY();
	this->m_nCharacterType = CHA_BOSS2;
}

void Boss2::Update(float Time) 
{
	//BaseCharacter::Update(Time);
	if(GetHealth() <= 0)
	{
		DestroyEnemy* pMsg = new DestroyEnemy(this);
		MessageSystem::GetInstance()->SendMsg(pMsg);
		pMsg = nullptr;
	}

	if(  float(GetHealth()) / 1000.0f >= .75f )
	{
		if(m_nState == ESTATE_CHASING)
		{
			if( m_dwFireDelay == 0)
			{
				m_dwFireDelay = GetTickCount() + 1000;
				//m_dwGunReset = GetTickCount() + 100;
				m_nState = ESTATE_SHOOT;
			}
			if( m_dwFireDelay < GetTickCount() && m_nState == ESTATE_CHASING )
			{
				m_dwFireDelay = GetTickCount() + 1000;
				m_pWeapon->FireWeapon();
				m_nState = ESTATE_SHOOT;
				//m_dwGunReset = GetTickCount() + 100;
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
			//notified = true;
		}
		else
		{
			/*if(notified)
			AudioManager::GetInstance()->playSound(notifyID);		
			notified = false;*/
			m_nState = ESTATE_CHASING;
		}

		if( m_nState == ESTATE_CHASING)
		{
			if( ((distanceX < 300 && distanceX >= 150) || (distanceY < 300 && distanceY >= 150 )) && distanceX+distanceY < 300  )
			{
				//MoveTo(m_pTarget->GetPosX(), m_pTarget->GetPosY(), 80 );
				BaseCharacter::Update(Time);
			}
			else if( distanceY < 50 || distanceX < 50 )
			{
				if(m_pTarget->GetPosX() < GetPosX()+5 )
				{
					//MoveTo(GetPosX()+100, GetPosY(), 80);
					/*if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);*/
				}
				else if(m_pTarget->GetPosX() > GetPosX()-5 )
				{
					//MoveTo(GetPosX() - 100, GetPosY(), 80);
					/*if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);*/
				}
				//else
				//AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();

				BaseCharacter::Update(Time);

				if(m_pTarget->GetPosY() < GetPosY()+5 )
				{
					//MoveTo(GetPosX(), GetPosY()+100, 80);
					/*if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);*/
				}
				else if(m_pTarget->GetPosY() > GetPosY()-5 )
				{
					//MoveTo(GetPosX(), GetPosY()-100, 80);
					/*if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);*/
				}
				/*else
				AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();*/

				BaseCharacter::Update(Time);
			}
			//else
			//AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();
		}
	}
	else if( float(GetHealth()) / 1000.0f < .75f && float(GetHealth()) / 1000.0f >= .5f )
	{
		float distance = ( chargeDestination.x + chargeDestination.y ) - ( GetPosX() + GetPosY() );
		if((chargeDestination.x == 0 && chargeDestination.y == 0))
		{
			chargeDestination.x = m_pTarget->GetPosX();
			chargeDestination.y = m_pTarget->GetPosY();
		}

		if( distance > GetWidth() )
		{
			float savex = GetPosX();
			float savey = GetPosY();
			MoveTo(m_pTarget->GetPosX(), m_pTarget->GetPosY(), 90 );
			BaseCharacter::Update(Time);

			if( GamePlayState::GetInstance()->GetLevel()->CheckCollision(this) )
			{
				SetPosX(savex);
				SetPosY(savey);
			}
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
	}
	else
	{
		float distance = ( m_pTarget->GetPosX() + m_pTarget->GetPosY() ) - ( GetPosX() + GetPosY() );

		if( distance > GetWidth() )
		{
			float savex = GetPosX();
			float savey = GetPosY();
			MoveTo(m_pTarget->GetPosX(), m_pTarget->GetPosY(), 90 );
			BaseCharacter::Update(Time);

			if( GamePlayState::GetInstance()->GetLevel()->CheckCollision(this) )
			{
				SetPosX(savex);
				SetPosY(savey);
			}
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

	if(m_nState == PSTATE_SHOOT)
	{
		if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && m_playerAnim.curAnimation != 8)
		{
			m_playerAnim.curAnimation = 8;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && m_playerAnim.curAnimation != 9)
		{
			m_playerAnim.curAnimation = 9;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 11)
		{
			m_playerAnim.curAnimation = 11;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 10)
		{
			m_playerAnim.curAnimation = 10;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}

	}
	else
	{
		if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && m_playerAnim.curAnimation != 0 && GetVelY() == 0)
		{
			m_playerAnim.curAnimation = 0;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && m_playerAnim.curAnimation != 4 && GetVelY() < 0)
		{
			m_playerAnim.curAnimation = 4;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && m_playerAnim.curAnimation != 1 && GetVelY() == 0)
		{
			m_playerAnim.curAnimation = 1;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && m_playerAnim.curAnimation != 5 && GetVelY() > 0)
		{
			m_playerAnim.curAnimation = 5;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 3 && GetVelX() == 0)
		{
			m_playerAnim.curAnimation = 3;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 7 && GetVelX() > 0)
		{
			m_playerAnim.curAnimation = 7;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 2 && GetVelX() == 0)
		{
			m_playerAnim.curAnimation = 2;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 6 && GetVelX() < 0)
		{
			m_playerAnim.curAnimation = 6;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
	}

	//Updating the ShootingAi's frame and timer for animations
	Animation* thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	m_playerAnim.fTime += Time;

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

void Boss2::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();
	pVM->GetSprite()->Flush();
	RECT tmp = GetRect();
	pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x),  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y), 1.5f, 1.5f);
}

bool Boss2::CheckCollision(IObjects* pBase) 
{
	if( BaseCharacter::CheckCollision(pBase) == false)
		return false;

	return true;
}

void Boss2::HandleEvent(Event* Event) 
{
	if(Event->GetEventID() == "target_hit")
	{
		if( Event->GetParam() == this )
		{
			int i = this->GetHealth();
			int j = 0;
		}
	}


	if(Event->GetEventID() == "bossWall_hit")
	{
		if( Event->GetParam() == this )
		{
			chargeDestination.x = m_pTarget->GetPosX();
			chargeDestination.y = m_pTarget->GetPosY();
		}
	}

}

