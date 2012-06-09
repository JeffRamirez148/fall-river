#include <Windows.h>
using namespace std;

#ifndef __DefeatMenuState_h__
#define __DefeatMenuState_h__

// #include "AudioManager.h"
// #include "ViewManager.h"
// #include "IDirectInputDevice.h"
// #include "XMLManager.h"
#include "IMenuState.h"

class AudioManager;
class ViewManager;
class DirectInput;
class XMLManager;

class DefeatMenuState: public IMenuState
{
private: 
	ViewManager* view;
	DirectInput* input;
	float fTime;
	int y;
	AudioManager* audio;
public:
	static DefeatMenuState* GetInstance();

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();
};

#endif
