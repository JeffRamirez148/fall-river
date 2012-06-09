#ifndef __Boss1_h__
#define __Boss1_h__

#include "Enemy.h"
#include "IListener.h"

class Boss1: public Enemy
{
public: 
	virtual void Update(float fElapsedTime) = 0;

	virtual void Render() = 0;

	virtual bool CheckCollision(BaseObject* pBase) = 0;

	virtual void HandleEvent(Event* pEvent) = 0;
};

#endif
