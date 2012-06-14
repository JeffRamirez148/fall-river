
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
	ViewManager* m_pVM;
	DirectInput* m_pDI;
	AudioManager* audio;
	int		m_nCursPosY;
	float sfxVolume;
	float musicVolume;
	float fTime;

	MainMenuState();
	~MainMenuState();
	MainMenuState(const MainMenuState&);
	MainMenuState& operator=(const MainMenuState&);

public: 

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();

	static MainMenuState* GetInstance();
};

#endif
