#include <Windows.h>
using namespace std;

#ifndef __Terrain_h__
#define __Terrain_h__

// #include "Level.h"
// #include "ObjectFactory.h"
// #include "BaseCharacter.h"
#include "BaseObject.h"

class Level;
class ObjectFactory;
class BaseCharacter;
// class BaseObject;
class Terrain;

class Terrain: public BaseObject
{
public: 
	virtual void Update(float aFElapsedTime);
	virtual void Render();
	virtual bool CheckCollision(BaseCharacter* aPBase);
};

#endif
