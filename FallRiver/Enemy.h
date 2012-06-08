#include <Windows.h>
using namespace std;

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
	virtual void HandleEvent(Event* aPEvent);

	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual void MoveTo(int x, int y);

	virtual bool CheckCollision(BaseCharacter* pBase);
};

#endif
