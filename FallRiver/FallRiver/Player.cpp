#include "Player.h"
#include "Quests.h"
#include "GamePlayState.h"
#include "Enemy.h"
#include "Bullet.h"
#include "ViewManager.h"
#include "EventSystem.h"
#include "DestroyBullet.h"
#include "DirectInput.h"
#include "Weapon.h"
#include "Light.h"
#include "EventSystem.h"
#include "Level.h"
#include "AudioManager.h"
#include "Sound.h"
#include "ViewManager.h"

Player::Player()
{
	m_nCharacterType = CHA_PLAYER;
	m_bIsAlive = true;
	m_bIsHidden = false;
	m_nScore = 0;
	m_nState = PSTATE_IDLE;
	m_nLives = 3;
	m_cName = "";
	SetDirection(DIRE_UP);

	//AnimInfo startup
	m_playerAnim.curAnimation = 0;
	m_playerAnim.curAnimID = 0;
	m_playerAnim.curFrame = 0;
	m_playerAnim.fTime = 0;

	m_dwGunCount = 0;
	m_dwGunReset = 0;

	EventSystem::GetInstance()->RegisterClient( "target_hit", this );
	EventSystem::GetInstance()->RegisterClient( "hit_wall", this );
	walkingID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/walking.aiff");
	hitID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/hit.aiff");
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	AudioManager::GetInstance()->setSoundVel(hitID, sound1);
	AudioManager::GetInstance()->setSoundVel(walkingID, sound1);
	sound1.x = m_nPosX;
	sound1.y = m_nPosY;
	AudioManager::GetInstance()->setSoundPos(walkingID, sound1);
	AudioManager::GetInstance()->setSoundLooping(walkingID, true);
	AudioManager::GetInstance()->setSoundPos(hitID, sound1);
	AudioManager::GetInstance()->setSoundLooping(hitID, false);

	Light tmpLight;
	tmpLight.lightPos[0] = 0.0f;
	tmpLight.lightPos[1] = 0.0f;
	tmpLight.lightPos[2] = -1.0f;
	tmpLight.lightDir[0] = 0.0f;
	tmpLight.lightDir[1] = 0.0f;
	tmpLight.lightDir[2] = 1.0f;
	ViewManager::GetInstance()->RegisterLight(tmpLight);
}

Player::~Player()
{

}

void Player::Update(float fElapsedTime) 
{
	DirectInput* pDI = DirectInput::GetInstance();
	FMOD_VECTOR sound1 = { m_nPosX, m_nPosY, 0};
	AudioManager::GetInstance()->setSoundPos(walkingID, sound1);
	AudioManager::GetInstance()->setSoundPos(hitID, sound1);

	if( m_dwGunReset < GetTickCount() && m_dwGunReset != 0 )
		m_nState = PSTATE_IDLE;

	if(pDI->KeyDown(DIK_SPACE) && 	m_dwGunCount  < GetTickCount() )
	{
		if(m_dwGunCount == 0)
		{
			m_dwGunCount = GetTickCount() + m_currWeapon->GetFireRate();
			m_nState = PSTATE_SHOOT;
			m_currWeapon->FireWeapon();
			m_dwGunReset = GetTickCount() + 500;
		}
		else if( m_dwGunCount < GetTickCount() )
		{
			m_nState = PSTATE_SHOOT;
			m_currWeapon->FireWeapon();
			m_dwGunCount = GetTickCount() + m_currWeapon->GetFireRate();
			m_dwGunReset = GetTickCount() + 500;
		}
	}	

	if( pDI->KeyDown(DIK_RIGHT))
	{
		if( pDI->KeyDown(DIK_UP))
			SetDirection(DIRE_UPRIGHT);
		else if(pDI->KeyDown(DIK_DOWN))
			SetDirection(DIRE_DOWNRIGHT);
		else
			SetDirection(DIRE_RIGHT);		
	}
	else if( pDI->KeyDown(DIK_LEFT))
	{
		if( pDI->KeyDown(DIK_UP))
			SetDirection(DIRE_UPLEFT);
		else if(pDI->KeyDown(DIK_DOWN))
			SetDirection(DIRE_DOWNLEFT);
		else
			SetDirection(DIRE_LEFT);
	}
	else if( pDI->KeyDown(DIK_UP))
	{
		SetDirection(DIRE_UP);
	}
	else if( pDI->KeyDown(DIK_DOWN))
	{
		SetDirection(DIRE_DOWN);
	}

	if( pDI->KeyDown(DIK_RIGHT) )
	{
		SetVelX(100);
		if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
			AudioManager::GetInstance()->playSound(walkingID);
	}
	else if( pDI->KeyDown(DIK_LEFT) )
	{
		SetVelX(-100);
		if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
			AudioManager::GetInstance()->playSound(walkingID);
	}
	else
	{
		SetVelX(0);
	}

	if( pDI->KeyDown(DIK_UP) )
	{
		SetVelY(-100);
		if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
			AudioManager::GetInstance()->playSound(walkingID);
	}
	else if( pDI->KeyDown(DIK_DOWN) )
	{
		SetVelY(100);
		if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
			AudioManager::GetInstance()->playSound(walkingID);
	}
	else
	{
		SetVelY(0);
	}
	if(GetVelX() == 0 && GetVelY() == 0)
		AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();

	BaseCharacter::Update(fElapsedTime);

	if(m_nState == PSTATE_IDLE)
	{
		if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && m_playerAnim.curAnimation != 0 && GetVelY() < 0)
		{
			m_playerAnim.curAnimation = 0;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && m_playerAnim.curAnimation != 4 && GetVelY() == 0)
		{
			m_playerAnim.curAnimation = 4;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && m_playerAnim.curAnimation != 1 && GetVelY() > 0)
		{
			m_playerAnim.curAnimation = 1;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && m_playerAnim.curAnimation != 5 && GetVelY() == 0)
		{
			m_playerAnim.curAnimation = 5;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 2 && GetVelX() > 0)
		{
			m_playerAnim.curAnimation = 2;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 7 && GetVelX() == 0)
		{
			m_playerAnim.curAnimation = 7;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 3 && GetVelX() < 0)
		{
			m_playerAnim.curAnimation = 3;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 6 && GetVelX() == 0)
		{
			m_playerAnim.curAnimation = 6;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		
	}
	else if(m_nState == PSTATE_SHOOT)
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
		else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 10)
		{
			m_playerAnim.curAnimation = 10;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 11)
		{
			m_playerAnim.curAnimation = 11;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}

	}


	for(unsigned int i = 0; i < m_vpWeapons.size(); i++)
		m_vpWeapons[i]->Update(fElapsedTime);

	//Updating the player's frame and timer for animations
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

