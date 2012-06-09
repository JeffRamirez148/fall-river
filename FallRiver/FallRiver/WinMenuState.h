#include <Windows.h>
using namespace std;

#ifndef __WinMenuState_h__
#define __WinMenuState_h__

// #include "ViewManager.h"
// #include "AudioManager.h"
// #include "IDirectInputDevice.h"
// #include "XMLManager.h"
#include "IMenuState.h"

class ViewManager;
class AudioManager;
class DirectInput;
class XMLManager;
// class IMenuState;
class WinMenuState;

class WinMenuState: public IMenuState
{
private: 
	ViewManager* view;
	DirectInput* input;
	AudioManager* audio;
	int y;
	float fTime;

public: 

	void Enter();
	void Exit();
	bool Input();
	void Update(float aFElapsedTime);
	void Render();
	static WinMenuState* GetInstance();
};

#endif
