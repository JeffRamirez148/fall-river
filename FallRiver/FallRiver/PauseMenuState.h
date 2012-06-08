#include <Windows.h>
using namespace std;

#ifndef __PauseMenuState_h__
#define __PauseMenuState_h__

// #include "ViewManager.h"
// #include "AudioManager.h"
// #include "XMLManager.h"
// #include "IDirectInputDevice.h"
#include "IMenuState.h"

class ViewManager;
class AudioManager;
class XMLManager;
class DirectInput;

class PauseMenuState: public IMenuState
{
private:
	ViewManager* view;
	DirectInput* input;
	float fTime;
	int y;
	AudioManager* audio;

public:
	
	PauseMenuState* GetInstance();
	void Enter();
	void Exit();
	bool Input();
	void Update(float aFElapsedTime);
	void Render();
};

#endif
