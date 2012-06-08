#include <Windows.h>

#ifndef __CGame_h__
#define __CGame_h__

// #include "DirectInput.h"
// #include "IMenuState.h"
// #include "WinMain.h"

class DirectInput;
class IMenuState;
class WinMain;
class CGame;
class IGameState;

class CGame
{
private: 
	DirectInput* _m_pDI;
	int m_nScreenWidth;
	int m_nScreenHeight;
	bool m_bIsWindowed;
	DWORD m_dwCurrTime;
	IMenuState* curMenuState;

	CGame();
public: 
	bool Input();

	void Update();

	void Render();

	static CGame* GetInstance();

	void Initialize(HWND HWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed);

	bool Main();

	void ShutDown();

	void ChangeState(IGameState* pNewState);

	void SetWindowed(bool Is);

	bool IsWindowed();
};

#endif
