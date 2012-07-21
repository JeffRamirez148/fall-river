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
	int m_nCursPosY;
	AudioManager* audio;

	// For Menu Part
	int m_nPauseID;
	int soundID;
	int soundID2;
//	int musicID;
//	int musicID2;

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
	void ReEnter();

};

#endif
