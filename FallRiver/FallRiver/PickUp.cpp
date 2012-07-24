#include "PickUp.h"
#include "DestroyPickUp.h"
#include "DirectInput.h"
#include "AudioManager.h"
#include "ViewManager.h"
#include "GamePlayState.h"
#include "DestroyPickUp.h"
#include "Player.h"

PickUp::PickUp()
{
	m_nObjectType = OBJ_PICKUP;
	m_nPickUpType = -1;
	audio = AudioManager::GetInstance();
	ammoID = audio->RegisterSound("resource/Sounds/reload.wav");
	batteriesID = audio->RegisterSound("resource/Sounds/PowerUpBattery.wav");
	medicineID = audio->RegisterSound("resource/Sounds/pillBottle.mp3");
	healthID = audio->RegisterSound("resource/Sounds/PowerUpHealth.wav");

	FMOD_VECTOR sound1 = { 0, 0, 0 };
	AudioManager::GetInstance()->setSoundVel(healthID, sound1);
	AudioManager::GetInstance()->setSoundVel(medicineID, sound1);
	AudioManager::GetInstance()->setSoundVel(batteriesID, sound1);
	AudioManager::GetInstance()->setSoundVel(ammoID, sound1);


	sound1.x = GamePlayState::GetInstance()->GetPlayer()->GetPosX();
	sound1.y = GamePlayState::GetInstance()->GetPlayer()->GetPosY();

	AudioManager::GetInstance()->setSoundPos(healthID, sound1);
	AudioManager::GetInstance()->setSoundLooping(healthID, false);
	AudioManager::GetInstance()->setSoundPos(medicineID, sound1);
	AudioManager::GetInstance()->setSoundLooping(medicineID, false);
	AudioManager::GetInstance()->setSoundPos(batteriesID, sound1);
	AudioManager::GetInstance()->setSoundLooping(batteriesID, false);
	AudioManager::GetInstance()->setSoundPos(ammoID, sound1);
	AudioManager::GetInstance()->setSoundLooping(ammoID, false);
}

PickUp::~PickUp()
{

}

void PickUp::Update(float fElapsedTime)
{
	fElapsedTime;
	FMOD_VECTOR sound1 = { GamePlayState::GetInstance()->GetPlayer()->GetPosX(), GamePlayState::GetInstance()->GetPlayer()->GetPosY(), 0};
	AudioManager::GetInstance()->setSoundPos(healthID, sound1);
	AudioManager::GetInstance()->setSoundPos(medicineID, sound1);
	AudioManager::GetInstance()->setSoundPos(batteriesID, sound1);
	AudioManager::GetInstance()->setSoundPos(ammoID, sound1);
}

void PickUp::Render() 
{
	ViewManager::GetInstance()->GetSprite()->Flush();

	
	RECT reRect = {long(GetPosX() - GamePlayState::GetInstance()->GetCamera().x), long(GetPosY() - GamePlayState::GetInstance()->GetCamera().y), long(reRect.left+GetWidth()), long(reRect.top + GetHeight())};

	//pVM->DrawRect(reRect, 255, 0, 255);
	if( this->GetImageID() != -1 )
	{
		ViewManager::GetInstance()->DrawStaticTexture(this->GetImageID(), GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y, 1.0f, 1.0f, nullptr, 0.0f, 0.0f);
	}
	else
	{
		if( GetPickUpType() == 0 )
		{
			ViewManager::GetInstance()->DrawRect(reRect,255,0,255);
		}
		else if( GetPickUpType() == 1 )
		{
			ViewManager::GetInstance()->DrawRect(reRect,255,0,0);
		}
		else if( GetPickUpType() == 2 )
		{
			ViewManager::GetInstance()->DrawRect(reRect,0,0,255);
		}
		else if( GetPickUpType() == 3 )
		{
			ViewManager::GetInstance()->DrawRect(reRect,255,255,255);
		}
		else if( GetPickUpType() == 4 )
		{
			ViewManager::GetInstance()->DrawRect(reRect,0,255,0);
		}
		else if( GetPickUpType() == 5 )
		{
			ViewManager::GetInstance()->DrawRect(reRect,255,255,0);
		}
		else if( GetPickUpType() == 6 )
		{
			ViewManager::GetInstance()->DrawRect(reRect,100,100,100);
		}
	}
}

RECT PickUp::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight()) };
	return cRect;
}

