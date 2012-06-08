#include <Windows.h>
using namespace std;

#ifndef __Bush_h__
#define __Bush_h__

#include "BaseObject.h"

// class BaseObject;
class Bush;

class Bush: public BaseObject
{

	public: 
	virtual void Update(float fElapsedTime);

	virtual void Render();
};

#endif
