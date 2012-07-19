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
	int talkBox;
	bool teaching;
	bool talking;

public: 

	CompanionAI();
	~CompanionAI();

	bool IsTeaching() {return teaching;}
	void SetTeaching(bool teach) {teaching = teach;}

	int GetStage() {return m_nStages;}
	int GetStep() {return m_nStep;}
	void NextStep() { m_nStep++; }

	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual bool CheckCollision(IObjects* pBase);

	virtual void HandleEvent(Event* pEvent);

	void SaySomething();
};

#endif
