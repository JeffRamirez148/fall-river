#ifndef __OptionsMenuState_h__
#define __OptionsMenuState_h__

#include "IMenuState.h"

class ViewManager;
class GamePlayState;
class XMLManager;
class DirectInput;
class OptionsMenuState;

class OptionsMenuState: public IMenuState
{
private:
	ViewManager* m_pVM;
	DirectInput* m_pDI;
	float fTime;
	int m_nCursPosY;
	float sfxVolume;
	float musicVolume;
	int resolution[2];

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

};

#endif
