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
#include "Emitter.h"
#include "EventSystem.h"
#include "Level.h"
#include "AudioManager.h"
#include "Particle_Manager.h"
#include "Sound.h"
#include "ViewManager.h"
#include "Bush.h"
#include "LoseMenuState.h"
#include "CGame.h"
#include "Boss2.h"

Player::Player()
{
	m_nCharacterType = CHA_PLAYER;
	m_bIsAlive = true;
	m_bIsHidden = false;
	m_bShotBush = false;
	m_bLocked = false;
	m_bmove = true;
	m_fshotTimer = 0;
	m_nScore = 0;
	m_ncurrWeap = 0;
	m_nlightglare = -1;
	m_nState = PSTATE_IDLE;
	SetHealth(500);
	m_nLives = 3;
	m_nFontID = 0;
	m_cName = "";
	questCounter = 0;
	completedQuest = 0;
	m_bHasMedicine = false;
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
	m_fTimePlayed = 0.0f;

	EventSystem::GetInstance()->RegisterClient( "target_hit", this );
	EventSystem::GetInstance()->RegisterClient( "hit_wall", this );
	walkingID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/walking.wav");
	hitID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/hit.aiff");

	flashLightID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/KCJ_MenuClick.wav");
	weaponChangeID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/reload.wav");
	sheathID = AudioManager::GetInstance()->RegisterSound("resource/Sounds/sheath.wav");

	m_nFontID = ViewManager::GetInstance()->RegisterFont("resource/graphics/FallRiver_0.png");
	m_nlightglare = ViewManager::GetInstance()->RegisterTexture("resource/graphics/stryker_sprites_01.png");

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
	lose = false;
	decreaseTime = 0;
	dammageTimer = 0;
	pushTimer = 0;
	m_dwReloadTime = 0;
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

	m_fshotTimer += fElapsedTime;
	dammageTimer += fElapsedTime;
	if(GetPushX() != 0 || GetPushY() != 0)
	{
		pushTimer += fElapsedTime;
		if(pushTimer > .1f)
		{
			SetPushX(0);
			SetPushY(0);
			pushTimer = 0;
		}
	}

	if( GetHealth() <= 0 )
	{
		SetHealth(0);
		SetGore(true);
		lose = true;
		CGame::GetInstance()->PlayLoseSound();
		if( m_dwDeathTime == 0 )
		{
			m_dwDeathTime = GetTickCount() + 5000;
			m_nState = PSTATE_DEAD;
			SetVelX(0);
			SetVelY(0);
			SetScore(GetScore() - 100);
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
	}

	if( m_dwGunReset < GetTickCount() && m_dwGunReset != 0 && m_nState != PSTATE_DEAD && m_nState != PSTATE_RELOAD )
		m_nState = PSTATE_IDLE;

	if( pDI->KeyPressed(DIK_R)  || pDI->JoystickButtonPressed(2,0) )
	{
		m_dwReloadTime = GetTickCount() + 1000;
		m_nState = PSTATE_RELOAD;
	}

	if( m_nState == PSTATE_RELOAD  )
	{
		if( m_currWeapon->GetClip() < m_currWeapon->GetMaxClip() )
			m_currWeapon->Reload();
		else if( m_dwReloadTime <= GetTickCount() )
		{
			m_dwReloadTime = 0;
			m_nState = PSTATE_IDLE;
		}
	}

	/*if( pDI->KeyDown(DIK_I) )
		if(ViewManager::GetInstance()->GetAmbientLightR() != 1.0f)
			ViewManager::GetInstance()->SetAmbientLight(1.0f, 1.0f, 1.0f);
		else
			ViewManager::GetInstance()->SetAmbientLight(0.0f, 0.0f, 0.0f);*/

	if( !m_bLocked && ((pDI->KeyDown(DIK_SPACE) && m_dwGunCount  < GetTickCount()) || (pDI->JoystickGetRTriggerAmount(0) > 1 && m_dwGunCount  < GetTickCount()) ) && m_nState != PSTATE_DEAD )
	{
		if(m_dwGunCount == 0 && m_nState != PSTATE_RELOAD)
		{
			m_dwGunCount = DWORD(GetTickCount() + m_currWeapon->GetFireRate());
			if( m_currWeapon->GetWeaponType() != WPN_MACHETE )
				m_nState = PSTATE_SHOOT;
			else
				m_nState = PSTATE_SWING;
			m_currWeapon->FireWeapon();
			m_dwGunReset = GetTickCount() + 500;
		}
		else if( m_dwGunCount < GetTickCount() && m_nState != PSTATE_RELOAD )
		{
			if( m_currWeapon->GetWeaponType() != WPN_MACHETE )
				m_nState = PSTATE_SHOOT;
			else
				m_nState = PSTATE_SWING;
			m_currWeapon->FireWeapon();
			m_dwGunCount = DWORD(GetTickCount() + m_currWeapon->GetFireRate());
			m_dwGunReset = GetTickCount() + 500;
		}

		if( m_bIsHidden == true )
		{
			m_bShotBush = true;
			m_bIsHidden = false;
			m_fshotTimer = 0;
		}
	}	

	if( m_bShotBush == true && m_fshotTimer < 5 )
	{
		m_bIsHidden = false;
	}
	else if( m_bShotBush == true && m_fshotTimer > 5 )
	{
		m_bIsHidden = true;
		m_bShotBush = false;
		m_fshotTimer = 0;
	}

	if( m_nState != PSTATE_DEAD )
	{
		// Flashlight
		if( pDI->KeyPressed(DIK_E) || pDI->JoystickButtonPressed(4,0)) //pDI->JoystickDPadPressed(DIR_LEFT,0) 8 
		{
			AudioManager::GetInstance()->playSound(flashLightID);		
			++flashLightType;
			if(flashLightType > 3)
				flashLightType = 0;
		}

		if( pDI->KeyPressed(DIK_Q) || pDI->JoystickButtonPressed(5,0)) //pDI->JoystickDPadPressed(DIR_RIGHT,0) 9
		{
			AudioManager::GetInstance()->playSound(flashLightID);		
			--flashLightType;
			if(flashLightType < 0)
				flashLightType = 3;
		}

		if( pDI->KeyPressed(DIK_F) || pDI->JoystickButtonPressed(1,0))
		{
			AudioManager::GetInstance()->playSound(flashLightID);		
			lightOn = !lightOn;
		}
		if(pDI->KeyPressed(DIK_L) ||  pDI->JoystickButtonPressed(6,0))
		{
			if(questLogToggle == true)
				questLogToggle = false;
			else
				questLogToggle = true;
		}

		if(battery <= 0)
		{
			battery = 0;
			lightOn = false;
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

					if( GetDirection() == DIRE_RIGHT )
						ViewManager::GetInstance()->SetLightPos(0.05f,-0.03f,0);
					else if( GetDirection() == DIRE_LEFT)
						ViewManager::GetInstance()->SetLightPos(0.03f,-0.03f,0);
					else if( GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT)
						ViewManager::GetInstance()->SetLightPos(0.02f,-0.03f,0);
					else if( GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT)
						ViewManager::GetInstance()->SetLightPos(0.06f,0,0);

					ViewManager::GetInstance()->SetSpotLightPos(0, 0, -.3f);
					ViewManager::GetInstance()->SetInnerCone(.95f);
					ViewManager::GetInstance()->SetOuterCone(.9f);
					ViewManager::GetInstance()->SetColor(.3f, .3f, .3f);
					decreaseTime = 1.2f;
				}
				break;
			case 1:		// Mag Light
				{
					ViewManager::GetInstance()->SetLightPos(0, 0, 0);

					if( GetDirection() == DIRE_RIGHT )
						ViewManager::GetInstance()->SetLightPos(0.05f,-0.03f,0);
					else if( GetDirection() == DIRE_LEFT)
						ViewManager::GetInstance()->SetLightPos(0.03f,-0.03f,0);
					else if( GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT)
						ViewManager::GetInstance()->SetLightPos(0.02f,-0.03f,0);
					else if( GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT)
						ViewManager::GetInstance()->SetLightPos(0.06f,0,0);

					ViewManager::GetInstance()->SetSpotLightPos(0, 0, -.3f);
					ViewManager::GetInstance()->SetInnerCone(.75f);
					ViewManager::GetInstance()->SetOuterCone(.7f);
					ViewManager::GetInstance()->SetColor(.3f, .3f, .3f);
					decreaseTime = .6f;			
				}
				break;
			case 2:		// Lantern
				{
					ViewManager::GetInstance()->SetLightPos(0, 0, -1);
					ViewManager::GetInstance()->SetSpotLightPos(0, 0, -.75);
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
			ViewManager::GetInstance()->SetSpotLightPos(0, 0, -.3f);
			ViewManager::GetInstance()->SetInnerCone(.95f);
			ViewManager::GetInstance()->SetOuterCone(.9f);
			ViewManager::GetInstance()->SetColor(.3f, .3f, .3f);
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


		if( m_bmove && pDI->KeyDown(DIK_D) || (pDI->JoystickGetLStickDirDown(DIR_RIGHT,0) && pDI->JoystickGetLStickXAmount(0) > 100))
		{
			SetVelX(100);
			if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
				AudioManager::GetInstance()->playSound(walkingID);
		}
		else if( m_bmove &&  pDI->KeyDown(DIK_A) || (pDI->JoystickGetLStickDirDown(DIR_LEFT,0) && pDI->JoystickGetLStickXAmount(0) < -800))
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

		if( m_bmove && pDI->KeyDown(DIK_W) || (pDI->JoystickGetLStickDirDown(DIR_UP,0) && pDI->JoystickGetLStickYAmount(0) < -400))
		{
			SetVelY(-100);
			if(!AudioManager::GetInstance()->isSoundPlaying(walkingID))
				AudioManager::GetInstance()->playSound(walkingID);
		}
		else if( m_bmove && pDI->KeyDown(DIK_S) || (pDI->JoystickGetLStickDirDown(DIR_DOWN,0) && pDI->JoystickGetLStickYAmount(0) > 10))
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
	else if( m_nState == PSTATE_RELOAD )
	{
		if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) )
		{
			if( m_currWeapon->GetWeaponType() == WPN_PISTOL  && m_playerAnim.curAnimation != 28 )
			{
				m_playerAnim.curAnimation = 28;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if( m_currWeapon->GetWeaponType() == WPN_RIFLE  && m_playerAnim.curAnimation != 32 )
			{
				m_playerAnim.curAnimation = 32;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if( m_currWeapon->GetWeaponType() == WPN_SHOTGUN && m_playerAnim.curAnimation != 36 )
			{
				m_playerAnim.curAnimation = 36;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) )
		{
			if( m_currWeapon->GetWeaponType() == WPN_PISTOL && m_playerAnim.curAnimation != 30 )
			{
				m_playerAnim.curAnimation = 30;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if( m_currWeapon->GetWeaponType() == WPN_RIFLE  && m_playerAnim.curAnimation != 34 )
			{
				m_playerAnim.curAnimation = 34;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if( m_currWeapon->GetWeaponType() == WPN_SHOTGUN && m_playerAnim.curAnimation != 38 )
			{
				m_playerAnim.curAnimation = 38;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
		}
		else if(GetDirection() == DIRE_RIGHT )
		{
			if( m_currWeapon->GetWeaponType() == WPN_PISTOL && m_playerAnim.curAnimation != 29 )
			{
				m_playerAnim.curAnimation = 29;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if( m_currWeapon->GetWeaponType() == WPN_RIFLE  && m_playerAnim.curAnimation != 33 )
			{
				m_playerAnim.curAnimation = 33;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if( m_currWeapon->GetWeaponType() == WPN_SHOTGUN && m_playerAnim.curAnimation != 37 )
			{
				m_playerAnim.curAnimation = 37;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
		}
		else if(GetDirection() == DIRE_LEFT  && m_playerAnim.curAnimation != 31 )
		{
			if( m_currWeapon->GetWeaponType() == WPN_PISTOL )
			{
				m_playerAnim.curAnimation = 31;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if( m_currWeapon->GetWeaponType() == WPN_RIFLE  && m_playerAnim.curAnimation != 35 )
			{
				m_playerAnim.curAnimation = 35;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
			else if( m_currWeapon->GetWeaponType() == WPN_SHOTGUN && m_playerAnim.curAnimation != 39 )
			{
				m_playerAnim.curAnimation = 39;
				m_playerAnim.curFrame = 0;
				m_playerAnim.fTime = 0;
			}
		}
	}

	if(m_nState == PSTATE_IDLE || m_nState == PSTATE_SHOOT)
	{
		if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && GetVelY() < 0)
		{
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE && m_playerAnim.curAnimation != 24)
			{
				m_playerAnim.curAnimation = 24;
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
			/*else
			{
			m_playerAnim.curAnimation = 0;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
			}*/
		}
		else if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && GetVelY() == 0)
		{
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE )
			{
				m_playerAnim.curAnimation = 24;
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
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE && m_playerAnim.curAnimation != 26)
			{
				m_playerAnim.curAnimation = 26;
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
				m_playerAnim.curAnimation = 26;
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
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE && m_playerAnim.curAnimation != 27)
			{
				m_playerAnim.curAnimation = 27;
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
				m_playerAnim.curAnimation = 27;
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
			if(m_currWeapon->GetWeaponType() == WPN_MACHETE && m_playerAnim.curAnimation != 25)
			{
				m_playerAnim.curAnimation = 25;
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
				m_playerAnim.curAnimation = 25;
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
	else if( m_nState == PSTATE_SWING )
	{
		if((GetDirection() == DIRE_UP || GetDirection() == DIRE_UPLEFT || GetDirection() == DIRE_UPRIGHT) && m_playerAnim.curAnimation != 16)
		{
			m_playerAnim.curAnimation = 16;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if((GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT) && m_playerAnim.curAnimation != 18)
		{
			m_playerAnim.curAnimation = 18;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if( GetDirection() == DIRE_RIGHT && m_playerAnim.curAnimation != 19 )
		{
			m_playerAnim.curAnimation = 19;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
		else if( GetDirection() == DIRE_LEFT && m_playerAnim.curAnimation != 17 )
		{
			m_playerAnim.curAnimation = 17;
			m_playerAnim.curFrame = 0;
			m_playerAnim.fTime = 0;
		}
	}


	for(unsigned int i = 0; i < m_vpWeapons.size(); i++)
		m_vpWeapons[i]->Update(fElapsedTime);

	//Updating the player's frame and timer for animations
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

void Player::Render()
{
	ViewManager* pVM = ViewManager::GetInstance();
	//RECT tmpRECT = GetRect2();
	//tmpRECT.bottom -= GamePlayState::GetInstance()->GetCamera().y;
	//tmpRECT.top -= GamePlayState::GetInstance()->GetCamera().y;
	//tmpRECT.left -= GamePlayState::GetInstance()->GetCamera().x;
	//tmpRECT.right -= GamePlayState::GetInstance()->GetCamera().x;
	//pVM->DrawRect(tmpRECT, 255, 255, 255, 255);

	if( IsOn() )
	{
		RECT c = {946, 67, c.left+54, c.top+45};

		if( GetDirection() == DIRE_RIGHT )
			pVM->DrawStaticTexture(m_nlightglare, ((GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2) - 19,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y-17), 1.0f, 1.0f, &c);
		else if ( GetDirection() == DIRE_UP || GetDirection() == DIRE_UPRIGHT || GetDirection() == DIRE_UPLEFT )
			pVM->DrawStaticTexture(m_nlightglare, ((GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2) - 35,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y-15), 1.0f, 1.0f, &c);
	}

	//Drawing Player Placeholder Sprite
	for( unsigned int i = 0; i < GamePlayState::GetInstance()->GetFireA().size(); ++i)
	{
		float tmpx, tmpy;
		tmpx = float(Particle_Manager::GetInstance()->GetActiveEmitter(GamePlayState::GetInstance()->GetFireA()[i])->rect.left);
		tmpy = float(Particle_Manager::GetInstance()->GetActiveEmitter(GamePlayState::GetInstance()->GetFireA()[i])->rect.top);
		RECT tmp = {0,0,32,32};
		pVM->DrawStaticTexture(GamePlayState::GetInstance()->GetLogID(),tmpx-GamePlayState::GetInstance()->GetCamera().x - 16,tmpy-GamePlayState::GetInstance()->GetCamera().y - 16,2.0f,2.0f, &tmp);
	}

	pVM->DrawAnimation(&m_playerAnim, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2  ,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight());
	/*pVM->DrawRect(GetRect(), 255, 255, 255);*/

	if( ( GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT ) && IsOn() )
	{
		RECT c = {946, 67, c.left+54, c.top+45};
		pVM->DrawStaticTexture(m_nlightglare, ((GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2) - 15,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y-17), 1.0f, 1.0f, &c);
	}
	else if( GetDirection() == DIRE_LEFT && IsOn() )
	{
		RECT c = {946, 67, c.left+54, c.top+45};
		pVM->DrawStaticTexture(m_nlightglare, ((GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth()/2) - 30,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y-15), 1.0f, 1.0f, &c);
	}
	BaseCharacter::Render();
	//if( ( GetDirection() == DIRE_DOWN || GetDirection() == DIRE_DOWNLEFT || GetDirection() == DIRE_DOWNRIGHT || GetDirection() == DIRE_RIGHT))
	//{
	//	Particle_Manager::GetInstance()->GetActiveEmitter(smokeA)
	//}
	for( unsigned int i = 0; i < GamePlayState::GetInstance()->GetFireA().size(); ++i)
		Particle_Manager::GetInstance()->GetActiveEmitter(GamePlayState::GetInstance()->GetFireA()[i])->Render();

	Animation* thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	Frame thisFrame = thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame];

	/*if( m_nState == PSTATE_SWING)
	{
		Animation* thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	Frame thisFrame = thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame];
	RECT collRect = {long(thisFrame.activeRect.left+GetPosX() - GamePlayState::GetInstance()->GetCamera().x+10), long(thisFrame.activeRect.top+GetPosY()- GamePlayState::GetInstance()->GetCamera().y+30), thisFrame.activeRect.right+(long)GetPosX() - GamePlayState::GetInstance()->GetCamera().x+10, thisFrame.activeRect.bottom+(long)GetPosY() - GamePlayState::GetInstance()->GetCamera().y+30};
	pVM->DrawRect(collRect, 255, 21, 39);
	}*/
}

bool Player::CheckCollision(IObjects* pBase) 
{
	Animation* thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	Frame thisFrame = thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame];

	if( m_nState == PSTATE_SWING && pBase->GetObjectType() == OBJ_CHARACTER )
	{
		BaseCharacter* tmp = (BaseCharacter*)pBase;

		if( tmp->GetCharacterType() == CHA_ENEMY || tmp->GetCharacterType() == CHA_BOSS2 )
		{
			RECT cRect;
			RECT collRect = {long(thisFrame.activeRect.left+GetPosX()+10), long(thisFrame.activeRect.top+GetPosY()+30), thisFrame.activeRect.right+(long)GetPosX()+10, thisFrame.activeRect.bottom+(long)GetPosY()+30};
			if( IntersectRect(&cRect, &collRect, &pBase->GetRect() ) && m_playerAnim.curFrame == 1 )
			{
				tmp->SetHealth(tmp->GetHealth()-m_currWeapon->GetDamage());
				EventSystem::GetInstance()->SendUniqueEvent( "target_hit", pBase );

				GamePlayState* gameState = GamePlayState::GetInstance();
				Particle_Manager* m_pPM = Particle_Manager::GetInstance();
				int bloodA1;
				int bloodA2;
				int bloodA3;

				RECT tmpRect1 = collRect;
				//RECT tmpRect1 = {LONG(m_nPosX - 5), LONG(m_nPosY - 5), LONG(m_nPosX + 5), LONG(m_nPosY + 5) };


				if( GetDirection() == DIRE_DOWNRIGHT)
				{
					bloodA1 = m_pPM->ActivateEmitter(gameState->GetBloodL1());
					bloodA2 = m_pPM->ActivateEmitter(gameState->GetBloodL7());
					bloodA3 = m_pPM->ActivateEmitter(gameState->GetBloodL3());
				}
				else if( GetDirection() == DIRE_UPRIGHT)
				{
					bloodA1 = m_pPM->ActivateEmitter(gameState->GetBloodL2());
					bloodA2 = m_pPM->ActivateEmitter(gameState->GetBloodL8());
					bloodA3 = m_pPM->ActivateEmitter(gameState->GetBloodL3());
				}
				else if( GetDirection() == DIRE_RIGHT)
				{
					bloodA1 = m_pPM->ActivateEmitter(gameState->GetBloodL3());
					bloodA2 = m_pPM->ActivateEmitter(gameState->GetBloodL2());
					bloodA3 = m_pPM->ActivateEmitter(gameState->GetBloodL1());
				}
				else if( GetDirection() == DIRE_LEFT)
				{
					bloodA1 = m_pPM->ActivateEmitter(gameState->GetBloodL4());
					bloodA2 = m_pPM->ActivateEmitter(gameState->GetBloodL5());
					bloodA3 = m_pPM->ActivateEmitter(gameState->GetBloodL6());
				}
				else if( GetDirection() == DIRE_UPLEFT)
				{
					bloodA1 = m_pPM->ActivateEmitter(gameState->GetBloodL5());
					bloodA2 = m_pPM->ActivateEmitter(gameState->GetBloodL4());
					bloodA3 = m_pPM->ActivateEmitter(gameState->GetBloodL8());
				}
				else if(GetDirection() == DIRE_DOWNLEFT)
				{
					bloodA1 = m_pPM->ActivateEmitter(gameState->GetBloodL6());
					bloodA2 = m_pPM->ActivateEmitter(gameState->GetBloodL4());
					bloodA3 = m_pPM->ActivateEmitter(gameState->GetBloodL7());
				}
				else if( GetDirection() == DIRE_DOWN)
				{
					bloodA1 = m_pPM->ActivateEmitter(gameState->GetBloodL7());
					bloodA2 = m_pPM->ActivateEmitter(gameState->GetBloodL6());
					bloodA3 = m_pPM->ActivateEmitter(gameState->GetBloodL1());
				}
				else if(GetDirection() == DIRE_UP)
				{
					bloodA1 = m_pPM->ActivateEmitter(gameState->GetBloodL8());
					bloodA2 = m_pPM->ActivateEmitter(gameState->GetBloodL5());
					bloodA3 = m_pPM->ActivateEmitter(gameState->GetBloodL2());
				}
				m_pPM->GetActiveEmitter(bloodA1)->SetRect(tmpRect1);
				m_pPM->GetActiveEmitter(bloodA2)->SetRect(tmpRect1);
				m_pPM->GetActiveEmitter(bloodA3)->SetRect(tmpRect1);
				bloodA.push_back(bloodA1);
				bloodA.push_back(bloodA2);
				bloodA.push_back(bloodA3);
			}
		}
	}
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
					Bullet* pBU = (Bullet*)pBase;
					if(pBU->GetOwner()->GetOwner() == this)
						return false;
					else
						return true;
				}
				if(pBase->GetObjectType() == OBJ_CHARACTER)
				{
					BaseCharacter* tmpChar = (BaseCharacter*)(pBase);
					if(tmpChar->GetCharacterType() == CHA_BOSS2)
					{
						Boss2* tmpBoss = (Boss2*)tmpChar;
						//if(float(tmpBoss->GetHealth() / 1000.0f) < .5f)
						{
							if(pBase->GetRect().left <= GetRect().right && GetRect().right - pBase->GetRect().left <= 5)
							{
								//MoveTo(float(pBase->GetRect().left-GetWidth() * 4), this->GetPosY(), 90);
								SetPosX(float(pBase->GetRect().left-GetWidth()));
								SetPushX(float((GetWidth() * 2)-pBase->GetRect().left));
							}
							else if(pBase->GetRect().right >= GetRect().left && pBase->GetRect().right - GetRect().left <= 5)
							{
								//MoveTo(float(pBase->GetRect().left+GetWidth() * 4), this->GetPosY(), 90);
								SetPosX(float(pBase->GetRect().right));
								SetPushX(float(pBase->GetRect().right+GetWidth() * 2));
							}
							else if(pBase->GetRect().top <= GetRect().bottom && GetRect().bottom - pBase->GetRect().top <= 5)
							{
								//MoveTo(this->GetPosX(), float(pBase->GetRect().bottom-GetHeight() * 4), 90);						
								SetPosY(float(pBase->GetRect().top-GetHeight()));
								SetPushY(float((GetHeight() * 2) - pBase->GetRect().top));
							}
							else if(pBase->GetRect().bottom >= GetRect().top && pBase->GetRect().bottom - GetRect().top <= 5)
							{
								//MoveTo(this->GetPosX(), float(pBase->GetRect().bottom+GetHeight() * 4), 90);				
								SetPosY(float(pBase->GetRect().bottom));
								SetPushY(float(pBase->GetRect().bottom+GetHeight() * 2));
							}
						}
						if (dammageTimer > 1)
						{
							SetHealth(GetHealth()-1);
							dammageTimer = 0;
						}
					}
					else
					{
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
	pWeapon->SetOwner(this);
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
			if(!lose)
			{
				AudioManager::GetInstance()->GetSoundChannel(hitID)->stop();
				AudioManager::GetInstance()->playSound(hitID);
			}
			this->SetBleeding(true);
		}
	}
	else if(pEvent->GetEventID() == "hit_wall")
	{

	}
}


void Player::MoveTo(float x, float y, float speed) 
{
	float storey = GetPosY() - y;
	float storex = GetPosX() - x;

	if(storey >= -10 && storey <= 10)
		SetVelY(0);
	else if(GetPosY() < y)
		SetVelY(GetVelY() + speed);
	else if(GetPosY() > y)
		SetVelY(GetVelY() -speed);

	if(storex >= -10 && storex <= 10)
		SetVelX(0);
	else if(GetPosX() < x)
		SetVelX(GetVelX() +speed);
	else if(GetPosX() > x)
		SetVelX(GetVelX() -speed);
}
