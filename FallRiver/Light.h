#include <Windows.h>
using namespace std;

#ifndef __Light_h__
#define __Light_h__

// #include "Player.h"
// #include "ObjectFactory.h"
#include "BaseObject.h"

class Player;
class ObjectFactory;

class Light: public BaseObject
{
private:
	float radius;
	float cone;
	int color;
	int soundID;

public:
	void Update(float fElapsedTime);

	void Render();
};

#endif
