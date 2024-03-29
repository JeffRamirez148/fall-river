#include <Windows.h>

#ifndef __Enemy_h__
#define __Enemy_h__

// #include "Player.h"
// #include "GamePlayState.h"
#include "BaseCharacter.h"
#include "IListener.h"
#include "Player.h"

enum ENEMYSTATES{ ESTATE_IDLE = 0, ESTATE_CHASING, ESTATE_SHOOT, ESTATE_DISTRACTED, ESTATE_DEAD, GONE};

class Enemy: public BaseCharacter, public IListener
{

protected: 
	int m_nState;
	POINTFLOAT m_pfDestination;
	DWORD m_dwIdleWait;

	Player* m_pTarget;

public: 
	Enemy();
	~Enemy();
	virtual void Update(float fElapsedTime);

	virtual void SetTarget(Player* p) {m_pTarget = p;}

	virtual void Render();

	virtual void MoveTo(float x, float y, float speed);

	int GetState() {return m_nState;}

	virtual bool CheckCollision(IObjects* pBase);
	virtual RECT GetRect();
	virtual void HandleEvent(Event* aPEvent);
};

#endif
