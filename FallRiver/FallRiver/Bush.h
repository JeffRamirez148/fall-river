#ifndef __Bush_h__
#define __Bush_h__

#include "BaseObject.h"


class Bush: public BaseObject
{
private:
	bool m_bIsInBush;
public:
	Bush();
	virtual ~Bush();

	virtual void Update(float fElapsedTime);

	virtual void Render();

	RECT GetRect();

	virtual bool CheckCollision(IObjects* pBase);
	void SetIsInBush( bool x ) { m_bIsInBush = x; }
	bool GetIsInBush( ) { return m_bIsInBush ;}
};

#endif
