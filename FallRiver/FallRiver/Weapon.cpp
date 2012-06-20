#include "Weapon.h"
#include "DirectInput.h"
#include "CreateBullet.h"
#include "MessageSystem.h"
#include "ViewManager.h"

Weapon::Weapon()
{
	m_dwTickCount = 0;
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

	return true;
}

void Weapon::Update(float fElapsedTime)
{
	DirectInput* pDI = DirectInput::GetInstance();

	if(pDI->KeyDown(DIK_SPACE) && 	m_dwTickCount  < GetTickCount() )
	{
		if( m_nWeaponType != WPN_MACHETE && m_nAmmo > 0 )
		{
			CreateBullet* pMsg = new CreateBullet( this );
			MessageSystem::GetInstance()->SendMsg( pMsg );
			pMsg = nullptr;
			m_nAmmo--;
			m_dwTickCount = GetTickCount() + (DWORD)m_fFireRate;
			if(m_nWeaponType == WPN_SHOTGUN)
			{
				for(int i = 0; i < 2; i++)
				{
					CreateBullet* pMsg = new CreateBullet( this );
					MessageSystem::GetInstance()->SendMsg( pMsg );
					pMsg = nullptr;
				}
			}
		}
	}	
}

void Weapon::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 0, 200, 210 );
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
