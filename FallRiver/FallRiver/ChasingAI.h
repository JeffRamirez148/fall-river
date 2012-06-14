#ifndef __ChasingAI_h__
#define __ChasingAI_h__

#include "Enemy.h"


class ChasingAI: public Enemy
{
public: 
	ChasingAI();
	~ChasingAI();

	void Update(float fElapsedTime);

	void Render();

	bool CheckCollision(BaseCharacter* pBase);

	void HandleEvent(Event* pEvent);
};

#endif
