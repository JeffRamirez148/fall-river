#ifndef __Closet_h__
#define __Closet_h__

#include "BaseObject.h"


class Closet: public BaseObject
{

public: 
	Closet();
	~Closet();

	virtual void Update(float fElapsedTime);

	virtual void Render();
	
	RECT GetRect();

	bool CheckCollision(BaseObject* pBase);
};

#endif
