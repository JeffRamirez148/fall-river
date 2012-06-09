#include <Windows.h>
#include <vector>
using namespace std;

#ifndef __CGame_h__
#define __CGame_h__


class DirectInput;
class IMenuState;
class CGame;
class IMenuState;

class CGame
{
private:
	// Wrapper Members
	DirectInput* m_pDI;

	// Game States
	IMenuState*			m_pCurrState;
	IMenuState*			m_pPrevState;
	vector<IMenuState*> m_vStates;
	
	// Window Attributes
	int m_nScreenWidth;
	int m_nScreenHeight;
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

	// State Machine
	void ChangeState( IMenuState* pNewState );
	void RevertState( void );
	IMenuState* GetState( void );
	IMenuState* GetPreviousState( void );
	void RemoveState( void );

	void	SetWindowed(bool _is)			{ m_bIsWindowed = _is; }

	int		GetScreenWidth( void ) const	{	return m_nScreenWidth;	}
	int		GetScreenHeight( void ) const	{	return m_nScreenHeight;	}
	bool	IsWindowed( void ) const		{	return m_bIsWindowed;	}
};

#endif
