

#include "CGame.h"
#include "DirectInput.h"
#include "ViewManager.h"
#include "MainMenuState.h"
#include "AudioManager.h"
#include "GamePlayState.h"
#include "sound.h"

CGame* CGame::GetInstance()
{
	static CGame s_Instance;

	return &s_Instance;
}

CGame::CGame() 
{
	m_pDI = nullptr;
	m_pVM = nullptr;

	m_nScreenWidth	= 800;
	m_nScreenHeight	= 600;
	m_bIsWindowed	= true;

	m_pPrevState	= nullptr;
	m_pCurrState	= nullptr;
}

CGame::~CGame()
{
}

bool CGame::Input() 
{
	m_bPrevWindowed = m_bIsWindowed;
	
	// Refresh Devices
	m_pDI->ReadDevices();

	if( ( m_pDI->KeyDown(DIK_LALT) || m_pDI->KeyDown(DIK_RALT) ) && m_pDI->KeyDown(DIK_F4) )
		return false;

	// Just in case
	if(m_vStates.size() > 0)
		return m_vStates.back()->Input();
	else
		return false;


	
	//return m_pCurrState->Input();
}

void CGame::Update() 
{
	DWORD time = GetTickCount();
	float ElapsedTime = (time - m_dwCurrTime) / 1000.0f;
	m_dwCurrTime = time;

	AudioManager::GetInstance()->Update(ElapsedTime);

	FMOD_VECTOR vec;
	vec.x = float(CGame::GetInstance()->GetScreenWidth()*0.45);
	vec.y = float(CGame::GetInstance()->GetScreenHeight()*0.4);
	vec.z = 0;

	AudioManager::GetInstance()->SetListenerPos(vec);

	// Redirect to the current state
	//m_pCurrState->Update(ElapsedTime);

	if(m_vStates.size() > 0)
		m_vStates.back()->Update(ElapsedTime);
}

void CGame::Render() 
{
	if(m_bIsWindowed != m_bPrevWindowed)
		m_pVM->ChangeDisplayParam(m_nScreenWidth, m_nScreenHeight, m_bIsWindowed);

	// Clear the background
	m_pVM->Clear(0, 0, 0);

	// Start D3D rendering
	m_pVM->DeviceBegin();
	m_pVM->SpriteBegin();


	// Fixing stuff
	m_vStates.back()->Render();
	// Redirect to the current state
	/*if( m_pPrevState == GamePlayState::GetInstance() )
		m_pPrevState->Render();

	m_pCurrState->Render();*/


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
	m_vStates.push_back( MainMenuState::GetInstance() );
	m_vStates.back()->Enter();
}

bool CGame::Main()
{
	if( this->Input() == false )
		return false;

	if(m_vStates.back() == nullptr)
		return false;

	Render();
	Update();

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

	for(unsigned int i = 0; i < AudioManager::GetInstance()->GetMusic()->size(); ++i)
		AudioManager::GetInstance()->GetMusicChannel(i)->stop();
	for(unsigned int i = 0; i < AudioManager::GetInstance()->GetSounds()->size(); ++i)
		AudioManager::GetInstance()->GetSoundChannel(i)->stop();
	
	m_pVM->SetAmbientLight( 1.0f, 1.0f, 1.0f);


	// Fixing stuff
	if(pNewState != nullptr)
	{
		m_vStates.push_back(pNewState);
		pNewState->Enter();
	}
	// Exit the current state (if any)
	/*if( pNewState == nullptr)
	{
		m_pCurrState->Exit();
		if(m_pPrevState != nullptr)
			m_pPrevState->Exit();

		m_pCurrState = nullptr;
		m_pPrevState = nullptr;
	}*/

	// Set the Previous State to what Current State is now
	/*if(m_pCurrState != nullptr )
		m_pPrevState = m_pCurrState;*/
	
	

	//// Add the new State
	//m_vStates.push_back(pNewState);

	//// Assign the current state
	//m_pCurrState = pNewState;

	//// Enter the new state (if any)
	//if( m_pCurrState != nullptr )
	//	m_pCurrState->Enter();
}

///////////////////////////
// Get the current State //
IMenuState* CGame::GetState( void )				{return  m_vStates.back();}

//////////////////////////////
// Get the previous State	//
IMenuState* CGame::GetPreviousState( void )		{return m_pPrevState; }

void CGame::RemoveState( void )
{
	for(unsigned int i = 0; i < AudioManager::GetInstance()->GetMusic()->size(); ++i)
		AudioManager::GetInstance()->GetMusicChannel(i)->stop();
	for(unsigned int i = 0; i < AudioManager::GetInstance()->GetSounds()->size(); ++i)
		AudioManager::GetInstance()->GetSoundChannel(i)->stop();

	m_pVM->SetAmbientLight( 1.0f, 1.0f, 1.0f);


	// Fixing stuff
	if( m_vStates.back() != nullptr )
	{
		m_vStates.back()->Exit();
		m_vStates.pop_back();		
	}
	m_vStates.back()->ReEnter();
	//// Checking. Just in case
	//if( m_pCurrState != nullptr )
	//	m_pCurrState->Exit();

	//// Take off the top state
	//m_vStates.pop_back();

	//// Null the previous state
	//m_pPrevState = nullptr;

	//for(int i = m_vStates.size()-2; i > 0; i++ )
	//{
	//	m_pPrevState = m_vStates[i];
	//	break;
	//}

	//if( m_vStates.size() > 0 )
	//{
	//	// Make the Current state equal to the back of the states
	//	// Would set to previous state but not previous could not exist.
	//	m_pCurrState = m_vStates.back();
	//}
	//else
	//	m_pCurrState = nullptr;
}
void CGame::RemoveState(int state)
{
	
	for(unsigned int i = 0; i < AudioManager::GetInstance()->GetMusic()->size(); ++i)
		AudioManager::GetInstance()->GetMusicChannel(i)->stop();
	for(unsigned int i = 0; i < AudioManager::GetInstance()->GetSounds()->size(); ++i)
		AudioManager::GetInstance()->GetSoundChannel(i)->stop();
		
	m_pVM->SetAmbientLight( 1.0f, 1.0f, 1.0f);

	for(int i = 0; i < state; i++)
	{
		m_vStates.back()->Exit();
		m_vStates.pop_back();
	}
	m_vStates.back()->ReEnter();
}
