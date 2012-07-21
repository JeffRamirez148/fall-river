#pragma once
#include "imenustate.h"

class ViewManager;
class AudioManager;
class DirectInput;
class XMLManager;
class WinMenuState;

class LoseMenuState :
	public IMenuState
{

private:
	ViewManager*	pVM;
	DirectInput*	pDI;
	AudioManager*	audio;
	int				LMS_ID;
	int				tempLoseID;
	int				curPos;
	float			fTime;
	int soundID;
	int soundID2;
	//int musicID;
	//int musicID2;

public:
	void Enter();
	void Exit();
	bool Input();
	void Update(float aFElapsedTime);
	void Render();
	static LoseMenuState* GetInstance();
	void ReEnter();
};

