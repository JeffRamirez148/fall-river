#include <Windows.h>
using namespace std;

#ifndef __OptionsMenuState_h__
#define __OptionsMenuState_h__

// #include "ViewManager.h"
// #include "GamePlayState.h"
// #include "XMLManager.h"
#include "IMenuState.h"

class ViewManager;
class GamePlayState;
class XMLManager;
class DirectInput;
class OptionsMenuState;

class OptionsMenuState: public IMenuState
{
private:
	ViewManager* view;
	DirectInput* input;
	float fTime;
	int y;
	float sfxVolume;
	float musicVolume;
	int resolution[2];

public: 

	XMLManager* _xMLManager;
	static OptionsMenuState* GetInstance();
	void Enter();
	void Exit();
	bool Input();
	void Update(float aFElapsedTime);
	void Render();

};

#endif
