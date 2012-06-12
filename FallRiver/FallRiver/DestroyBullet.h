#ifndef __DestroyBullet_h__
#define __DestroyBullet_h__

#include "Message.h"

class Bullet;

class DestroyBullet: public Message
{
private: 
	Bullet* m_pBullet;

public: 
	DestroyBullet(Bullet* pBullet);
	Bullet* GetBullet(void) { return m_pBullet; }
	virtual ~DestroyBullet();
};

#endif
