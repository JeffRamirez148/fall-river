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
	DWORD m_dwGunReset;

	BaseObject* m_cInTheWay;
	int hitID;
	int walkingID;
	int notifyID;
	bool notified;
	bool boss;
	float autoBotsRollOut;

public: 
	ShootingAi();
	~ShootingAi();

	virtual void Update(float aFElapsedTime);
	virtual void Render();
	void SetWeapon(Weapon* pWeapon) {m_pWeapon = pWeapon;}
	virtual bool CheckCollision(IObjects* aPBase);
	virtual void HandleEvent(Event* aPEvent);
	bool GetBossBool() {return boss;}
	void SetBossBool(bool hasBoss) { boss = hasBoss; }
};

#endif
