#include "Boss1.h"
#include "ObjectFactory.h"
#include "BaseCharacter.h"
#include "MessageSystem.h"
#include <tchar.h>
#include "Enemy.h"
#include "ViewManager.h"
#include "ShootingAi.h"
#include "DestroyEnemy.h"
#include "EventSystem.h"
#include "Bullet.h"
#include "Level.h"
#include "GamePlayState.h"
#include "AudioManager.h"
#include "Weapon.h"
#include "GamePlayState.h"
#include "ChasingAI.h"
#include "ShootingAi.h"


Boss1::Boss1()
{
	m_cInTheWay = nullptr;
	m_nState = ESTATE_IDLE;
	m_pfDestination.x = 0;
	m_pfDestination.y = 0;
	m_dwIdleWait = 0;
	m_nVelX = 0;
	m_nVelY = 0;
	m_nSpawnCounter = 0;
	m_nStages = 0;
	m_dwFireDelay = 0;
	m_pWeapon = nullptr;
	EventSystem::GetInstance()->RegisterClient( "target_hit", this );

	//AnimInfo startup
	m_playerAnim.curAnimation = 0;
	m_playerAnim.curAnimID = 0;
	m_playerAnim.curFrame = 0;
	m_playerAnim.fTime = 0;
	m_fSpawnTime = 0;
	oldSize = 0;
	enemies = 0;
	m_pOM = ObjectManager::GetInstance();
	m_pOF = Factory::GetInstance();
}

Boss1::~Boss1()
{

}

