

#include "CGame.h"
#include "DirectInput.h"
#include "ViewManager.h"
#include "MainMenuState.h"
#include "GamePlayState.h"
#include "AudioManager.h"

CGame* CGame::GetInstance()
{
	static CGame s_Instance;

	return &s_Instance;
}

CGame::CGame() 
{
	m_pDI = nullptr;
	m_pVM = nullptr;

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


	// Refresh Devices
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
	AudioManager::GetInstance()->Update(ElapsedTime);
}

void CGame::Render() 
{
	// Clear the background
	m_pVM->Clear(0, 0, 0);

	// Start D3D rendering
	m_pVM->DeviceBegin();
	m_pVM->SpriteBegin();



	// Redirect to the current state
	if( m_pPrevState == GamePlayState::GetInstance() )
		m_pPrevState->Render();

	m_pCurrState->Render();


	// End the D3D rendering (draw to buffer)
	m_pVM->SpriteEnd();
	m_pVM->DeviceEnd();

	// Render the buffer to the screen
	m_pVM->Present();
}

void CGame::Initialize(HWND hWnd, HINSTANCE hInstance, int nScreenWidth, int nScreenHeight, bool bIsWindowed)
{
	m_nScreenWidth	= nScreenWidth;
	m_nScreenHeight = nScreenHeight;
	m_bIsWindowed	= bIsWindowed;


	// Access the Wrappers
	m_pDI	= DirectInput::GetInstance();
	m_pVM	= ViewManager::GetInstance();

	m_pDI->InitDirectInput( hWnd, hInstance, DI_KEYBOARD | DI_MOUSE | DI_JOYSTICKS, NULL );
	m_pVM->InitViewManager( hWnd, nScreenWidth, nScreenHeight, bIsWindowed, false );


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

	// Set the Previous State to what Current State is now
	if(m_pCurrState != nullptr )
		m_pPrevState = m_pCurrState;
	
	// Add the new State
	m_vStates.push_back(pNewState);

	// Assign the current state
	m_pCurrState = pNewState;

	// Enter the new state (if any)
	if( m_pCurrState != nullptr )
		m_pCurrState->Enter();
}

///////////////////////////
// Get the current State //
IMenuState* CGame::GetState( void )				{return m_pCurrState;}

//////////////////////////////
// Get the previous State	//
IMenuState* CGame::GetPreviousState( void )		{return m_pPrevState; }

void CGame::RemoveState( void )
{
	// Checking. Just in case
	if( m_pCurrState != nullptr )
		m_pCurrState->Exit();

	// Take off the top state
	m_vStates.pop_back();

	// Null the previous state
	m_pPrevState = nullptr;

	if( m_vStates.size() > 0 )
	{
		// Make the Current state equal to the back of the states
		// Would set to previous state but not previous could not exist.
		m_pCurrState = m_vStates.back();
	}
	else
		m_pCurrState = nullptr;
}

