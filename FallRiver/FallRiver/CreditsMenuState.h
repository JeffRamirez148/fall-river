#include <Windows.h>
using namespace std;

#ifndef __CreditsMenuState_h__
#define __CreditsMenuState_h__

// #include "ViewManager.h"
// #include "AudioManager.h"
// #include "IDirectInputDevice.h"
#include "IMenuState.h"

class ViewManager;
class AudioManager;
class DirectInput;
// class IMenuState;
class CreditsMenuState;

class CreditsMenuState: public IMenuState
{
private: 
	ViewManager* view;
	DirectInput* input;
	float fTime;
	float fAttractTime;
	AudioManager* audio;
public: 
	CreditsMenuState* GetInstance();

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();
};

#endif
