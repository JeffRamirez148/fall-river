#include <Windows.h>
using namespace std;

#ifndef __DestroyBullet_h__
#define __DestroyBullet_h__

// #include "Bullet.h"
#include "Message.h"

class Bullet;
// class Message;

class DestroyBullet: public Message
{
	private: 
		Bullet* m_pBullet;

	public: 
	DestroyBullet(Bullet* pBullet);

	~DestroyBullet();
};

#endif
