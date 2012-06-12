#ifndef __Bush_h__
#define __Bush_h__

#include "BaseObject.h"


class Bush: public BaseObject
{
public:
	Bush();
	virtual ~Bush() { }

	virtual void Update(float fElapsedTime);

	virtual void Render();

	RECT GetRect();

	bool CheckCollision(BaseObject* pBase);
};

#endif
