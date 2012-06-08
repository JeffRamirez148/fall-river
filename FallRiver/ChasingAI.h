#include <Windows.h>
using namespace std;

#ifndef __ChasingAI_h__
#define __ChasingAI_h__

// #include "ObjectFactory.h"
// #include "BaseCharacter.h"
#include "Enemy.h"

class ObjectFactory;
// class BaseCharacter;
// class Enemy;
class Event;

class ChasingAI: public Enemy
{
public: 
	void Update(float fElapsedTime);

	void Render();

	bool CheckCollision(BaseCharacter* pBase);

	void HandleEvent(Event* pEvent);
};

#endif
