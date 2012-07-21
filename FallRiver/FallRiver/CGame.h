#include <Windows.h>
#include <vector>
#include "AudioManager.h"
using namespace std;

#ifndef __CGame_h__
#define __CGame_h__


class DirectInput;
class IMenuState;
class CGame;
class IMenuState;
class ViewManager;

class CGame
{
private:
	// Wrapper Members
	DirectInput* m_pDI;
	ViewManager* m_pVM;

	// Game States
	IMenuState*			m_pCurrState;
	IMenuState*			m_pPrevState;
	
	// Sounds
	int pianoID;
	int backGroundID;
	int musicID;
	int stick;
	int owl;
	int loseID;


	float stickTimer;
	float owlTimer;

	// Window Attributes
	int m_nScreenWidth;
	int m_nScreenHeight;
	bool m_bPrevWindowed;
	bool m_bIsWindowed;
	DWORD m_dwCurrTime;

	CGame(void);
	~CGame(void);
	CGame(const CGame& ref);
	CGame& operator=(const CGame& ref);

	// Running
	bool Input();
	void Update();
	void Render();

public: 

	static CGame* GetInstance();

	void Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed);

	bool Main();

	void ShutDown();

	////////////////////////////
	// State Machine		  //
	////////////////////////////
	
	// Add a state unto the stack of states
	void ChangeState( IMenuState* pNewState );

	// Get the Current State
	IMenuState* GetState( void );

	// Get the Previous State if there is one
	IMenuState* GetPreviousState( void );

	// Pop the current state off the top
	void RemoveState( void );
	void RemoveState(int state);
	vector<IMenuState*> m_vStates;
	///////////////////////////////

	void	SetWindowed(bool _is)			{ m_bIsWindowed = _is; }

	int		GetScreenWidth( void ) const	{	return m_nScreenWidth;	}
	int		GetScreenHeight( void ) const	{	return m_nScreenHeight;	}
	bool	IsWindowed( void ) const		{	return m_bIsWindowed;	}
	void PlayLoseSound(void)
	{	
		if(!AudioManager::GetInstance()->isMusicPlaying(loseID))
			AudioManager::GetInstance()->playMusic(loseID);
	}
};

#endif
