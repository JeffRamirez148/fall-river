#include "Player.h"
#include "Quests.h"
#include "GamePlayState.h"
#include "Enemy.h"
#include "Bullet.h"
#include "ViewManager.h"
#include "EventSystem.h"
#include "DestroyBullet.h"
#include "CompanionAI.h"
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
	m_ncurrWeap = 0;
	m_nState = PSTATE_IDLE;
	SetHealth(200);
	m_nLives = 3;
	m_nFontID = 0;
	m_cName = "";
	questCounter = 0;
	completedQuest = 0;
	questLogToggle = false;
	SetDirection(DIRE_UP);

	//AnimInfo startup
	m_playerAnim.curAnimation = 0;
	m_playerAnim.curAnimID = 0;
	m_playerAnim.curFrame = 0;
	m_playerAnim.fTime = 0;

	m_dwGunCount = 0;
	m_dwGunReset = 0;
	m_dwDeathTime = 0;
	flickerRate = 9;


	EventSystem::GetInstance()->RegisterClient( "target_hit", this );
	EventSystem::GetInstance()->RegisterClient( "hit_wall", this );
	walkingID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/walking.wav");
	hitID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/hit.aiff");

	flashLightID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/KCJ_MenuClick.wav");
	weaponChangeID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/reload.wav");
	sheathID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/sheath.wav");

	m_nFontID = ViewManager::GetInstance()->RegisterFont("resource/graphics/FallRiver_0.png");
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	AudioManager::GetInstance()->setSoundVel(hitID, sound1);
	AudioManager::GetInstance()->setSoundVel(walkingID, sound1);
	AudioManager::GetInstance()->setSoundVel(flashLightID, sound1);
	AudioManager::GetInstance()->setSoundVel(weaponChangeID, sound1);
	AudioManager::GetInstance()->setSoundVel(sheathID, sound1);
	sound1.x = m_nPosX;
	sound1.y = m_nPosY;
	AudioManager::GetInstance()->setSoundPos(walkingID, sound1);
	AudioManager::GetInstance()->setSoundLooping(walkingID, true);
	AudioManager::GetInstance()->setSoundPos(hitID, sound1);
	AudioManager::GetInstance()->setSoundLooping(hitID, false);
	AudioManager::GetInstance()->setSoundPos(flashLightID, sound1);
	AudioManager::GetInstance()->setSoundLooping(flashLightID, false);
	AudioManager::GetInstance()->setSoundPos(weaponChangeID, sound1);
	AudioManager::GetInstance()->setSoundLooping(weaponChangeID, false);
	AudioManager::GetInstance()->setSoundPos(sheathID, sound1);
	AudioManager::GetInstance()->setSoundLooping(sheathID, false);

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
	return m_currWeapon->GetAmmo();
}
int Player::GetClip()
{
	return m_currWeapon->GetClip();
}
int Player::GetWeaponType()
{
	return m_currWeapon->GetWeaponType();
}

