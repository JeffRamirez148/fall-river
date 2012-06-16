#ifndef __Boss2_h__
#define __Boss2_h__

#include "Enemy.h"
#include "IListener.h"

class Boss2: public Enemy, public IListener
{
public: 
	virtual void Update(float aTime);

	virtual void Render();

	void HandleEvent(Event* Event);

	virtual bool CheckCollision(IObjects* pBase);
};

#endif
