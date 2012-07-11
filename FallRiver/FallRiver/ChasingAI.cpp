#include "ChasingAI.h"
#include "DestroyEnemyC.h"
#include "MessageSystem.h"
#include "BaseCharacter.h"
#include "ViewManager.h"
#include "Event.h"
#include "CGame.h"
#include "EventSystem.h"
#include "Enemy.h"
#include "GamePlayState.h"
#include "Level.h"
#include "AudioManager.h"

ChasingAI::ChasingAI()
{
	m_cInTheWay = nullptr;
	m_nState = ESTATE_IDLE;

	m_pfDestination.x = 0;
	m_pfDestination.y = 0;
	m_dwIdleWait = 0;
	attackDelay = 0;
	EventSystem::GetInstance()->RegisterClient( "target_hit", this );

	AudioManager* m_pAM = AudioManager::GetInstance();
	zombieHitID = m_pAM->RegisterSound("resource/Sounds/zombieHit.mp3");
	zombieWalkingID = m_pAM->RegisterSound("resource/Sounds/zombieWalking.mp3");
	notifyID = m_pAM->RegisterSound("resource/Sounds/notify.mp3");
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	m_pAM->setSoundVel(zombieHitID, sound1);
	m_pAM->setSoundVel(zombieWalkingID, sound1);
	m_pAM->setSoundVel(notifyID, sound1);
	sound1.x = m_nPosX;
	sound1.y = m_nPosY;
	m_pAM->setSoundPos(zombieWalkingID, sound1);
	m_pAM->setSoundLooping(zombieWalkingID, true);
	m_pAM->setSoundPos(zombieHitID, sound1);
	m_pAM->setSoundLooping(zombieHitID, false);
	m_pAM->setSoundPos(notifyID, sound1);
	m_pAM->setSoundLooping(notifyID, false);
	notified = false;

	//AnimInfo startup
	m_playerAnim.curAnimation = 0;
	m_playerAnim.curAnimID = 0;
	m_playerAnim.curFrame = 0;
	m_playerAnim.fTime = 0;
}

ChasingAI::~ChasingAI()
{
	EventSystem::GetInstance()->UnregisterClient( "target_hit", this );
}

