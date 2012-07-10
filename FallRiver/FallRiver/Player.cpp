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
#include "Bush.h"
#include "LoseMenuState.h"
#include "CGame.h"

Player::Player()
{
	m_nCharacterType = CHA_PLAYER;
	m_bIsAlive = true;
	m_bIsHidden = false;
	m_nScore = 0;
	m_nState = PSTATE_IDLE;
	this->SetHealth(100);
	m_nLives = 3;
	m_nFontID = 0;
	m_cName = "";
	questCounter = 0;
	completedQuest = 0;
	SetDirection(DIRE_UP);

	//AnimInfo startup
	m_playerAnim.curAnimation = 0;
	m_playerAnim.curAnimID = 0;
	m_playerAnim.curFrame = 0;
	m_playerAnim.fTime = 0;

	m_dwGunCount = 0;
	m_dwGunReset = 0;
	flickerRate = 9;

	EventSystem::GetInstance()->RegisterClient( "target_hit", this );
	EventSystem::GetInstance()->RegisterClient( "hit_wall", this );
	walkingID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/walking.aiff");
	hitID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/hit.aiff");
	m_nFontID = ViewManager::GetInstance()->RegisterFont("resource/graphics/FallRiver_0.png");
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	AudioManager::GetInstance()->setSoundVel(hitID, sound1);
	AudioManager::GetInstance()->setSoundVel(walkingID, sound1);
	sound1.x = m_nPosX;
	sound1.y = m_nPosY;
	AudioManager::GetInstance()->setSoundPos(walkingID, sound1);
	AudioManager::GetInstance()->setSoundLooping(walkingID, true);
	AudioManager::GetInstance()->setSoundPos(hitID, sound1);
	AudioManager::GetInstance()->setSoundLooping(hitID, false);


	lightOn = false;
	battery = 100;
	batteryTime = 0;
	flashLightType = 0;
	decreaseTime = 0;
}

Player::~Player()
{

}

int Player::GetAmmo()
{
	return this->m_currWeapon->GetAmmo();
}
int Player::GetClip()
{
	return this->m_currWeapon->GetClip();
}
int Player::GetWeaponType()
{
	return this->m_currWeapon->GetWeaponType();
}

