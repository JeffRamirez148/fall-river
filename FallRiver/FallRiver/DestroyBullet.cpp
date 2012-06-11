#include "DestroyBullet.h"
#include "Bullet.h"
#include "Message.h"

DestroyBullet::DestroyBullet(Bullet* aBullet) : Message(MSG_DESTROY_BULLET)
{
	m_pBullet = aBullet;
	m_pBullet->AddRef();
}

DestroyBullet::~DestroyBullet() 
{
	m_pBullet->Release();
}

