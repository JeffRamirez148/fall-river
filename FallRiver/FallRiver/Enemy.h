#include <Windows.h>

#ifndef __Enemy_h__
#define __Enemy_h__

// #include "Player.h"
// #include "GamePlayState.h"
#include "BaseCharacter.h"

class Player;
class GamePlayState;
// class BaseCharacter;
class Event;

class Enemy: public BaseCharacter
{
protected: 
	int m_nFrameX;
	int m_nFrameY;

private: 
	Player* m_pTarget;

public: 
	Enemy();
	~Enemy();

	virtual void HandleEvent(Event* pEvent);

	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual void MoveTo(int x, int y);

	virtual bool CheckCollision(BaseObject* pBase);
	virtual RECT GetRect();
};

#endif