void Player::Update(float fElapsedTime) 
{
	DirectInput* pDI = DirectInput::GetInstance();
	FMOD_VECTOR sound1 = { m_nPosX, m_nPosY, 0};
	AudioManager::GetInstance()->setSoundPos(walkingID, sound1);
	AudioManager::GetInstance()->setSoundPos(hitID, sound1);

	if( this->GetHealth() < 0 )
	{
		CGame::GetInstance()->ChangeState(LoseMenuState::GetInstance());
		//m_nLives--;
		//SetHealth(100);
	}
	//if( this->GetLives() < 0 )
	//{
	//	CGame::GetInstance()->ChangeState(LoseMenuState::GetInstance());
	//}

	if( m_dwGunReset < GetTickCount() && m_dwGunReset != 0 )
		m_nState = PSTATE_IDLE;

	if( pDI->KeyDown(DIK_R) || m_currWeapon->m_bReloading )
		m_currWeapon->Reload();

	if(pDI->KeyDown(DIK_SPACE) && 	m_dwGunCount  < GetTickCount() )
	{
		if(m_dwGunCount == 0)
		{
			m_dwGunCount = DWORD(GetTickCount() + m_currWeapon->GetFireRate());
			m_nState = PSTATE_SHOOT;
			m_currWeapon->FireWeapon();
			m_dwGunReset = GetTickCount() + 500;
		}
		else if( m_dwGunCount < GetTickCount() )
		{
			m_nState = PSTATE_SHOOT;
			m_currWeapon->FireWeapon();
			m_dwGunCount = DWORD(GetTickCount() + m_currWeapon->GetFireRate());
			m_dwGunReset = GetTickCount() + 500;
		}

	}	

	// Flashlight
	if( pDI->KeyPressed(DIK_E))
	{
		++flashLightType;
		if(flashLightType > 3)
			flashLightType = 3;
	}
	if( pDI->KeyPressed(DIK_Q))
	{
		--flashLightType;
		if(flashLightType < 0)
			flashLightType = 0;
	}

	if( pDI->KeyPressed(DIK_F))
	{
		lightOn = !lightOn;
	}

	if(lightOn)
	{
		ViewManager::GetInstance()->SetLightPos(0,0,0);
		batteryTime += fElapsedTime;
		if(batteryTime > decreaseTime)
		{
			--battery;
			batteryTime = 0;
		}
		switch(flashLightType)
		{
		case 0:		// Flashlight
			{
				ViewManager::GetInstance()->SetLightPos(0, 0, 0);
				ViewManager::GetInstance()->SetSpotLightPos(0, 0, -.7f);
				ViewManager::GetInstance()->SetInnerCone(.95f);
				ViewManager::GetInstance()->SetOuterCone(.9f);
				ViewManager::GetInstance()->SetColor(.5f, .5f, .5f);
				decreaseTime = 1.2f;
			}
			break;
		case 1:		// Mag Light
			{
				ViewManager::GetInstance()->SetLightPos(0, 0, 0);
				ViewManager::GetInstance()->SetSpotLightPos(0, 0, -.7f);
				ViewManager::GetInstance()->SetInnerCone(.7f);
				ViewManager::GetInstance()->SetOuterCone(.7f);
				ViewManager::GetInstance()->SetColor(.5f, .5f, .5f);
				decreaseTime = .6f;			
			}
			break;
		case 2:		// Lantern
			{
				ViewManager::GetInstance()->SetLightPos(0, 0, -1);
				ViewManager::GetInstance()->SetSpotLightPos(0, 0, -1);
				ViewManager::GetInstance()->SetInnerCone(.95f);
				ViewManager::GetInstance()->SetOuterCone(.9f);
				if(rand() % flickerRate == 0)
					ViewManager::GetInstance()->SetColor(1, 0, 0);
				else
					ViewManager::GetInstance()->SetColor(1, .6f, 0);

				decreaseTime = .8f;			
			}
			break;
		case 3:		// Lighter
			{
				ViewManager::GetInstance()->SetLightPos(0, 0, -1);	
				ViewManager::GetInstance()->SetSpotLightPos(0, 0, -.25f);
				ViewManager::GetInstance()->SetInnerCone(.95f);
				ViewManager::GetInstance()->SetOuterCone(.9f);
				if(rand() % flickerRate == 0)
					ViewManager::GetInstance()->SetColor(1, 0, 0);
				else
					ViewManager::GetInstance()->SetColor(1, .6f, 0);
				decreaseTime = 1.4f;						
			}
			break;
		}
	}
	else
		ViewManager::GetInstance()->SetLightPos(0,0,-1);

	if( pDI->KeyDown(DIK_D))
	{
		if( pDI->KeyDown(DIK_W))
		{
			SetDirection(DIRE_UPRIGHT);
			ViewManager::GetInstance()->SetLightDir(1,1,0);
		}
		else if(pDI->KeyDown(DIK_S))
		{
			SetDirection(DIRE_DOWNRIGHT);
			ViewManager::GetInstance()->SetLightDir(1,-1,0);
		}
		else
		{
			SetDirection(DIRE_RIGHT);	
			ViewManager::GetInstance()->SetLightDir(1,0,0);		
		}
	}
	else if( pDI->KeyDown(DIK_A))
	{
		if( pDI->KeyDown(DIK_W))
		{
			SetDirection(DIRE_UPLEFT);
			ViewManager::GetInstance()->SetLightDir(-1,1,0);
		}
		else if(pDI->KeyDown(DIK_S))
		{
			SetDirection(DIRE_DOWNLEFT);
			ViewManager::GetInstance()->SetLightDir(-1,-1,0);
		}
		else
		{
			SetDirection(DIRE_LEFT);
			ViewManager::GetInstance()->SetLightDir(-1,0,0);
		}
	}
	else if( pDI->KeyDown(DIK_W))
	{
		SetDirection(DIRE_UP);
		ViewManager::GetInstance()->SetLightDir(0,1,0);
	}
	else if( pDI->KeyDown(DIK_S))
	{
		SetDirection(DIRE_DOWN);
		ViewManager::GetInstance()->SetLightDir(0,-1,0);
	}

	if( pDI->KeyDown(DIK_D) )
	{
		SetVelX(100);
		if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
			AudioManager::GetInstance()->playSound(walkingID);
	}
	else if( pDI->KeyDown(DIK_A) )
	{
		SetVelX(-100);
		if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
			AudioManager::GetInstance()->playSound(walkingID);
	}
	else
	{
		SetVelX(0);
	}

	if( pDI->KeyDown(DIK_W) )
	{
		SetVelY(-100);
		if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
			AudioManager::GetInstance()->playSound(walkingID);
	}
	else if( pDI->KeyDown(DIK_S) )
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
	{
		flickerRate = 9;
		AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();
	}
	else
		flickerRate = 5;


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
		
	if(battery <=0)
	{
		battery = 0;
		lightOn = false;
	}





}

