

#include "CGame.h"
#include "DirectInput.h"
#include "MainMenuState.h"
#include "GamePlayState.h"

CGame* CGame::GetInstance()
{
	static CGame s_Instance;

	return &s_Instance;
}

CGame::CGame() 
{
	m_pDI = nullptr;

	m_nScreenWidth	= 0;
	m_nScreenHeight	= 0;
	m_bIsWindowed	= true;

	m_pPrevState	= nullptr;
	m_pCurrState	= nullptr;
}

CGame::~CGame()
{
}

bool CGame::Input() 
{
	// Just in case
	if(m_pCurrState == nullptr)
		return false;



	m_pDI->ReadDevices();

	return m_pCurrState->Input();
}

void CGame::Update() 
{
	DWORD time = GetTickCount();
	float ElapsedTime = (time - m_dwCurrTime) / 1000.0f;
	m_dwCurrTime = time;

	// Redirect to the current state
	m_pCurrState->Update(ElapsedTime);
}

void CGame::Render() 
{
	if(m_pPrevState == MainMenuState::GetInstance() || m_pPrevState == GamePlayState::GetInstance() )
		m_pPrevState->Render();

	m_pCurrState->Render();
}

void CGame::Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed)
{
	m_nScreenWidth	= nScreenWidth;
	m_nScreenHeight = nScreenHeight;
	m_bIsWindowed	= bIsWindowed;


	// Access the Wrappers
	m_pDI	= DirectInput::GetInstance();

	m_pDI->InitDirectInput( hWnd, hInstance, DI_KEYBOARD | DI_MOUSE | DI_JOYSTICKS, NULL );


	// Start the game in the gamplay state
	ChangeState( MainMenuState::GetInstance() );
}

bool CGame::Main()
{
	if( Input() == false )
		return false;

	if(m_pCurrState == nullptr)
		return false;

	Update();
	Render();

	return true;
}

void CGame::ShutDown() 
{
	// Exit the current state
	ChangeState( nullptr );

	// Shutdown the wrappers in REVERSE order!
	if( m_pDI != nullptr )
	{
		m_pDI->ShutdownDirectInput();
		m_pDI = nullptr;
	}
}

void CGame::ChangeState(IMenuState* pNewState) 
{
	// Exit the current state (if any)
	if( pNewState == nullptr)
	{
		m_pCurrState->Exit();
		if(m_pPrevState != nullptr)
			m_pPrevState->Exit();

		m_pCurrState = nullptr;
		m_pPrevState = nullptr;
	}

	if(m_pCurrState != nullptr )
		m_pPrevState = m_pCurrState;

	m_vStates.push_back(pNewState);

	// Assign the current state
	m_pCurrState = pNewState;

	// Enter the new state (if any)
	if( m_pCurrState != nullptr )
		m_pCurrState->Enter();
}

void CGame::RevertState( void )
{
	if( m_pCurrState != nullptr )
		m_pCurrState->Exit();

	m_vStates.pop_back();

	m_pCurrState = m_pPrevState;
}

IMenuState* CGame::GetState( void )				{return m_pCurrState;}
IMenuState* CGame::GetPreviousState( void )		{return m_pPrevState; }

void CGame::RemoveState( void )
{
	if( m_pCurrState != nullptr )
		m_pCurrState->Exit();

	m_vStates.pop_back();

	m_pPrevState = nullptr;

	if( m_vStates.size() > 0 )
	{
		m_pCurrState = m_vStates.back();
		if( m_vStates.size() == 1 )
			m_pPrevState = nullptr;
	}
	else
		m_pCurrState = nullptr;
}

