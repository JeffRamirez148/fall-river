#include <Windows.h>

#ifndef __Boss1_h__
#define __Boss1_h__

// #include "ObjectFactory.h"
// #include "BaseCharacter.h"
#include "Enemy.h"

class ObjectFactory;
// class BaseCharacter;
// class Enemy;
class Boss1;

class Boss1: public Enemy
{
public: 
	virtual void Update(float fElapsedTime) = 0;

	virtual void Render() = 0;

	virtual bool CheckCollision(BaseCharacter* pBase) = 0;

	virtual void HandleEvent(Event* aPEvent) = 0;
};

#endif
