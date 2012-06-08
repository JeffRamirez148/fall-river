#include <Windows.h>

#ifndef __Closet_h__
#define __Closet_h__

#include "BaseObject.h"

// class BaseObject;
class Closet;

class Closet: public BaseObject
{

public: 
	virtual void Update(float fElapsedTime);

	virtual void Render();
};

#endif
