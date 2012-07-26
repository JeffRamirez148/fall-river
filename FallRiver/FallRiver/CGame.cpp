

#include "CGame.h"
#include "DirectInput.h"
#include "ViewManager.h"
#include "MainMenuState.h"
#include "AudioManager.h"
#include "GamePlayState.h"
#include "Particle_Manager.h"
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

	scoreCatch		= 120;
	stickTimer = 0;
	owlTimer = 0;
	AudioManager* m_pAM = AudioManager::GetInstance();
	pianoID = m_pAM->registerMusic("resource/Sounds/piano.wav");
	backGroundID = m_pAM->registerMusic("resource/Sounds/background.wav");
	musicID= m_pAM->registerMusic("resource/Sounds/rainroof.wav");
	stick = m_pAM->registerMusic("resource/Sounds/stickCrack.mp3");
	owl = m_pAM->registerMusic("resource/Sounds/owl.wav");
	loseID = m_pAM->registerMusic("resource/Sounds/loseSound.wav");

	

	FMOD_VECTOR sound1 = { 0, 0, 0 };

	m_pAM->setMusicPos(backGroundID, sound1);
	m_pAM->setMusicVel(backGroundID, sound1);
	m_pAM->setMusicLooping(backGroundID, true);
	m_pAM->playMusic(backGroundID);
	m_pAM->setMusicPos(pianoID, sound1);
	m_pAM->setMusicVel(pianoID, sound1);
	m_pAM->setMusicLooping(pianoID, true);
	m_pAM->playMusic(pianoID);
	m_pAM->setMusicPos(musicID, sound1);
	m_pAM->setMusicVel(musicID, sound1);
	m_pAM->setMusicLooping(musicID, true);
	m_pAM->playMusic(musicID);
	m_pAM->setMusicPos(stick, sound1);
	m_pAM->setMusicVel(stick, sound1);
	m_pAM->setMusicLooping(stick, false);
	m_pAM->setMusicPos(owl, sound1);
	m_pAM->setMusicVel(owl, sound1);
	m_pAM->setMusicLooping(owl, false);
	m_pAM->setMusicPos(loseID, sound1);
	m_pAM->setMusicVel(loseID, sound1);
	m_pAM->setMusicLooping(loseID, false);
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
	stickTimer += ElapsedTime;
	owlTimer += ElapsedTime;
	AudioManager* m_pAM = AudioManager::GetInstance();
	if(stickTimer > 9 && rand() % 300 == 0)
	{
		m_pAM->GetMusicChannel(stick)->stop();
		m_pAM->playMusic(stick);
		stickTimer = 0;
	}
	if(owlTimer > 9 && rand() % 300 == 0)
	{
		m_pAM->GetMusicChannel(owl)->stop();
		m_pAM->playMusic(owl);
		owlTimer = 0;
	}
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
	//m_pVM->Present();
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

	if( m_pVM != nullptr )
	{
		m_pVM->ShutdownDirect3D();
		m_pVM = nullptr;
	}
}

void CGame::ChangeState(IMenuState* pNewState) 
{

	for(unsigned int i = 0; i < AudioManager::GetInstance()->GetMusic()->size(); ++i)
		if( (int)i != pianoID && (int)i != backGroundID && (int)i != musicID && (int)i != owl && (int)i != stick && (int)i != loseID )
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
		if( (int)i != pianoID && (int)i != backGroundID && (int)i != musicID && (int)i != owl && (int)i != stick && (int)i != loseID )
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
		if( (int)i != pianoID && (int)i != backGroundID && (int)i != musicID && (int)i != owl && (int)i != stick && (int)i != loseID )
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
