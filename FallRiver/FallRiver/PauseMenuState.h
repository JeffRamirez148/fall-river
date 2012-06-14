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
	ViewManager* m_pVM;
	DirectInput* m_pDI;
	float fTime;
	int m_nCursPosY;
	AudioManager* audio;

	PauseMenuState();
	~PauseMenuState();
	PauseMenuState(const PauseMenuState&);
	PauseMenuState& operator=(const PauseMenuState&);

public:
	
	static PauseMenuState* GetInstance();
	void Enter();
	void Exit();
	bool Input();
	void Update(float aFElapsedTime);
	void Render();
};

#endif
