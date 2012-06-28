#ifndef __WinMenuState_h__
#define __WinMenuState_h__
#include <Windows.h>

// #include "ViewManager.h"
// #include "AudioManager.h"
// #include "IDirectInputDevice.h"
// #include "XMLManager.h"
#include "IMenuState.h"
using namespace std;

class ViewManager;
class AudioManager;
class DirectInput;
class XMLManager;
// class IMenuState;
class WinMenuState;

class WinMenuState: public IMenuState
{
private: 
	ViewManager*	pVM;
	DirectInput*	pDI;
	AudioManager*	pAM;
	int				WMS_ID;
	int				tempWinID;
	int				curPos;
	float			fTime;

public: 

	void Enter();
	void Exit();
	bool Input();
	void Update(float aFElapsedTime);
	void Render();
	static WinMenuState* GetInstance();
};

#endif
