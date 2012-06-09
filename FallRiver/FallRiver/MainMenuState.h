#include <Windows.h>
using namespace std;

#ifndef __MainMenuState_h__
#define __MainMenuState_h__

#include "IMenuState.h"

class ViewManager;
class AudioManager;
class DirectInput;
class XMLManager;

class MainMenuState: public IMenuState
{
private: 
	ViewManager* view;
	DirectInput* m_pDI;
	AudioManager* audio;
	int y;
	float sfxVolume;
	float musicVolume;
	float fTime;

public: 

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();

	static MainMenuState* GetInstance();
};

#endif
