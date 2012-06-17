#include <Windows.h>

#ifndef __Enemy_h__
#define __Enemy_h__

// #include "Player.h"
// #include "GamePlayState.h"
#include "BaseCharacter.h"
#include "IListener.h"
#include "Player.h"

class GamePlayState;

class Enemy: public BaseCharacter, public IListener
{
protected: 
	int m_nFrameX;
	int m_nFrameY;
	bool m_bCanMove;

protected: 
	Player* m_pTarget;

public: 
	Enemy();
	~Enemy();

	virtual void HandleEvent(Event* pEvent);

	virtual void Update(float fElapsedTime);

	virtual void SetTarget(Player* p) {m_pTarget = p;}

	virtual void Render();

	virtual bool CanMove() {return m_bCanMove;}
	virtual void SetCanMove(bool move) {m_bCanMove = move;}

	virtual void MoveTo(float x, float y, float speed);

	virtual bool CheckCollision(IObjects* pBase);
	virtual RECT GetRect();
};

#endif