void Player::Render()
{
	ViewManager* pVM = ViewManager::GetInstance();

	//Drawing Player Placeholder Sprite
	pVM->DrawAnimation(&m_playerAnim, int( (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2 ) , int( (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight() ));
	/*pVM->DrawRect(GetRect(), 255, 255, 255);*/

	//RECT reRect = {GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y, reRect.left+GetWidth(), reRect.top + GetHeight()};

	//pVM->DrawRect(reRect, 0, 0, 0);

	/*for(unsigned int i = 0; i < m_vpWeapons.size(); i++)
		m_vpWeapons[i]->Render();*/
}

bool Player::CheckCollision(IObjects* pBase) 
{
	Animation thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	Frame thisFrame = thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame];

	if( pBase->GetObjectType() != OBJ_LEVEL)
	{
		if(BaseObject::CheckCollision(pBase) == true )
		{
			if(pBase->GetObjectType() == OBJ_BULLET)
			{
				Bullet* pBU = (Bullet*)pBase;
				if(pBU->GetOwner()->GetOwner() == this)
					return false;
				DestroyBullet* pMsg = new DestroyBullet(pBU);
				MessageSystem::GetInstance()->SendMsg(pMsg);
				pMsg = nullptr;
			}

			if(pBase->GetRect().left <= GetRect().right && GetRect().right - pBase->GetRect().left <= 5)
				SetPosX(float(pBase->GetRect().left-GetWidth()-2));
			else if(pBase->GetRect().right >= GetRect().left && pBase->GetRect().right - GetRect().left <= 5)
				SetPosX(float(pBase->GetRect().right+2));
			else if(pBase->GetRect().top <= GetRect().bottom && GetRect().bottom - pBase->GetRect().top <= 5)
				SetPosY(float(pBase->GetRect().top-GetHeight()-2));
			else if(pBase->GetRect().bottom >= GetRect().top && pBase->GetRect().bottom - GetRect().top <= 5)
				SetPosY(float(pBase->GetRect().bottom));


		}
	}
	else
	{
		if( pBase->CheckCollision(this) == true )
		{
			return true;
		}

	}
	return false;

}

// Check if the player is still alive
bool Player::CheckLifes() {return m_bIsAlive;}

void Player::AddQuest(Quest_Struct* pQuest)
{
	// Just in case
	if(pQuest == nullptr)
		return;

	// Add the quest
	m_vpActiveQuests.push_back(pQuest);
}

void Player::AddWeapon(Weapon* pWeapon)
{
	// Just in case
	if(pWeapon == nullptr)
		return;

	// Add the weapon and make it current
	pWeapon->SetHeight(20);
	pWeapon->SetWidth(10);
	pWeapon->SetPosX(GetPosX()+(GetWidth()/2));
	pWeapon->SetPosY(GetPosY());
	m_vpWeapons.push_back(pWeapon);
	m_currWeapon = pWeapon;
}

void Player::AddLight(Light* pLight) 
{
	// Just in case
	if(pLight == nullptr)
		return;

	// Add the weapon and make it current
	m_vpLights.push_back(pLight);
	m_currLight = pLight;
}

void Player::HandleEvent(Event* pEvent)
{
	if(pEvent->GetEventID() == "target_hit")
	{
		if( pEvent->GetParam() == this )
		{
			SetHealth(GetHealth()-30);
			AudioManager::GetInstance()->playSound(hitID);
		}
	}
	else if(pEvent->GetEventID() == "hit_wall")
	{
		
	}
}