void Player::Update(float fElapsedTime) 
{
	DirectInput* pDI = DirectInput::GetInstance();
	FMOD_VECTOR sound1 = { m_nPosX, m_nPosY, 0};
	AudioManager::GetInstance()->setSoundPos(walkingID, sound1);
	AudioManager::GetInstance()->setSoundPos(hitID, sound1);
	AudioManager::GetInstance()->setSoundPos(flashLightID, sound1);
	AudioManager::GetInstance()->setSoundPos(weaponChangeID, sound1);
	AudioManager::GetInstance()->setSoundPos(sheathID, sound1);

	CompanionAI* pBud = GamePlayState::GetInstance()->GetCompanion();

	if( GetHealth() <= 0 )
	{
		SetHealth(0);
		if( m_dwDeathTime == 0 )
		{
			m_dwDeathTime = GetTickCount() + 5000;
			m_nState = PSTATE_DEAD;
			SetVelX(0);
			SetVelY(0);
		}
	}

	if( m_dwDeathTime <= GetTickCount() && m_nState == PSTATE_DEAD )
	{
		CGame::GetInstance()->ChangeState(LoseMenuState::GetInstance());
		//m_nLives--;
		//SetHealth(100);
	}


	if( pDI->KeyPressed( DIK_TAB ) || pDI->JoystickButtonPressed(3,0) )
	{
		if( pBud && pBud->IsTeaching() && pBud->GetStage() != 3 )
		{}
		else
		{
		if( m_currWeapon == m_vpWeapons.back() )
		{
			m_currWeapon = m_vpWeapons.front();
			m_ncurrWeap = 0;
		}
		else
		{
			m_ncurrWeap++;
			m_currWeapon = m_vpWeapons[m_ncurrWeap];
		}
		if(m_ncurrWeap == WPN_MACHETE )
		{
			AudioManager::GetInstance()->GetSoundChannel(sheathID)->stop();
			AudioManager::GetInstance()->playSound(sheathID);	
		}
		else
		{
			AudioManager::GetInstance()->GetSoundChannel(weaponChangeID)->stop();
			AudioManager::GetInstance()->playSound(weaponChangeID);	
		}
		if( pBud && pBud->IsTeaching() && pBud->GetStage() == 3 )
			pBud->NextStep();
		}
	}

	if( m_dwGunReset < GetTickCount() && m_dwGunReset != 0 && m_nState != PSTATE_DEAD )
		m_nState = PSTATE_IDLE;

	if( pDI->KeyDown(DIK_R) || m_currWeapon->m_bReloading || pDI->JoystickButtonPressed(2,0) )
		m_currWeapon->Reload();

	if( ((pDI->KeyDown(DIK_SPACE) && m_dwGunCount  < GetTickCount()) || (pDI->JoystickGetRTriggerAmount(0) > 1 && m_dwGunCount  < GetTickCount()) ) && m_nState != PSTATE_DEAD )
	{
		if( pBud && pBud->IsTeaching() &&  pBud->GetStage() != 2 )
		{}
		else
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
			if( pBud && pBud->IsTeaching() )
				pBud->NextStep();
		}
	}	

	if( m_nState != PSTATE_DEAD )
	{
		// Flashlight
		if( pDI->KeyPressed(DIK_E) || pDI->JoystickButtonPressed(4,0)) //pDI->JoystickDPadPressed(DIR_LEFT,0) 8 
		{
			if( pBud && (pBud->IsTeaching() && pBud->GetStage() != 1) || !IsOn() )
			{}
			else
			{
				AudioManager::GetInstance()->playSound(flashLightID);		
				++flashLightType;
				if(flashLightType > 3)
					flashLightType = 0;
				if( pBud && pBud->GetStage() == 1 && pBud->IsTeaching() &&  pBud->GetStep() < 4 )
					pBud->NextStep();
			}
		}

		if( pDI->KeyPressed(DIK_Q) || pDI->JoystickButtonPressed(5,0)) //pDI->JoystickDPadPressed(DIR_RIGHT,0) 9
		{
			if( pBud && (pBud->IsTeaching() && pBud->GetStage() != 1 ) || !IsOn() || pBud->GetStep() < 4)
			{}
			else
			{
				AudioManager::GetInstance()->playSound(flashLightID);		
				--flashLightType;
				if(flashLightType < 0)
					flashLightType = 3;
				if( pBud && pBud->GetStage() == 1 && pBud->IsTeaching() && pBud->GetStep() == 4 )
					pBud->NextStep();
			}
		}

		if( pDI->KeyPressed(DIK_F) || pDI->JoystickButtonPressed(1,0))
		{
			if( pBud && pBud->IsTeaching() && pBud->GetStage() == 0 )
				pBud->NextStep();
			AudioManager::GetInstance()->playSound(flashLightID);		
			lightOn = !lightOn;
		}
		if(pDI->KeyPressed(DIK_L) ||  pDI->JoystickButtonPressed(6,0))
		{
			if( pBud &&  pBud->IsTeaching() && pBud->GetStage() != 4 )
			{}
			else
			{
			if(questLogToggle == true)
				questLogToggle = false;
			else
				questLogToggle = true;
			if( pBud && pBud->IsTeaching() && pBud->GetStage() == 4 )
				pBud->NextStep();
			}
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
					ViewManager::GetInstance()->SetSpotLightPos(0, 0, -.5f);
					ViewManager::GetInstance()->SetInnerCone(.95f);
					ViewManager::GetInstance()->SetOuterCone(.9f);
					ViewManager::GetInstance()->SetColor(.5f, .5f, .5f);
					decreaseTime = 1.2f;
				}
				break;
			case 1:		// Mag Light
				{
					ViewManager::GetInstance()->SetLightPos(0, 0, 0);
					ViewManager::GetInstance()->SetSpotLightPos(0, 0, -.5f);
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
		{
			ViewManager::GetInstance()->SetLightPos(0, 0, -1);
			ViewManager::GetInstance()->SetSpotLightPos(0, 0, -.5f);
			ViewManager::GetInstance()->SetInnerCone(.95f);
			ViewManager::GetInstance()->SetOuterCone(.9f);
			ViewManager::GetInstance()->SetColor(.5f, .5f, .5f);
		}


		if( pDI->KeyDown(DIK_D) || (pDI->JoystickGetLStickDirDown(DIR_RIGHT,0) && pDI->JoystickGetLStickXAmount(0) > 100))
		{
			if( pDI->KeyDown(DIK_W) || (pDI->JoystickGetLStickDirDown(DIR_UP,0) && pDI->JoystickGetLStickYAmount(0) < -400))
			{
				SetDirection(DIRE_UPRIGHT);
				ViewManager::GetInstance()->SetLightDir(1,1,0);
			}
			else if(pDI->KeyDown(DIK_S) || (pDI->JoystickGetLStickDirDown(DIR_DOWN,0) && pDI->JoystickGetLStickYAmount(0) > 10))
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
		else if( pDI->KeyDown(DIK_A) || (pDI->JoystickGetLStickDirDown(DIR_LEFT,0) && pDI->JoystickGetLStickXAmount(0) < -800))
		{
			int temp = pDI->JoystickGetLStickXAmount(0);
			if( pDI->KeyDown(DIK_W) || (pDI->JoystickGetLStickDirDown(DIR_UP,0) && pDI->JoystickGetLStickYAmount(0) < -400))
			{
				SetDirection(DIRE_UPLEFT);
				ViewManager::GetInstance()->SetLightDir(-1,1,0);
			}
			else if(pDI->KeyDown(DIK_S) || (pDI->JoystickGetLStickDirDown(DIR_DOWN,0) && pDI->JoystickGetLStickYAmount(0) > 10))
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
		else if( pDI->KeyDown(DIK_W) || (pDI->JoystickGetLStickDirDown(DIR_UP,0) && pDI->JoystickGetLStickYAmount(0) < -400))
		{
			SetDirection(DIRE_UP);
			ViewManager::GetInstance()->SetLightDir(0,1,0);
		}
		else if(pDI->KeyDown(DIK_S) || (pDI->JoystickGetLStickDirDown(DIR_DOWN,0) && pDI->JoystickGetLStickYAmount(0) > 10))
		{
			SetDirection(DIRE_DOWN);
			ViewManager::GetInstance()->SetLightDir(0,-1,0);
		}


		if( pDI->KeyDown(DIK_D) || (pDI->JoystickGetLStickDirDown(DIR_RIGHT,0) && pDI->JoystickGetLStickXAmount(0) > 100))
		{
			SetVelX(100);
			if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
				AudioManager::GetInstance()->playSound(walkingID);
		}
		else if( pDI->KeyDown(DIK_A) || (pDI->JoystickGetLStickDirDown(DIR_LEFT,0) && pDI->JoystickGetLStickXAmount(0) < -800))
		{
			int temptemp = pDI->JoystickGetLStickXAmount(0);
			SetVelX(-100);
			if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
				AudioManager::GetInstance()->playSound(walkingID);
		}
		else
		{
			SetVelX(0);
		}

		if(pDI->KeyDown(DIK_W) || (pDI->JoystickGetLStickDirDown(DIR_UP,0) && pDI->JoystickGetLStickYAmount(0) < -400))
		{
			SetVelY(-100);
			if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
				AudioManager::GetInstance()->playSound(walkingID);
		}
		else if( pDI->KeyDown(DIK_S) || (pDI->JoystickGetLStickDirDown(DIR_DOWN,0) && pDI->JoystickGetLStickYAmount(0) > 10))
		{
			SetVelY(100);
			if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
				AudioManager::GetInstance()->playSound(walkingID);
		}
		else
		{
			SetVelY(0);
		}
	}

	if(GetVelX() == 0 && GetVelY() == 0)
	{
		flickerRate = 9;
		AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();
	}
	else
		flickerRate = 5;


	if(GetVelX() == 0 && GetVelY() == 0)
	{
		flickerRate = 9;
		AudioManager::GetInstance()->GetSoundChannel(walkingID)->stop();
	}
	else
		flickerRate = 5;


	BaseCharacter::Update(fElapsedTime);

	if( m_nState == PSTATE_DEAD )
	{
		if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && m_playerAnim.curAnimation != 20 )
		{
			m_playerAnim.curAnimation = 20;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && m_playerAnim.curAnimation != 22 )
		{
			m_playerAnim.curAnimation = 22;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 21 )
		{
			m_playerAnim.curAnimation = 21;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 23 )
		{
			m_playerAnim.curAnimation = 23;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
	}

	if(m_nState == PSTATE_IDLE || m_nState == PSTATE_SHOOT)
	{
		if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && GetVelY() < 0)
		{
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE && m_playerAnim.curAnimation != 0)
			{
				m_playerAnim.curAnimation = 0;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_PISTOL && m_playerAnim.curAnimation != 4)
			{
				m_playerAnim.curAnimation = 4;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_SHOTGUN && m_playerAnim.curAnimation != 8)
			{
				m_playerAnim.curAnimation = 8;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_RIFLE && m_playerAnim.curAnimation != 12)
			{
				m_playerAnim.curAnimation = 12;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
		}
		else if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && GetVelY() == 0)
		{
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE )
			{
				m_playerAnim.curAnimation = 0;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_PISTOL )
			{
				m_playerAnim.curAnimation = 4;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_SHOTGUN )
			{
				m_playerAnim.curAnimation = 8;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_RIFLE )
			{
				m_playerAnim.curAnimation = 12;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && GetVelY() > 0)
		{
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE && m_playerAnim.curAnimation != 2)
			{
				m_playerAnim.curAnimation = 2;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_PISTOL && m_playerAnim.curAnimation != 6)
			{
				m_playerAnim.curAnimation = 6;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_SHOTGUN && m_playerAnim.curAnimation != 10)
			{
				m_playerAnim.curAnimation = 10;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_RIFLE && m_playerAnim.curAnimation != 14)
			{
				m_playerAnim.curAnimation = 14;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && GetVelY() == 0)
		{
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE )
			{
				m_playerAnim.curAnimation = 2;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_PISTOL )
			{
				m_playerAnim.curAnimation = 6;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_SHOTGUN )
			{
				m_playerAnim.curAnimation = 10;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_RIFLE )
			{
				m_playerAnim.curAnimation = 14;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
		}
		else if(GetDirection() == DIRE_RIGHT && GetVelX() > 0)
		{
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE && m_playerAnim.curAnimation != 3)
			{
				m_playerAnim.curAnimation = 3;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_PISTOL && m_playerAnim.curAnimation != 7)
			{
				m_playerAnim.curAnimation = 7;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_SHOTGUN && m_playerAnim.curAnimation != 11)
			{
				m_playerAnim.curAnimation = 11;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_RIFLE && m_playerAnim.curAnimation != 15)
			{
				m_playerAnim.curAnimation = 15;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
		}
		else if(GetDirection() == DIRE_RIGHT && GetVelX() == 0)
		{
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE )
			{
				m_playerAnim.curAnimation = 3;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_PISTOL )
			{
				m_playerAnim.curAnimation = 7;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_SHOTGUN )
			{
				m_playerAnim.curAnimation = 11;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_RIFLE )
			{
				m_playerAnim.curAnimation = 15;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
		}
		else if(GetDirection() == DIRE_LEFT && GetVelX() < 0)
		{
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE && m_playerAnim.curAnimation != 1)
			{
				m_playerAnim.curAnimation = 1;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_PISTOL && m_playerAnim.curAnimation != 5)
			{
				m_playerAnim.curAnimation = 5;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_SHOTGUN && m_playerAnim.curAnimation != 9)
			{
				m_playerAnim.curAnimation = 9;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_RIFLE && m_playerAnim.curAnimation != 13)
			{
				m_playerAnim.curAnimation = 13;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
		}
		else if(GetDirection() == DIRE_LEFT && GetVelX() == 0)
		{
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE )
			{
				m_playerAnim.curAnimation = 1;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_PISTOL )
			{
				m_playerAnim.curAnimation = 5;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_SHOTGUN )
			{
				m_playerAnim.curAnimation = 9;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if(m_currWeapon->GetWeaponType() == WPN_RIFLE )
			{
				m_playerAnim.curAnimation = 13;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
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
			m_playerAnim.curFrame--;
	}

	if(battery <= 0)
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
	//Animation thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	//Frame thisFrame = thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame];
	//int x =pBase->GetObjectType();
	if( pBase->GetObjectType() != OBJ_LEVEL)
	{
		if( pBase->GetObjectType() != OBJ_BUSH )
		{
			//int x =pBase->GetObjectType();
			if(BaseCharacter::CheckCollision(pBase) == true )
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
				if(pBase->GetObjectType() == OBJ_CHARACTER)
					
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
	m_ncurrWeap = m_vpWeapons.size()-1;
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
			AudioManager::GetInstance()->GetSoundChannel(hitID)->stop();
			AudioManager::GetInstance()->playSound(hitID);
		}
	}
	else if(pEvent->GetEventID() == "hit_wall")
	{

	}
}