void ChasingAI::Update(float fElapsedTime)
{
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	sound1.x = m_nPosX;
	sound1.y = m_nPosY;
	AudioManager* m_pAM = AudioManager::GetInstance();
	m_pAM->setSoundPos(zombieWalkingID, sound1);
	m_pAM->setSoundPos(zombieHitID, sound1);

	if(GetHealth() <= 0)
	{
		DestroyEnemyC* pMsg = new DestroyEnemyC(this);
		MessageSystem::GetInstance()->SendMsg(pMsg);
		pMsg = nullptr;
	}

	float distance = ( m_pTarget->GetPosX() + m_pTarget->GetPosY() ) - ( GetPosX() + GetPosY() );
	float distX = GetPosX() - m_pTarget->GetPosX();
	float distY = GetPosY() - m_pTarget->GetPosY();

	if( distance < 0)
		distance = -distance;
	if( distX < 0)
		distX = -distX;
	if( distY < 0)
		distY = -distY;

	if( (distX < 10 && distY < 10) || (distX-m_pTarget->GetWidth() < 10 && distY - m_pTarget->GetHeight() < 10))
	{
		if( attackDelay < GetTickCount() )
		{
			m_pTarget->SetHealth(m_pTarget->GetHealth()-5);
			attackDelay = GetTickCount() + 1000;
		}
		return;
	}

	if( m_pTarget->IsOn() && m_nState == ESTATE_IDLE && distance < 400 )
	{
		float targetPosX = m_pTarget->GetPosX();
		float targetPosY = m_pTarget->GetPosY();

		if( m_pTarget->GetLightType() == 0 )
		{
			if( targetPosX < m_nPosX && m_pTarget->GetDirection() == DIRE_RIGHT )
				m_nState = ESTATE_CHASING;
			else if( targetPosX > m_nPosX && m_pTarget->GetDirection() == DIRE_LEFT )
				m_nState = ESTATE_CHASING;
			else if( targetPosY < m_nPosY && m_pTarget->GetDirection() == DIRE_DOWN )
				m_nState = ESTATE_CHASING;
			else if( targetPosY > m_nPosY && m_pTarget->GetDirection() == DIRE_UP )
				m_nState = ESTATE_CHASING;
		}
	}
	else if( ((distance >= 200) || m_pTarget->CheckHidden() ) && !m_pTarget->IsOn() )
	{
		if(  m_pTarget->CheckHidden() )
		{
			m_nState = ESTATE_IDLE;
		}
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
			m_pfDestination.x = GetPosX()+rand()%100-50;
			m_pfDestination.y = GetPosY()+rand()%100-50;
			m_dwIdleWait = GetTickCount() + 1000;
		}
		if( fDistX  > 10 && fDistY > 10 )
		{
			float savex = GetPosX();
			float savey = GetPosY();

			MoveTo(m_pfDestination.x, m_pfDestination.y, 50);
			if(!AudioManager::GetInstance()->isSoundPlaying(zombieWalkingID))
				AudioManager::GetInstance()->playSound(zombieWalkingID);
			BaseCharacter::Update(fElapsedTime);

			if( GamePlayState::GetInstance()->GetLevel()->CheckCollision(this) )
			{
				SetPosX(savex);
				SetPosY(savey);
			}
		}
		else
			AudioManager::GetInstance()->GetSoundChannel(zombieWalkingID)->stop();

		if(GetVelX() > 0)
		{
			if( GetVelY() < 0 )
				SetDirection(DIRE_UPRIGHT);
			else if( GetVelY() > 0 )
				SetDirection(DIRE_DOWNRIGHT);
			else
				SetDirection(DIRE_RIGHT);

			m_playerAnim.curAnimation = -1;
		}
		else if(GetVelX() < 0)
		{
			if( GetVelY() < 0 )
				SetDirection(DIRE_UPLEFT);
			else if( GetVelY() > 0 )
				SetDirection(DIRE_DOWNLEFT);
			else
				SetDirection(DIRE_LEFT);
		}
		else if( GetVelY() < 0 )
			SetDirection(DIRE_UP);
		else if( GetVelY() > 0 )
			SetDirection(DIRE_DOWN);
	}
	else if( m_nState == ESTATE_CHASING)
	{
		if( distance > GetWidth() && !m_cInTheWay )
		{
			float savex = GetPosX();
			float savey = GetPosY();
			MoveTo(m_pTarget->GetPosX(), m_pTarget->GetPosY(), 80 );
			if(!AudioManager::GetInstance()->isSoundPlaying(zombieWalkingID))
				AudioManager::GetInstance()->playSound(zombieWalkingID);
			BaseCharacter::Update(fElapsedTime);

			if( GamePlayState::GetInstance()->GetLevel()->CheckCollision(this) )
			{
				SetPosX(savex);
				SetPosY(savey);
			}
		}
		else
			AudioManager::GetInstance()->GetSoundChannel(zombieWalkingID)->stop();

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
	else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 2 && GetVelX() == 0)
	{
		m_playerAnim.curAnimation = 2;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}
	else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 6 && GetVelX() > 0)
	{
		m_playerAnim.curAnimation = 6;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}
	else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 3 && GetVelX() == 0)
	{
		m_playerAnim.curAnimation = 3;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}
	else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 7 && GetVelX() < 0)
	{
		m_playerAnim.curAnimation = 7;
		m_playerAnim.curFrame = 0;
		m_playerAnim.fTime = 0;
	}

	//Updating the ChasingAI's frame and timer for animations
	Animation thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	m_playerAnim.fTime += fElapsedTime;

	if(m_playerAnim.fTime >= thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].duration)
	{
		m_playerAnim.fTime -= thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].duration;
		m_playerAnim.curFrame++;
		if(m_playerAnim.curFrame < (int)thisAnim.frames[m_playerAnim.curAnimation].size())
		{
			if(strcmp(thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].eventMsg,"none") != 0)
				EventSystem::GetInstance()->SendEvent(thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame].eventMsg, this);
		}
		if((m_playerAnim.curFrame == thisAnim.frames[m_playerAnim.curAnimation].size()) && thisAnim.looping[m_playerAnim.curAnimation])
			m_playerAnim.curFrame = 0;
		else if(m_playerAnim.curFrame == thisAnim.frames[m_playerAnim.curAnimation].size() && !thisAnim.looping[m_playerAnim.curAnimation])
			m_playerAnim.curFrame = thisAnim.frames.size() -1;
	}
}

void ChasingAI::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();
	Player* tmp = GamePlayState::GetInstance()->GetPlayer();
	if(GetShadow())
		if(tmp->IsOn() && tmp->GetLightType() < 2 )
		{
			if(tmp->GetDirection() == 1)
				pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.5f, 1.5f);
			else if(tmp->GetDirection() < 4 && tmp->GetDirection() != 1)
				pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.5f, 1.5f);
			else
			{
				switch(tmp->GetDirection())
				{
				case 4:
				pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.5f, 1.5f);
					break;
				case 5:
				pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.5f, 1.5f);
					break;
				case 6:
				pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.5f, 1.5f);
					break;
				case 7:
				pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.5f, 1.5f);
					break;
				default:
					break;
				}	
			}
		}
		else if( tmp->IsOn() )
			pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.5f, 1.5f);

	pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.5f, 1.5f);

	//RECT reRect = {long(GetPosX() - GamePlayState::GetInstance()->GetCamera().x), long(GetPosY() - GamePlayState::GetInstance()->GetCamera().y), long(reRect.left+GetWidth()), long(reRect.top + GetHeight())};

	//pVM->DrawRect(reRect, 255, 0, 0);
}

bool ChasingAI::CheckCollision(IObjects* pBase) 
{
	if(Enemy::CheckCollision(pBase))
	{
		if(pBase != m_pTarget && pBase->GetObjectType() != OBJ_BUSH)
			m_cInTheWay = (BaseObject*)pBase;
		return true;
	}
	m_cInTheWay = nullptr;
	return false;
}

void ChasingAI::HandleEvent(Event* pEvent)
{
	if(pEvent->GetEventID() == "target_hit")
	{
		if( pEvent->GetParam() == this )
		{
			SetHealth(GetHealth()-30);
			AudioManager::GetInstance()->playSound(zombieHitID);
		}
	}
}



