#ifndef __ShootingAi_h__
#define __ShootingAi_h__
#include "Enemy.h"
#include <Windows.h>

class Weapon;

class ShootingAi: public Enemy
{
private:
	Weapon* m_pWeapon;
	DWORD m_dwFireDelay;

	BaseObject* m_cInTheWay;

public: 
	ShootingAi();
	~ShootingAi();

	virtual void Update(float aFElapsedTime);
	virtual void Render();
	void SetWeapon(Weapon* pWeapon) {m_pWeapon = pWeapon;}
	virtual bool CheckCollision(IObjects* aPBase);
	virtual void HandleEvent(Event* aPEvent);
};

#endif
