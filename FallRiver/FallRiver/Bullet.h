#include <Windows.h>

#ifndef __Bullet_h__
#define __Bullet_h__

// #include "ObjectFactory.h"
// #include "DestroyBullet.h"
#include "BaseObject.h"

class ObjectFactory;
class DestroyBullet;
class Event;

class Bullet: public BaseObject
{
private: 
	int soundID;

public: 
	void Update(float fElapsedTime);

	void Render();

	void HandleEvent (Event* Event);
};

#endif
