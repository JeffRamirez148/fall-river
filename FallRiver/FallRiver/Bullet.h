#ifndef __Bullet_h__
#define __Bullet_h__

#include "BaseObject.h"
#include "IListener.h"
#include "Weapon.h"

class Bullet: public BaseObject, public IListener
{
private: 
	int soundID;
	Weapon* m_pOwner;
	float m_fSpeedX;
	float m_fSpeedY;

	// For the Range
	float m_fStartPosX;
	float m_fStartPosY;

	// Particles
	int smokeA;
public: 
	Bullet();
	virtual ~Bullet();

	void Update(float fElapsedTime);

	void Render();

	RECT GetRect();

	void SetStartPos(float x, float y) {m_fStartPosX = x; m_fStartPosY = y;}

	// Get and Set Speed for X
	float GetSpeedX() {return m_fSpeedX;}
	void SetSpeedX(float fSpeed) {m_fSpeedX = fSpeed;}

	// Get and Set Speed for Y
	float GetSpeedY() {return m_fSpeedY;}
	void SetSpeedY(float fSpeed) {m_fSpeedY = fSpeed;}

	// Get and Set Owner of this bullet
	void SetOwner(Weapon* pOwner) {m_pOwner = pOwner;}
	Weapon* GetOwner() {return m_pOwner;}


	bool CheckCollision(IObjects* pBase);

	void HandleEvent (Event* cEvent);
	int GetSmokeID() { return smokeA; }
	void SetSmokeID(int id) { smokeA = id; }

};

#endif
