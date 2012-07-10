
#ifndef __MainMenuState_h__
#define __MainMenuState_h__

#include "IMenuState.h"
#include <Windows.h>

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
	int soundID;
	int musicID;

	// For Flashing effect
	DWORD	m_dwFlash1;
	DWORD	m_dwFlash2;
	DWORD	m_dwFlash3;

	DWORD	m_dwReset;

	// Game Logo
	int		m_nFallRiverID;
	
	// For the actual menu
	int		m_nMenuPlayID;
	int		m_nMenuHowToID;
	int		m_nMenuOptionsID;
	int		m_nMenuHighScoresID;
	int		m_nMenuCreditsID;
	int		m_nMenuExitID;

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
	void ReEnter();
};

#endif
