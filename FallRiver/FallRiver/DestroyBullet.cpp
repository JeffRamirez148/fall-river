#include "DestroyBullet.h"
#include "Bullet.h"
#include "Message.h"

DestroyBullet::DestroyBullet(Bullet* aBullet) : Message(MSG_DESTROY_BULLET)
{
	m_pBullet = aBullet;
	if( m_pBullet != nullptr )
	m_pBullet->AddRef();
}

DestroyBullet::~DestroyBullet() 
{
	if( m_pBullet != nullptr )
		m_pBullet->Release();

	m_pBullet = nullptr;
}

