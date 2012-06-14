#include "Weapon.h"
#include "DirectInput.h"
#include "CreateBullet.h"
#include "MessageSystem.h"

Weapon::Weapon()
{

}

Weapon::~Weapon()
{
}

bool Weapon::Init(WEAPONTYPE wType, int nAmmo, int nDamage, float currRotation )
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
		m_fFireRate = 0.5f;
		m_fFiringRange = 10.0f;
		m_nClip = 10;
		break;
	case WPN_SHOTGUN:
		m_fFireRate = 1.0f;
		m_fFiringRange = 10.0f;
		m_nClip = 3;
		break;
	case WPN_RIFLE:
		break;
	case WPN_MACHETE:
		m_bMelee = true;
		break;
	}

	return true;
}

void Weapon::Update(float fElapsedTime)
{
	DirectInput* pDI = DirectInput::GetInstance();

	if(pDI->KeyDown(DIK_SPACE) )
	{
		CreateBullet* pMsg = new CreateBullet( this );
		MessageSystem::GetInstance()->SendMsg( pMsg );
		pMsg = nullptr;
	}	
}

void Weapon::Render() 
{
	
}

RECT Weapon::GetRect()
{
	RECT cRect = {GetPosX(), GetPosY(), GetPosX()+GetWidth(), GetPosY()+GetHeight() };
	return cRect;
}

bool Weapon::CheckCollision(BaseObject* pBase)
{
	RECT cRect;
	if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == false  )
		return false;
	return true;
}
