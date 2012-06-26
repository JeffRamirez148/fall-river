#include <Windows.h>

#ifndef __CompanionAI_h__
#define __CompanionAI_h__

#include "BaseCharacter.h"

class Weapon;
class Event;
class CompanionAI;

class CompanionAI: public BaseCharacter
{
private: 
	Weapon* m_nWeapon;

public: 

	CompanionAI();
	~CompanionAI();

	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual bool CheckCollision(IObjects* pBase);

	virtual void HandleEvent(Event* pEvent);

	void SaySomething();
};

#endif
