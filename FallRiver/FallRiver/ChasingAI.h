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
	bool helped;
	DWORD attackDelay;
	float cryTimer;

public: 
	ChasingAI();
	~ChasingAI();

	void Update(float fElapsedTime);

	void Render();

	bool CheckCollision(IObjects* pBase);

	void HandleEvent(Event* pEvent);
};

#endif
