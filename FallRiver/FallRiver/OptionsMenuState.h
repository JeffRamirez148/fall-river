#ifndef __OptionsMenuState_h__
#define __OptionsMenuState_h__

#include "IMenuState.h"

class ViewManager;
class GamePlayState;
class AudioManager;
class XMLManager;
class DirectInput;
class OptionsMenuState;

class OptionsMenuState: public IMenuState
{
private:
	ViewManager* m_pVM;
	DirectInput* m_pDI;
	AudioManager* m_pAM;
	float fTime;
	int m_nCursPosY;
	float sfxVolume;
	float musicVolume;
	bool m_bIsWindowed;
	int soundID;
	int musicID;

	int		m_nOptionID;
	int		m_nFontID;

	OptionsMenuState();
	~OptionsMenuState();
	OptionsMenuState(const OptionsMenuState&);
	OptionsMenuState& operator=(const OptionsMenuState&);

public: 

	static OptionsMenuState* GetInstance();
	void Enter();
	void Exit();
	bool Input();
	void Update(float aFElapsedTime);
	void Render();
	void ReEnter();
};

#endif
