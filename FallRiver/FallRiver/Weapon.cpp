#include "Weapon.h"
#include "DirectInput.h"
#include "CreateBullet.h"
#include "MessageSystem.h"
#include "ViewManager.h"
#include "AudioManager.h"

Weapon::Weapon()
{
	
}

Weapon::~Weapon()
{
}

bool Weapon::Init(int wType, int nAmmo, int nDamage, float currRotation )
{
	// Just in case
	if(wType < WPN_MAX)
		m_nWeaponType = wType;
	else 
		return false;

	// Set up variables
	m_nAmmo = nAmmo;
	m_nDamage = nDamage;
	m_fCurrRotation = currRotation;
	m_bMelee = false;

	switch( m_nWeaponType )
	{
	case WPN_PISTOL:
		m_fFireRate = 500;
		m_fFiringRange = 128.0f;
		m_nClip = 10;
		break;
	case WPN_SHOTGUN:
		m_fFireRate = 1000;
		m_fFiringRange = 64.0f;
		m_nClip = 5;
		break;
	case WPN_RIFLE:
		m_fFireRate = 1000;
		m_fFiringRange = 288.0f;
		m_nClip = 8;
		break;
	case WPN_MACHETE:
		m_bMelee = true;
		break;
	}
	AudioManager* m_pAM = AudioManager::GetInstance();
	swingMissID = m_pAM->RegisterSound("resource/Sounds/swingMiss.wav");
	shotID = m_pAM->RegisterSound("resource/Sounds/shot.wav");

	FMOD_VECTOR sound1 = { 0, 0, 0 };
	m_pAM->setSoundVel(swingMissID, sound1);
	m_pAM->setSoundLooping(swingMissID, false);
	m_pAM->setSoundVel(shotID, sound1);
	m_pAM->setSoundLooping(shotID, false);
	sound1.x = m_pOwner->GetPosX();
	sound1.y = m_pOwner->GetPosY();
	m_pAM->setSoundPos(swingMissID, sound1);
	m_pAM->setSoundPos(shotID, sound1);

	return true;
}

void Weapon::Update(float fElapsedTime)
{
	SetPosX(m_pOwner->GetPosX()+m_pOwner->GetWidth()/2);
	SetPosY(m_pOwner->GetPosY());

	DirectInput* pDI = DirectInput::GetInstance();

	AudioManager* m_pAM = AudioManager::GetInstance();
	FMOD_VECTOR sound1 = { 0, 0, 0 };
	sound1.x = m_pOwner->GetPosX();
	sound1.y = m_pOwner->GetPosY();
	m_pAM->setSoundPos(swingMissID, sound1);
	m_pAM->setSoundPos(shotID, sound1);
}

void Weapon::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 0, 200, 210 );
}

void Weapon::FireWeapon()
{
	if( m_nWeaponType != WPN_MACHETE && m_nAmmo > 0 )
	{
		CreateBullet* pMsg = new CreateBullet( this );
		MessageSystem::GetInstance()->SendMsg( pMsg );
		pMsg = nullptr;
		m_nAmmo--;
		if(m_nWeaponType == WPN_SHOTGUN)
		{
			for(int i = 0; i < 2; i++)
			{
				CreateBullet* pMsg = new CreateBullet( this );
				MessageSystem::GetInstance()->SendMsg( pMsg );
				pMsg = nullptr;
			}
		}
		AudioManager::GetInstance()->playSound(shotID);
	}
}


RECT Weapon::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight()) };
	return cRect;
}

bool Weapon::CheckCollision(IObjects* pBase)
{
	RECT cRect;
	if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == false  )
		return false;
	return true;
}
