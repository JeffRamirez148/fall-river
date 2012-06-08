#include <Windows.h>

#ifndef __CompanionAI_h__
#define __CompanionAI_h__

// #include "ObjectFactory.h"
// #include "Weapon.h"
// #include "BaseCharacter.h"
#include "Enemy.h"

class ObjectFactory;
class Weapon;
// class BaseCharacter;
class Event;
class CompanionAI;

class CompanionAI: public Enemy
{
private: 
	int m_nFrameX;
	int m_nFrameY;
	Weapon* m_nWeapon;
	char* m_cAdvice;

public: 
	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual bool CheckCollision(BaseCharacter* pBase);

	virtual void HandleEvent(Event* pEvent);

	void ShootEnemy(Enemy* pEnemy);

	void SaySomething();
};

#endif
