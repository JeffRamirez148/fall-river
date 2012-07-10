
#ifndef __IMenuState_h__
#define __IMenuState_h__

// #include "CGame.h"

class CGame;
class IMenuState;

class IMenuState
{
public: 

	virtual ~IMenuState() {/* Do Nothing */ }
	
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual bool Input() = 0;
	virtual void Update(float fElapsedTime) = 0;
	virtual void Render() = 0;
	virtual void ReEnter() = 0;
};

#endif