void Boss1::Update(float fElapsedTime)
{
	BaseCharacter::Update(fElapsedTime);
	//FMOD_VECTOR sound1 = { m_nPosX, m_nPosY, 0};
	//AudioManager::GetInstance()->setSoundPos(walkingID, sound1);
	//AudioManager::GetInstance()->setSoundPos(hitID, sound1);
	if(GetHealth() <= 0)
	{
		DestroyEnemy* pMsg = new DestroyEnemy(this);
		MessageSystem::GetInstance()->SendMsg(pMsg);
		pMsg = nullptr;
	}

	m_pWeapon->Update(fElapsedTime);
	m_fSpawnTime += fElapsedTime;

	//if(oldSize > GamePlayState::GetInstance()->GetEnemies().size())
	//	for( int i = 0; i < oldSize - GamePlayState::GetInstance()->GetEnemies().size(); ++i)
	//			m_cEnemies.erase(m_cEnemies.begin());

	if( m_nStages == 0 )
	{
		if( m_fSpawnTime > 3 )
		{
			if( m_nSpawnCounter < 1 )
			{
				m_cEnemies.push_back(nullptr);
				m_cEnemies[m_cEnemies.size()-1] = (ShootingAi*)m_pOF->CreateObject( _T("ShootingAi") );
				ShootingAi* pEnemy = (ShootingAi*)(m_cEnemies[m_cEnemies.size()-1]);
				pEnemy->SetHeight(GetHeight());
				pEnemy->SetWidth(GetWidth());
				pEnemy->SetImageID(-1);
				pEnemy->SetTarget(GamePlayState::GetInstance()->GetPlayer());
				pEnemy->SetPosX(GetPosX()+(rand()%20-10));
				pEnemy->SetPosY(GetPosY()+(rand()%20-10));
				pEnemy->SetHealth(100);
				pEnemy->SetBossBool(true);
				pEnemy->SetAnimation(ViewManager::GetInstance()->RegisterAnimation("resource/graphics/BanditAnimations.xml"));
				m_pOM->AddObject(pEnemy);
				GamePlayState::GetInstance()->AddEnemy(m_cEnemies[m_cEnemies.size()-1]);
				Weapon* eWeapon = (Weapon*)m_pOF->CreateObject( _T("Weapon"));
				eWeapon->SetHeight(20);
				eWeapon->SetWidth(10);
				eWeapon->SetImageID(-1);
				eWeapon->SetOwner(pEnemy);
				eWeapon->Init(WPN_PISTOL, 100, 0);
				eWeapon->SetPosX(pEnemy->GetPosX()+pEnemy->GetWidth()/2);
				eWeapon->SetPosY(pEnemy->GetPosY());
				pEnemy->SetWeapon(eWeapon);
				oldSize = GamePlayState::GetInstance()->GetEnemies().size();
				m_fSpawnTime = 0;
				m_nSpawnCounter++;
				enemies++;
			}
			else if(enemies <= 0)
			{
				m_nStages = 1;
				m_nSpawnCounter = 0;
				m_fSpawnTime = 0;
			}
		}
	}
	else if( m_nStages == 1 )
	{
		if( m_fSpawnTime > 3 )
		{
			if( m_nSpawnCounter < 1 )
			{
				m_cEnemies.push_back(nullptr);
				m_cEnemies[m_cEnemies.size()-1] = (ShootingAi*)m_pOF->CreateObject( _T("ShootingAi") );
				ShootingAi* pEnemy = (ShootingAi*)(m_cEnemies[m_cEnemies.size()-1]);
				pEnemy->SetHeight(GetHeight());
				pEnemy->SetWidth(GetWidth());
				pEnemy->SetImageID(-1);
				pEnemy->SetTarget(GamePlayState::GetInstance()->GetPlayer());
				pEnemy->SetPosX(GetPosX()+(rand()%20-10));
				pEnemy->SetPosY(GetPosY()+(rand()%20-10));
				pEnemy->SetHealth(100);
				pEnemy->SetBossBool(true);
				pEnemy->SetAnimation(ViewManager::GetInstance()->RegisterAnimation("resource/graphics/BanditAnimations.xml"));
				m_pOM->AddObject(pEnemy);
				GamePlayState::GetInstance()->AddEnemy(m_cEnemies[m_cEnemies.size()-1]);
				GamePlayState::GetInstance()->AddEnemy(m_cEnemies[m_cEnemies.size()-1]);
				Weapon* eWeapon = (Weapon*)m_pOF->CreateObject( _T("Weapon"));
				eWeapon->SetHeight(20);
				eWeapon->SetWidth(10);
				eWeapon->SetImageID(-1);
				eWeapon->SetOwner(pEnemy);
				eWeapon->Init(WPN_PISTOL, 100, 0);
				eWeapon->SetPosX(pEnemy->GetPosX()+pEnemy->GetWidth()/2);
				eWeapon->SetPosY(pEnemy->GetPosY());
				pEnemy->SetWeapon(eWeapon);

				m_fSpawnTime = 0;
				m_nSpawnCounter++;
				enemies++;
			}
			else if(enemies <= 0)
			{
				m_nStages = 2;
				m_nSpawnCounter = 0;
				m_fSpawnTime = 0;
			}
		}
	}
	else if( m_nStages == 2 )
	{
		if(GetHealth() <= 0)
		{
			for( unsigned int i = 0; i < GamePlayState::GetInstance()->GetEnemies().size(); i++ )
			{
				if( this == GamePlayState::GetInstance()->GetEnemies()[i] )
				{
					vector<Enemy*>::iterator nth = GamePlayState::GetInstance()->GetEnemies().begin() + i;
					GamePlayState::GetInstance()->GetEnemies()[i] = nullptr;
					GamePlayState::GetInstance()->GetEnemies().erase(nth);
					break;
				}
			}
			ObjectManager::GetInstance()->RemoveObject( this );
		}

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
				MoveTo(m_pTarget->GetPosX(), m_pTarget->GetPosY(), 80 );
				BaseCharacter::Update(fElapsedTime);
			}
			else if( distanceY < 50 || distanceX < 50 )
			{
				if(m_pTarget->GetPosX() < GetPosX()+5 )
				{
					MoveTo(GetPosX()+100, GetPosY(), 80);
					/*if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);*/
				}
				else if(m_pTarget->GetPosX() > GetPosX()-5 )
				{
					MoveTo(GetPosX() - 100, GetPosY(), 80);
					/*if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);*/
				}
				//else
				//AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();

				BaseCharacter::Update(fElapsedTime);

				if(m_pTarget->GetPosY() < GetPosY()+5 )
				{
					MoveTo(GetPosX(), GetPosY()+100, 80);
					/*if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);*/
				}
				else if(m_pTarget->GetPosY() > GetPosY()-5 )
				{
					MoveTo(GetPosX(), GetPosY()-100, 80);
					/*if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
					AudioManager::GetInstance()->playSound(walkingID);*/
				}
				/*else
				AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();*/

				BaseCharacter::Update(fElapsedTime);
			}
			//else
			//AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();
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

void Boss1::Render()
{
	// Do Rendering here

	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.0f, 1.0f);

	//RECT reRect = {long(GetPosX() - GamePlayState::GetInstance()->GetCamera().x), long(GetPosY() - GamePlayState::GetInstance()->GetCamera().y), long(reRect.left+GetWidth()), long(reRect.top + GetHeight())};
	//pVM->DrawRect(reRect, 255, 255, 100);
}

bool Boss1::CheckCollision(IObjects* pBase)
{
	if( BaseCharacter::CheckCollision(pBase) == false )
		return false;

	return true;
}

void Boss1::HandleEvent(Event* pEvent)
{
	if(pEvent->GetEventID() == "target_hit")
	{
		if( pEvent->GetParam() == this )
		{
			//m_nStages =  1;
		}
	}
}

