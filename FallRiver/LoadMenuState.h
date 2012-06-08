#include <Windows.h>
using namespace std;

#ifndef __LoadMenuState_h__
#define __LoadMenuState_h__

// #include "ViewManager.h"
// #include "AudioManager.h"
// #include "XMLManager.h"
// #include "IDirectInputDevice.h"
#include "IMenuState.h"

class ViewManager;
class AudioManager;
class XMLManager;
class DirectInput;
// class IMenuState;
class LoadMenuState;

class LoadMenuState: public IMenuState
{
private: 
	ViewManager* view;
	DirectInput* input;
	float fTime;
	int y;
	AudioManager* audio;

public:

	LoadMenuState* GetInstance();

	void Enter();

	void Exit();

	void Input();

	void Update(float fElapsedTime);

	void Render();
};

#endif
