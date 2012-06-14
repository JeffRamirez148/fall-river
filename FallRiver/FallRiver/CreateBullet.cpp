#include "CreateBullet.h"
#include "Weapon.h"

CreateBullet::CreateBullet(Weapon* pWeapon) : Message(MSG_CREATE_BULLET)
{
	m_pWeapon = pWeapon;

	if( m_pWeapon != nullptr )
		m_pWeapon->AddRef();
}

CreateBullet::~CreateBullet() 
{
	if( m_pWeapon != nullptr )
		m_pWeapon->Release();

	m_pWeapon = nullptr;
}

