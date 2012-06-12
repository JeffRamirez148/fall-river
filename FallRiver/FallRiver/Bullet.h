#ifndef __Bullet_h__
#define __Bullet_h__

#include "BaseObject.h"
#include "IListener.h"

class Bullet: public BaseObject, public IListener
{
private: 
	int soundID;

	// Speed
	int m_nSpeedX;
	int m_nSpeedY;

public: 
	Bullet();
	virtual ~Bullet() { };

	void Update(float fElapsedTime);

	void Render();

	RECT GetRect();

	bool CheckCollision(BaseObject* pBase);

	void SetSpeed(int x, int y) {m_nSpeedX = x, m_nSpeedY = y;}

	void HandleEvent (Event* cEvent);
};

#endif
