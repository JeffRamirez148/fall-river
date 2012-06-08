#include <Windows.h>
using namespace std;

#ifndef __ShootingAi_h__
#define __ShootingAi_h__

// #include "ObjectFactory.h"
// #include "DestroyEnemyS.h"
// #include "BaseCharacter.h"
#include "Enemy.h"

class ObjectFactory;
class DestroyEnemyS;
// class BaseCharacter;
// class Enemy;
class ShootingAi;

class ShootingAi: public Enemy
{
public: 
	virtual void Update(float aFElapsedTime);
	virtual void Render();
	virtual bool CheckCollision(BaseCharacter* aPBase);
	virtual void HandleEvent(Event* aPEvent);
};

#endif
