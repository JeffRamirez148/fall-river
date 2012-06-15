#ifndef __Bullet_h__
#define __Bullet_h__

#include "BaseObject.h"
#include "IListener.h"

class Bullet: public BaseObject, public IListener
{
private: 
	int soundID;

public: 
	Bullet();
	virtual ~Bullet();

	void Update(float fElapsedTime);

	void Render();

	RECT GetRect();

	bool CheckCollision(BaseObject* pBase);

	void HandleEvent (Event* cEvent);
};

#endif
