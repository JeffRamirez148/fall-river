#include <Windows.h>

#ifndef __CompanionAI_h__
#define __CompanionAI_h__

#include "BaseCharacter.h"

class Weapon;
class Event;
class Player;

class CompanionAI: public BaseCharacter
{
private: 
	Player* m_cFriend;
	Weapon* m_cWeapon;
	int m_nFontID;
	int m_nStages;
	int m_nStep;
	int m_nNumTimes;
	bool teaching;

public: 

	CompanionAI();
	~CompanionAI();

	bool IsTeaching() {return teaching;}

	void NextStep() { m_nStep++; }

	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual bool CheckCollision(IObjects* pBase);

	virtual void HandleEvent(Event* pEvent);

	void SaySomething();
};

#endif