bool PickUp::CheckCollision(IObjects* pBase)
{
	RECT cRect;
	RECT temp = GetRect();
	RECT temp2 = pBase->GetRect();
	if( IntersectRect( &cRect, &temp, &temp2 ) == false  )
		return false;
	else
	{
		if( pBase->GetObjectType() == OBJ_CHARACTER )
		{
			BaseCharacter* pCh = (BaseCharacter*)pBase;
			if( pCh->GetCharacterType() == CHA_PLAYER )
			{
				switch( GetPickUpType() )
				{
				case SHOTGUN_AMMO:
					{
						for( unsigned int i = 0; i < GamePlayState::GetInstance()->GetPlayer()->GetWeapons().size(); i++)
						{
							audio->GetSoundChannel(ammoID)->stop();
							audio->playSound(ammoID);
							if( GamePlayState::GetInstance()->GetPlayer()->GetWeapons()[i]->GetWeaponType() == WPN_SHOTGUN )
							{
								GamePlayState::GetInstance()->GetPlayer()->GetWeapons()[i]->SetAmmo(GamePlayState::GetInstance()->GetPlayer()->GetWeapons()[i]->GetAmmo() + 2 );
								DestroyPickUp* pMsg = new DestroyPickUp(this);
								MessageSystem::GetInstance()->SendMsg(pMsg);
								pMsg = nullptr;
								break;
							}
						}
					}
					break;
				case RIFLE_AMMO:
					{
						audio->GetSoundChannel(ammoID)->stop();
						audio->playSound(ammoID);
						for( unsigned int i = 0; i < GamePlayState::GetInstance()->GetPlayer()->GetWeapons().size(); i++)
						{
							if( GamePlayState::GetInstance()->GetPlayer()->GetWeapons()[i]->GetWeaponType() == WPN_RIFLE )
							{
								GamePlayState::GetInstance()->GetPlayer()->GetWeapons()[i]->SetAmmo(GamePlayState::GetInstance()->GetPlayer()->GetWeapons()[i]->GetAmmo() + 12 );
								DestroyPickUp* pMsg = new DestroyPickUp(this);
								MessageSystem::GetInstance()->SendMsg(pMsg);
								pMsg = nullptr;
								break;
							}
						}
					}
					break;
				case PISTOL_AMMO:
					{
						audio->GetSoundChannel(ammoID)->stop();
						audio->playSound(ammoID);
						for( unsigned int i = 0; i < GamePlayState::GetInstance()->GetPlayer()->GetWeapons().size(); i++)
						{
							if( GamePlayState::GetInstance()->GetPlayer()->GetWeapons()[i]->GetWeaponType() == WPN_PISTOL )
							{
								GamePlayState::GetInstance()->GetPlayer()->GetWeapons()[i]->SetAmmo(GamePlayState::GetInstance()->GetPlayer()->GetWeapons()[i]->GetAmmo() + 8 );
								DestroyPickUp* pMsg = new DestroyPickUp(this);
								MessageSystem::GetInstance()->SendMsg(pMsg);
								pMsg = nullptr;
								break;
							}
						}
					}
					break;
				case MEDICINE:
					{
						audio->GetSoundChannel(medicineID)->stop();
						audio->playSound(medicineID);
						GamePlayState::GetInstance()->GetPlayer()->m_bHasMedicine = true;
						DestroyPickUp* pMsg = new DestroyPickUp(this);
						MessageSystem::GetInstance()->SendMsg(pMsg);
						pMsg = nullptr;

					}
					break;
				case HEALTH:
					{
						audio->GetSoundChannel(healthID)->stop();
						audio->playSound(healthID);
						int x = GamePlayState::GetInstance()->GetPlayer()->GetHealth() + 30 ;
						if( x > 500 )
						{
							x = 500;
						}
						GamePlayState::GetInstance()->GetPlayer()->SetHealth(x);
						DestroyPickUp* pMsg = new DestroyPickUp(this);
						MessageSystem::GetInstance()->SendMsg(pMsg);
						pMsg = nullptr;
					}
					break;
				case BATTERY:
					{
						audio->GetSoundChannel(batteriesID)->stop();
						audio->playSound(batteriesID);
						int x = GamePlayState::GetInstance()->GetPlayer()->battery + 20;
						if( x > 100 )
						{
							x = 100;
						}
						GamePlayState::GetInstance()->GetPlayer()->battery = x;
						DestroyPickUp* pMsg = new DestroyPickUp(this);
						MessageSystem::GetInstance()->SendMsg(pMsg);
						pMsg = nullptr;
					}
					break;
				}
			}
		}
	}
	return true;
}
