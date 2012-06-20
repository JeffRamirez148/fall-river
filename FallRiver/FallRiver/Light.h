#ifndef __Light_h__
#define __Light_h__

#include "BaseObject.h"

class Player;
class ObjectFactory;

class Light: public BaseObject
{
private:
	float m_fRadius;
	float m_fCone;
	int m_nColor;
	int soundID;

	// Owner
	Player* m_pOwner;

public:
	Light();
	~Light();

	void Update(float fElapsedTime);

	float GetRadius() {return m_fRadius;}
	void SetRadius(float rad) {m_fRadius = rad;}

	void Render();

	RECT GetRect();

	bool CheckCollision(BaseObject* pBase);
};

#endif
