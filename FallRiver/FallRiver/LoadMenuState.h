#ifndef __LoadMenuState_h__
#define __LoadMenuState_h__

#include "IMenuState.h"

class ViewManager;
class AudioManager;
class XMLManager;
class DirectInput;

class LoadMenuState: public IMenuState
{
private: 
	ViewManager* m_pVM;
	DirectInput* m_pDI;
	int m_nCursPosY;
	int m_nCursPosX;
	int m_nFontID;
	AudioManager* audio;
	bool m_bSure;
	bool m_bCheck;
	bool m_bIsLoading;

	int m_nNewID;
	int m_nLoadID;
	int m_nExitID;

	LoadMenuState();
	~LoadMenuState();
	LoadMenuState(const LoadMenuState&);
	LoadMenuState& operator= (const LoadMenuState&);

public:

	static LoadMenuState* GetInstance();

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();
	void ReEnter();
};

#endif
