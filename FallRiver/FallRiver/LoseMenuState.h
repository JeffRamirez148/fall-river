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
	ViewManager* view;
	DirectInput* input;
	AudioManager* audio;
	int y;
	float fTime;
public:
	void Enter();
	void Exit();
	bool Input();
	void Update(float aFElapsedTime);
	void Render();
	static WinMenuState* GetInstance();
};

