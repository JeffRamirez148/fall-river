#ifndef __ChasingAI_h__
#define __ChasingAI_h__

#include "Enemy.h"


class ChasingAI: public Enemy
{
private:
	bool m_bIsChasing;
	bool m_bIsMoving;


	BaseObject* m_cInTheWay;

public: 
	ChasingAI();
	~ChasingAI();

	void Update(float fElapsedTime);

	void Render();

	bool CheckCollision(IObjects* pBase);

	void HandleEvent(Event* pEvent);
};

#endif
