#ifndef __PickUp_h__
#define __PickUp_h__

#include "BaseObject.h"

class PickUp : public BaseObject
{
public:
	PickUp();
	virtual ~PickUp();

	virtual void Update(float fElapsedTime);

	virtual void Render();

	RECT GetRect();

	bool CheckCollision(BaseObject* pBase);
};

#endif
