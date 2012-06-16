#ifndef __ShootingAi_h__
#define __ShootingAi_h__
#include "Enemy.h"


class ShootingAi: public Enemy
{
public: 
	ShootingAi();
	~ShootingAi();

	virtual void Update(float aFElapsedTime);
	virtual void Render();
	virtual bool CheckCollision(IObjects* aPBase);
	virtual void HandleEvent(Event* aPEvent);
};

#endif
