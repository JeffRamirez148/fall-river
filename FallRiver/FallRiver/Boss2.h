#include <Windows.h>

#ifndef __Boss2_h__
#define __Boss2_h__

// #include "ObjectFactory.h"
// #include "BaseCharacter.h"
#include "Enemy.h"

// class BaseCharacter;
// class Enemy;
class Event;

class Boss2: public Enemy
{
public: 
	virtual void Update(float aTime);

	virtual void Render();

	void HandleEvent(Event* Event);

	virtual bool CheckCollision(BaseCharacter* pBase);
};

#endif