void Player::Render()
{
	ViewManager* pVM = ViewManager::GetInstance();

	//Drawing Player Placeholder Sprite
	pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight());
	/*pVM->DrawRect(GetRect(), 255, 255, 255);*/


	//char szName[100] = {};
	//
	//TCHAR buffer[ 100 ];
	////int playerScore = 15;
	//_stprintf_s( buffer, 100, _T("Health - %i"), GetHealth() );

	//wcstombs_s( nullptr, szName, 100, buffer, _TRUNCATE );
	//pVM->GetSprite()->Flush();
	//pVM->DrawTextW("hello",0,0,0,255,255);

	////m_pVM->DrawText(szName,0,0,255,255,255);
	//pVM->DrawFont(m_nFontID,szName,0,50);


	//RECT reRect = {GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y, reRect.left+GetWidth(), reRect.top + GetHeight()};

	
	//RECT logRect = { 600, 0, 800, 200};

	//pVM->DrawRect(logRect, 50, 50, 50);

	//for(unsigned int i = 0; i < m_vpActiveQuests.size(); i++)
//		pVM->DrawFont(m_nFontID, (char*)m_vpActiveQuests[i]->QuestTitle.c_str(), 610, i*50+50, 0.5f, 0.5f);

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
		if( pBase->GetObjectType() != OBJ_BUSH )
		{
			if(BaseObject::CheckCollision(pBase) == true )
			{
				if(pBase->GetObjectType() == OBJ_BULLET)
				{
					//if(pBU->GetOwner()->GetOwner() == this)
					//return false;
					Bullet* pBU = (Bullet*)pBase;
					//EventSystem::GetInstance()->SendUniqueEvent( "target_hit", pBase );
					if(pBU->GetOwner()->GetOwner() == this)
						return false;
					else
						return true;
					//DestroyBullet* pMsg = new DestroyBullet(pBU);
					//MessageSystem::GetInstance()->SendMsg(pMsg);
					//pMsg = nullptr;
				}

				if(pBase->GetRect().left <= GetRect().right && GetRect().right - pBase->GetRect().left <= 5)
					SetPosX(float(pBase->GetRect().left-GetWidth()));
				else if(pBase->GetRect().right >= GetRect().left && pBase->GetRect().right - GetRect().left <= 5)
					SetPosX(float(pBase->GetRect().right));
				else if(pBase->GetRect().top <= GetRect().bottom && GetRect().bottom - pBase->GetRect().top <= 5)
					SetPosY(float(pBase->GetRect().top-GetHeight()));
				else if(pBase->GetRect().bottom >= GetRect().top && pBase->GetRect().bottom - GetRect().top <= 5)
					SetPosY(float(pBase->GetRect().bottom));
			}

		}
		else
		{
			if(BaseObject::CheckCollision(pBase) == true )
			{
				RECT cRect;
				if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == TRUE )
				{
					Bush* tmp = (Bush*)pBase;
					tmp->SetIsInBush( true );
					m_bIsHidden = true;
				}
			}
			else
			{
				Bush* tmp = (Bush*)pBase;
				tmp->SetIsInBush( false );
				m_bIsHidden = false;

			}
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


