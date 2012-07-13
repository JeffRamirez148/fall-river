#ifndef __Boss1_h__
#define __Boss1_h__

#include "Enemy.h"
#include "IListener.h"

class Boss1: public Enemy
{	
	DWORD m_dwFireDelay;

	Weapon* m_pWeapon;
	BaseObject* m_cInTheWay;

	int m_nStages;
	int m_nMinnions;

public: 
	Boss1();
	~Boss1();

	void SetWeapon(Weapon* pWeapon) {m_pWeapon = pWeapon;}

	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual bool CheckCollision(IObjects* pBase);

	virtual void HandleEvent(Event* pEvent);
};

#endif
