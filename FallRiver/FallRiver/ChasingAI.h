#ifndef __ChasingAI_h__
#define __ChasingAI_h__

#include "Enemy.h"


class ChasingAI: public Enemy
{
private:
	int zombieHitID;
	int zombieWalkingID;
	int notifyID;
	bool notified;
	bool locked;
	DWORD attackDelay;
	DWORD m_dwDeathTime;
	float cryTimer;

public: 
	ChasingAI();
	~ChasingAI();

	void Update(float fElapsedTime);

	void Render();

	void SetLocked(bool lock) {locked = lock;}

	bool CheckCollision(IObjects* pBase);

	void HandleEvent(Event* pEvent);
};

#endif
