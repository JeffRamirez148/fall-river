#include <Windows.h>
using namespace std;

#ifndef __IMenuState_h__
#define __IMenuState_h__

// #include "CGame.h"

class CGame;
class IMenuState;

class IMenuState
{
	public: 
		void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();
};

#endif
