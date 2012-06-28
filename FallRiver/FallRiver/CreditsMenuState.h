#ifndef __CreditsMenuState_h__
#define __CreditsMenuState_h__

#include <Windows.h>
using namespace std;
#include "IMenuState.h"

class ViewManager;
class AudioManager;
class DirectInput;

class CreditsMenuState: public IMenuState
{
private: 
	ViewManager* m_pVM;
	DirectInput* m_pDI;
	float fTime;
	float fAttractTime;
	AudioManager* audio;
	int fontID;
	int creditsBGID;
	int logoID;

	CreditsMenuState();
	~CreditsMenuState();
	CreditsMenuState(const CreditsMenuState&);
	CreditsMenuState& operator=(const CreditsMenuState&); 

public: 
	static CreditsMenuState* GetInstance();

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();
};

#endif
