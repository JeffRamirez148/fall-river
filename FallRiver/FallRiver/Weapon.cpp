#include "Weapon.h"
#include "DirectInput.h"
#include "CreateBullet.h"
#include "MessageSystem.h"
#include "ViewManager.h"
#include "AudioManager.h"

Weapon::Weapon()
{
	m_bReloading = false;
	m_nAmmo = 0;
	m_nDamage = 0;
	swingMissID	= -1;
	shotID		= -1;
	reloadID	= -1;
	m_fFireRate = 0;
	m_fFiringRange = 0;
	m_nClip = 0;
	m_nDamage = 0;
	m_nMaxClip = 0;
}

Weapon::~Weapon()
{
}

bool Weapon::Init(int wType, int nAmmo, float currRotation )
{
	// Just in case
	if(wType < WPN_MAX)
		m_nWeaponType = wType;
	else 
		return false;

	// Set up variables
	m_nAmmo = nAmmo;
	m_fCurrRotation = currRotation;
	

	switch( m_nWeaponType )
	{
	case WPN_PISTOL:
		m_fFireRate = 500;
		m_fFiringRange = 128.0f;
		m_nClip = 10;
		m_nDamage = 25;
		m_nMaxClip = 10;
		break;
	case WPN_SHOTGUN:
		m_fFireRate = 1000;
		m_fFiringRange = 128.0f;
		m_nClip = 5;
		m_nDamage = 20;
		m_nMaxClip = 5;
		break;
	case WPN_RIFLE:
		m_fFireRate = 200;
		m_fFiringRange = 288.0f;
		m_nClip = 8;
		m_nDamage = 10;
		m_nMaxClip = 8;
		break;
	case WPN_MACHETE:
		m_fFireRate = 500;
		m_fFiringRange = 128.0f;
		m_nClip = 10;
		m_nDamage = 10;
		m_nMaxClip = 10;
		break;
	}
	AudioManager* m_pAM = AudioManager::GetInstance();
	swingMissID = m_pAM->RegisterSound("resource/Sounds/swingMiss.wav");
	shotID = m_pAM->RegisterSound("resource/Sounds/shot.wav");
	reloadID = m_pAM->RegisterSound("resource/Sounds/reload.wav");

	FMOD_VECTOR sound1 = { 0, 0, 0 };
	m_pAM->setSoundVel(swingMissID, sound1);
	m_pAM->setSoundLooping(swingMissID, false);
	m_pAM->setSoundVel(shotID, sound1);
	m_pAM->setSoundLooping(shotID, false);
	m_pAM->setSoundVel(reloadID, sound1);
	m_pAM->setSoundLooping(reloadID, false);
	sound1.x = m_pOwner->GetPosX();
	sound1.y = m_pOwner->GetPosY();
	m_pAM->setSoundPos(swingMissID, sound1);
	m_pAM->setSoundPos(shotID, sound1);
	m_pAM->setSoundPos(reloadID, sound1);


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
	m_pAM->setSoundPos(reloadID, sound1);
}

void Weapon::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 0, 200, 210 );
}

void Weapon::FireWeapon()
{
	if( m_nClip == 0 || m_bReloading && m_nWeaponType != WPN_MACHETE )
	{
		if(!Reload())
			return;
		else 
			m_bReloading = false;
	}
	if( m_nWeaponType != WPN_MACHETE && m_nAmmo > 0 )
	{
		CreateBullet* pMsg = new CreateBullet( this );
		MessageSystem::GetInstance()->SendMsg( pMsg );
		pMsg = nullptr;
		m_nClip--;
		//if(m_nWeaponType == WPN_SHOTGUN)
		//{
		//	for(int i = 0; i < 2; i++)
		//	{
		//		CreateBullet* pMsg = new CreateBullet( this );
		//		MessageSystem::GetInstance()->SendMsg( pMsg );
		//		pMsg = nullptr;
		//	}
		//}
		
		AudioManager::GetInstance()->GetSoundChannel(shotID)->stop();
		AudioManager::GetInstance()->playSound(shotID);
	}
}

bool Weapon::Reload()
{
	if( m_nAmmo > 0 && m_nClip < m_nMaxClip)
	{
		m_bReloading = true;
		m_nAmmo--;
		m_nClip++;
		return false;
	}
	else
	{
		AudioManager::GetInstance()->GetSoundChannel(reloadID)->stop();
		AudioManager::GetInstance()->playSound(reloadID);
	}
	return true;

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
