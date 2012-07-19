#ifndef __Boss2_h__
#define __Boss2_h__

#include "Enemy.h"
#include "IListener.h"

class Boss2: public Enemy
{
	Weapon*			m_pWeapon;
	DWORD	m_dwFireDelay;
	POINTFLOAT chargeDestination;
	POINTFLOAT oldPosition;

public: 
	Boss2();
	virtual void Update(float aTime);

	virtual void Render();

	void HandleEvent(Event* Event);
	void SetWeapon(Weapon* pWeapon) {m_pWeapon = pWeapon;}

	virtual bool CheckCollision(IObjects* pBase);
};

#endif
