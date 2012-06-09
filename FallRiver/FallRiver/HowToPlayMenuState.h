#include <Windows.h>
using namespace std;

#ifndef __HowToPlayMenuState_h__
#define __HowToPlayMenuState_h__

#include "IMenuState.h"

class ViewManager;
class AudioManager;
class DirectInput;
// class IMenuState;
class HowToPlayMenuState;

class HowToPlayMenuState: public IMenuState
{
private: 
	ViewManager* view;
	DirectInput* input;
	float fTime;

public: 
	static HowToPlayMenuState* GetInstance();

	void Enter(void);

	void Exit(void);

	bool Input(void);

	void Update(float fElapsedTime);

	void Render(void);
};

#endif
