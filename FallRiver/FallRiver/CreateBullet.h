#ifndef __CreateBullet_h__
#define __CreateBullet_h__

#include "Message.h"

class Weapon;

class CreateBullet: public Message
{
public:
	CreateBullet(Weapon* pWeapon);
	virtual ~CreateBullet(void);

	void SetWeapon( Weapon* pWeapon )	{ m_pWeapon = pWeapon; }
	Weapon* GetWeapon( void )		{ return m_pWeapon; }
private:
	Weapon*	m_pWeapon;
};

#endif
