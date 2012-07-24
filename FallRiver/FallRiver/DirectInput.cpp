#include <Windows.h>
#include <vector>
using namespace std;

#include "DirectInput.h"
#include "CGame.h"
#include "GamePlayState.h"
#include "HighScoresMenuState.h"

#include <tchar.h>

DirectInput DirectInput::m_Instance;

DirectInput::DirectInput(void)
{
	m_lpDIObject	= NULL;
	m_pKeyboard		= NULL;
	m_pMouse		= NULL;

}

DirectInput::~DirectInput(void)
{
	ShutdownDirectInput();
}

DirectInput* DirectInput::GetInstance(void)
{
	return &m_Instance;
}

bool DirectInput::InitDirectInput(HWND hWnd, HINSTANCE hInstance, unsigned int unInitDevices, unsigned int unExclusiveDevices)
{
	//	Create the DirectInput Object
	if (FAILED( DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_lpDIObject, NULL) ))
		return false;

	//	Initialize the keyboard if the keyboard flag is on
	if (unInitDevices & DI_KEYBOARD)
	{
		//	Initialize the keyboard
		if (!InitKeyboard(hWnd, (unExclusiveDevices & DI_KEYBOARD) ? true : false ))
			return false;
	}

	//	Initialize the mouse if the mouse flag is on
	if (unInitDevices & DI_MOUSE)
	{
		//	Initialize the mouse
		if (!InitMouse(hWnd, (unExclusiveDevices & DI_MOUSE) ? true : false ))
			return false;
	}

	//	Initialize joysticks if the joystick flag is on
	if (unInitDevices & DI_JOYSTICKS)
	{
		//	Initialize joysticks
		if (!InitJoysticks(hWnd, (unExclusiveDevices & DI_JOYSTICKS) ? true : false ))
			return false;
	}

	return true;
}

void DirectInput::ShutdownDirectInput(void)
{
	UnacquireAll();

	if (m_pKeyboard)
	{
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	if (m_pMouse)
	{
		delete m_pMouse;
		m_pMouse = NULL;
	}

	if (m_vpJoysticks.size() > 0)
	{
		for (unsigned int i=0; i < m_vpJoysticks.size(); i++)
		{
			delete m_vpJoysticks[i];
			m_vpJoysticks[i] = NULL;
		}

		m_vpJoysticks.clear();
	}
}

void DirectInput::ReadDevices(void)
{
	if (m_pKeyboard)
	{
		m_pKeyboard->ReadDevice();
		m_pKeyboard->ReadBufferedDevice();
	}

	if (m_pMouse)
	{
		m_pMouse->ReadDevice();
		m_pMouse->ReadBufferedDevice();
	}

	if (m_vpJoysticks.size() > 0)
	{
		for (unsigned int i=0; i < m_vpJoysticks.size(); i++)
		{
			if (m_vpJoysticks[i])
			{
				m_vpJoysticks[i]->ReadDevice();
				m_vpJoysticks[i]->ReadBufferedDevice();
			}
		}
	}
}

void DirectInput::ClearInput(void)
{
	if (m_pKeyboard)
	{
		m_pKeyboard->ClearKeys();
	}

	if (m_pMouse)
	{
		m_pMouse->ClearMouseButtons();
	}

	if (m_vpJoysticks.size() > 0)
	{
		for (unsigned int i=0; i < m_vpJoysticks.size(); i++)
		{
			if (m_vpJoysticks[i])
			{
				m_vpJoysticks[i]->ClearJoystickButtons();
			}
		}
	}
}

void DirectInput::AcquireAll(void)
{
	if (m_pKeyboard)
		m_pKeyboard->Acquire();

	if (m_pMouse)
		m_pMouse->Acquire();

	if (m_vpJoysticks.size() > 0)
	{
		for (unsigned int i=0; i < m_vpJoysticks.size(); i++)
		{
			if (m_vpJoysticks[i]) 
				m_vpJoysticks[i]->Acquire();
		}
	}
}

void DirectInput::UnacquireAll(void)
{
	if (m_pKeyboard)
		m_pKeyboard->Unacquire();

	if (m_pMouse)
		m_pMouse->Unacquire();

	if (m_vpJoysticks.size() > 0)
	{
		for (unsigned int i=0; i < m_vpJoysticks.size(); i++)
		{
			if (m_vpJoysticks[i]) 
				m_vpJoysticks[i]->Unacquire();
		}
	}
}

bool DirectInput::InitKeyboard(HWND hWnd, bool bIsExclusive)
{
	//	Make sure we dont do this more than once
	if (m_pKeyboard)
		return false;

	m_pKeyboard = new DIKeyboard(m_lpDIObject, hWnd, bIsExclusive);

	if (m_pKeyboard == NULL)
		return false;

	return true;
}

////////////////////////////////////////////
// When user is holding a Key Down		  //
// Returns true if Key is Being Held Down //
////////////////////////////////////////////
bool DirectInput::KeyDown(unsigned char ucDIKey)			{ return (m_pKeyboard && m_pKeyboard->KeyDown(ucDIKey)); }


//////////////////////////////////////////////////
// When user has pressed a Key					//
// Returns true if key was pressed this frame	//
//////////////////////////////////////////////////
bool DirectInput::KeyPressed(unsigned char ucDIKey)		{ return (m_pKeyboard && m_pKeyboard->KeyPressed(ucDIKey)); }


///////////////////////////////////////////////////
// If the key sent in isn't being pressed		 //
// Returns true if key isnt down				 //
///////////////////////////////////////////////////
bool DirectInput::KeyUp(unsigned char ucDIKey)			{ return (m_pKeyboard && m_pKeyboard->KeyUp(ucDIKey)); }

/////////////////////////////////////////////////////
// When the user releases a Key					   //
// Returns true if the key was released this frame //
/////////////////////////////////////////////////////
bool DirectInput::KeyReleased(unsigned char ucDIKey)		{ return (m_pKeyboard && m_pKeyboard->KeyReleased(ucDIKey)); }

/////////////////////////////////////////////////////
// Ascii value of the key being pressed            //
// returns 0 if no key was pressed this frame      //
/////////////////////////////////////////////////////
char DirectInput::CheckKeys(void)					{  return (m_pKeyboard) ? m_pKeyboard->CheckKeys() : 0; }

//////////////////////////////////////////////////
// To get the DIK code of the key pressed		//
// Returns 0 if no key was pressed this frame   //
//////////////////////////////////////////////////
unsigned char DirectInput::GetDIKCode(void)			{ return (m_pKeyboard) ? m_pKeyboard->GetDIKCode() : 0; }

////////////////
// MOUSE      //
////////////////

///////////////////////////////////////////
// Initialize the Mouse					 //
///////////////////////////////////////////
bool DirectInput::InitMouse(HWND hWnd, bool bIsExclusive)
{
	if (m_pMouse)
	{
			return false;
	}

	m_pMouse = new DIMouse(m_lpDIObject, hWnd, bIsExclusive);

	if (m_pMouse == NULL)
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////
// Checks whether the mouse button is currently being held down //
// Returns true if the button is down							//
//////////////////////////////////////////////////////////////////
bool DirectInput::MouseButtonDown(unsigned char ucButton)			{ return (m_pMouse && m_pMouse->ButtonDown(ucButton)); }

///////////////////////////////////////////////////////
// Checks if the Mouse button was pressed this frame //
// Returns true if it was pressed					 //
///////////////////////////////////////////////////////
bool DirectInput::MouseButtonPressed(unsigned char ucButton)		{ return (m_pMouse && m_pMouse->ButtonPressed(ucButton)); }

///////////////////////////////////////////////////////
// Checks if the Mouse button is not being pressed   //
// Returns true if the mouse button is up            //
///////////////////////////////////////////////////////
bool DirectInput::MouseButtonUp(unsigned char ucButton)			{ return (m_pMouse && m_pMouse->ButtonUp(ucButton)); }

////////////////////////////////////////////////////////
// Checks if the mouse button was released this frame //
// Returns true if the button was pressed this frame  //
////////////////////////////////////////////////////////
bool DirectInput::MouseButtonReleased(unsigned char ucButton)		{ return (m_pMouse && m_pMouse->ButtonReleased(ucButton)); }

////////////////////////////////////////////////////////
// Checks which mouse button was pressed			  //
// Returns -1 if nothing was pressed this frame		  //
////////////////////////////////////////////////////////
int DirectInput::MouseCheckBufferedButtons(void)			{ return (m_pMouse) ? m_pMouse->CheckBufferedButtons() : -1; }

long DirectInput::MouseMovementX(void)						{ return (m_pMouse) ? m_pMouse->MovementX() : 0; }

long DirectInput::MouseMovementY(void)						{ return (m_pMouse) ? m_pMouse->MovementY() : 0; }

long DirectInput::MouseWheelMovement(void)					{ return (m_pMouse) ? m_pMouse->WheelMovement() : 0; }

int DirectInput::MouseGetNumButtons(void)					{ return (m_pMouse) ? m_pMouse->GetNumButtons() : 0; }

int DirectInput::MouseGetPosX(void)							{ return (m_pMouse) ? m_pMouse->GetPosX() : 0; }

int DirectInput::MouseGetPosY(void)					{ return (m_pMouse) ? m_pMouse->GetPosY() : 0; }

void DirectInput::MouseSetPosX(int nPosX)			{ if (m_pMouse) m_pMouse->SetPosX( nPosX ); }

void DirectInput::MouseSetPosY(int nPosY)			{ if (m_pMouse) m_pMouse->SetPosY( nPosY ); }

bool DirectInput::InitJoysticks(HWND hWnd, bool bIsExclusive)
{
	//	Dont do this more than once.
	if (m_vpJoysticks.size() > 0)
	{
			return false;
	}

	//	Remember the info in a struct to pass along
	tJoystickSetupInfo joySetupInfo = { hWnd, bIsExclusive };

	//	Enumerate all joysticks attached to the system.
	if(FAILED( m_lpDIObject->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, (LPVOID)&joySetupInfo, DIEDFL_ATTACHEDONLY) ))
		return false;

	//	If we don't have any joysticks, we couldn't initialize them
	if (m_vpJoysticks.size() == 0)
		return false;

	return true;
}

BOOL CALLBACK DirectInput::EnumJoysticksCallback(const DIDEVICEINSTANCE* lpdidi, VOID* pVoid)
{
	DirectInput*	pDI = DirectInput::GetInstance();

	//	Retrieve the setup info
	tJoystickSetupInfo joySetupInfo = (*(tJoystickSetupInfo*)pVoid);

	//	Create the joystick
	DIJoystick* pJoystick = new DIJoystick(pDI->m_lpDIObject, joySetupInfo.hWnd, lpdidi, joySetupInfo.bIsExclusive);

	//	Failed to allocate the joystick
	if (pJoystick == NULL)
		return DIENUM_STOP; 

	//	Store the joystick.
	pDI->m_vpJoysticks.push_back(pJoystick);

	//	Continue looking for Joysticks.
	return DIENUM_CONTINUE;
}

bool DirectInput::JoystickButtonDown(unsigned char ucButton, int nJoyNum)			{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->ButtonDown(ucButton)); }

bool DirectInput::JoystickButtonPressed(unsigned char ucButton, int nJoyNum)		{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->ButtonPressed(ucButton)); }

bool DirectInput::JoystickButtonUp(unsigned char ucButton, int nJoyNum)			{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->ButtonUp(ucButton)); }

bool DirectInput::JoystickButtonReleased(unsigned char ucButton, int nJoyNum)		{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->ButtonReleased(ucButton)); }

bool DirectInput::JoystickDPadDown(int nDir, int nJoyNum)			{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->DPadDown(nDir)); }

bool DirectInput::JoystickDPadPressed(int nDir, int nJoyNum)		{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->DPadPressed(nDir)); }

bool DirectInput::JoystickDPadUp(int nDir, int nJoyNum)			{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->DPadUp(nDir)); }

bool DirectInput::JoystickDPadReleased(int nDir, int nJoyNum)		{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->DPadReleased(nDir)); }

bool DirectInput::JoystickGetLStickDirDown(int nDir, int nJoyNum)			{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->GetLStickDirDown(nDir)); }

bool DirectInput::JoystickGetLStickDirPressed(int nDir, int nJoyNum)		{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->GetLStickDirPressed(nDir)); }

int DirectInput::JoystickGetLStickXAmount(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetLStickXAmount() : 0; }

int DirectInput::JoystickGetLStickYAmount(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetLStickYAmount() : 0; }

float DirectInput::JoystickGetLStickXNormalized(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetLStickXNormalized() : 0.0f; }

float DirectInput::JoystickGetLStickYNormalized(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetLStickYNormalized() : 0.0f; }

bool DirectInput::JoystickGetRStickDirDown(int nDir, int nJoyNum)			{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->GetRStickDirDown(nDir)); }

bool DirectInput::JoystickGetRStickDirPressed(int nDir, int nJoyNum)		{ return ((nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) && m_vpJoysticks[nJoyNum]->GetRStickDirPressed(nDir)); }

int DirectInput::JoystickGetRStickXAmount(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetRStickXAmount() : 0; }

int DirectInput::JoystickGetRStickYAmount(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetRStickYAmount() : 0; }

float DirectInput::JoystickGetRStickXNormalized(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetRStickXNormalized() : 0.0f; }

float DirectInput::JoystickGetRStickYNormalized(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetRStickYNormalized() : 0.0f; }

int DirectInput::JoystickGetLTriggerAmount(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetLTriggerAmount() : 0; }

int DirectInput::JoystickGetRTriggerAmount(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetRTriggerAmount() : 0; }

float DirectInput::JoystickGetLTriggerNormalized(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetLTriggerNormalized() : 0.0f; }

float DirectInput::JoystickGetRTriggerNormalized(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetRTriggerNormalized() : 0.0f; }

int DirectInput::JoystickCheckBufferedButtons(int nJoyNum)	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->CheckBufferedButtons() : -1; }

int DirectInput::JoystickGetNumButtons(int nJoyNum) const	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->GetNumButtons() : 0; }

bool DirectInput::JoystickIsUnplugged(int nJoyNum) const	{ return (nJoyNum >= 0 && nJoyNum < (int)m_vpJoysticks.size()) ? m_vpJoysticks[nJoyNum]->IsUnplugged() : true; }

DIKeyboard::DIKeyboard(LPDIRECTINPUT8 pDI, HWND hWnd, bool bIsExclusive)
{
	//	Create the Keyboard Device.
	if (FAILED( pDI->CreateDevice(GUID_SysKeyboard, &m_lpDevice, NULL) ))
	{
	}

	//	Set the Data Format for the Keyboard.
	if (FAILED( m_lpDevice->SetDataFormat(&c_dfDIKeyboard) ))
	{
	}

	//	Set the Cooperative level for the keyboard.
	DWORD dwFlags = DISCL_FOREGROUND;

	if (bIsExclusive)
		dwFlags |= DISCL_EXCLUSIVE;
	else
		dwFlags |= DISCL_NONEXCLUSIVE | DISCL_NOWINKEY;

	if (FAILED( m_lpDevice->SetCooperativeLevel(hWnd, dwFlags) ))
	{
	}

	//	Set up the device to use buffered input
	//	For Use With Buffered Input.
	DIPROPDWORD dipdw;

	//	Clear the structure to all zeroes.
	memset(&dipdw, 0, sizeof(dipdw));

	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = 10;	//	Arbitrary buffer size

	//	Set the buffer size on the device.
	if (FAILED( m_lpDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph) ))
	{
	}
		//	Acquire the Keyboard.
		if (FAILED( m_lpDevice->Acquire() ))
		{
		}	

		ClearKeys();

		//	Get the Keyboard Layout.
		m_keyLayout = GetKeyboardLayout(0);
}

bool DIKeyboard::ReadDevice(void)
{
	//	Make sure the keyboard device was made.
	if (!m_lpDevice)
		return false;

	//	Remember previously pressed keys
	memcpy(m_ucPrevKeysPressed, m_ucKeysPressed, sizeof(m_ucPrevKeysPressed));

	//	Attempt to read the keyboard...
	if (FAILED( m_lpDevice->GetDeviceState(sizeof(m_ucKeysPressed), (LPVOID)m_ucKeysPressed) ))
	{
		//	If we couldn't, try to re-acquire the device.
		if (FAILED( m_lpDevice->Acquire() ))
			return false; //	Could not re-acquire the Keyboard.

		//	Now try reading it
		if (FAILED( m_lpDevice->GetDeviceState(sizeof(m_ucKeysPressed), (LPVOID)m_ucKeysPressed) ))
			return false;
	}

	//	Success.
	return true;
}

bool DIKeyboard::ReadBufferedDevice(void)
{
	//	Make sure the device was made.
	if (!m_lpDevice)
		return false;

	ClearBufferedData();

	//	Attempt to read the device...
	if (FAILED( m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_didod, &m_dwBufferElements, 0) ))
	{
		//	If we couldn't, try to re-acquire the device.
		if (FAILED( m_lpDevice->Acquire() ))
			return false; //	Could not re-acquire the Device.

		ClearBufferedData();

		//	Now try reading it
		if (FAILED( m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_didod, &m_dwBufferElements, 0) ))
			return false;
	}

	//	Success.
	return true;
}

bool DIKeyboard::KeyDown(unsigned char ucDIKey)
{
	//	if the high bit is on, it is pressed.
	return (m_ucKeysPressed[ucDIKey] & 0x80) ? true : false;
}

bool DIKeyboard::KeyPressed(unsigned char ucDIKey)
{
	//	if the key is down and wasn't previously pressed.
	return KeyDown(ucDIKey) && !(m_ucPrevKeysPressed[ucDIKey] & 0x80);
}

bool DIKeyboard::KeyUp(unsigned char ucDIKey)
{
	//	if the high bit is off, it isn't pressed.
	return !KeyDown(ucDIKey);
}

bool DIKeyboard::KeyReleased(unsigned char ucDIKey) // was key just released?
{
	//	if the key is up and was previously pressed.
	return KeyUp(ucDIKey) && (m_ucPrevKeysPressed[ucDIKey] & 0x80);
}

char DIKeyboard::CheckKeys(void)
{	
	//	Get the Current Keyboard State.
	if ( !GetKeyboardState(m_ucAsciiVals) )
		return 0; // Could not GetKeyboardState.

	unsigned short usNum	= 0;
	unsigned int uiVKCode	= 0;

	//	Go through each keyboard key
	for (int i = 0; i < 256; i++)
	{
		// if the high bit is on, it is pressed
		if (KeyDown( (unsigned char)i ))
		{
			//	Map the Scan Code from DirectInput to a Virtual Key value...
			uiVKCode = MapVirtualKeyEx(i, 1, m_keyLayout);
			//	...and translate that Virtual Key into an Ascii Value.
			ToAsciiEx(uiVKCode, i, m_ucAsciiVals, &usNum, 0, m_keyLayout);
		}
	}

	//	Return the Ascii Value.
	return (char)usNum;
}

unsigned char DIKeyboard::GetDIKCode(void)
{	
	unsigned char ucNum = 0;

	//	Go through each keyboard key
	for (int i = 0; i < 256; i++)
	{
		// find the first one that is pressed
		if (KeyDown( (unsigned char)i ))
		{
			ucNum = (unsigned char)i;
			break;
		}
	}

	//	Return the DIK Code.
	return ucNum;
}

DIMouse::DIMouse(LPDIRECTINPUT8 pDI, HWND hWnd, bool bIsExclusive)
{
	//	Create the Mouse Device.
	if (FAILED( pDI->CreateDevice(GUID_SysMouse, &m_lpDevice, NULL) ))
	{
	}

	//	Set the Data Format for the Mouse.
	if (FAILED( m_lpDevice->SetDataFormat(&c_dfDIMouse2) ))
	{
	}

	//	Set the Cooperative level for the mouse.
	DWORD dwFlags = DISCL_FOREGROUND;

	if (bIsExclusive)
		dwFlags |= DISCL_EXCLUSIVE;
	else
		dwFlags |= DISCL_NONEXCLUSIVE;

	if (FAILED( m_lpDevice->SetCooperativeLevel(hWnd, dwFlags) ))
	{
	}

	//	Set up the device to use buffered input
	//	For Use With Buffered Input.
	DIPROPDWORD dipdw;

	//	Clear the structure to all zeroes.
	memset(&dipdw, 0, sizeof(dipdw));

	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = 10;	//	Arbitrary buffer size

	//	Set the buffer size on the device.
	if (FAILED( m_lpDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph) ))
	{
	}

		//	Acquire the Mouse.
		if (FAILED( m_lpDevice->Acquire() ))
		{
		}	

		DIDEVCAPS  didCaps;

		// clear out struct
		memset(&didCaps, 0, sizeof(didCaps));
		didCaps.dwSize = sizeof(didCaps); 

	/*	m_lpDevice->GetCapabilities(&didCaps);
		{
			if (didCaps.dwFlags & DIDC_POLLEDDATAFORMAT)
				int y = 4;
			if (didCaps.dwFlags & DIDC_POLLEDDEVICE)
				int y = 5;
		}*/

		// will be zero if it failed because the struct was cleared out
		m_nNumButtons = didCaps.dwButtons;

		//	clear out current state
		memset(&m_diMouseState, 0, sizeof(m_diMouseState));
		//	clear prev state
		memset(&m_diPrevMouseState, 0, sizeof(m_diPrevMouseState));

		//	Set psuedo position of mouse
		SetPosX( 0 );
		SetPosY( 0 );
}

bool DIMouse::ReadDevice(void)
{
	//	Make sure the mouse device was made.
	if (!m_lpDevice)
		return false;

	//	Remember previous state
	memcpy(&m_diPrevMouseState, &m_diMouseState, sizeof(m_diPrevMouseState));

	//	Attempt to read the mouse...
	if (FAILED( m_lpDevice->GetDeviceState(sizeof(m_diMouseState), (LPVOID)&m_diMouseState) ))
	{
		//	If we couldn't, try to re-acquire the device.
		if (FAILED( m_lpDevice->Acquire() ))
			return false; //	Could not re-acquire the Mouse.

		//	Now try reading it
		if (FAILED( m_lpDevice->GetDeviceState(sizeof(m_diMouseState), (LPVOID)&m_diMouseState) ))
			return false;
	}

	// Update "psuedo" position of mouse
	SetPosX( GetPosX() + MovementX() );
	SetPosY( GetPosY() + MovementY() );

	//	Success.
	return true;
}

bool DIMouse::ReadBufferedDevice(void)
{
	//	Make sure the device was made.
	if (!m_lpDevice)
		return false;

	ClearBufferedData();

	//	Attempt to read the device...
	if (FAILED( m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_didod, &m_dwBufferElements, 0) ))
	{
		//	If we couldn't, try to re-acquire the device.
		if (FAILED( m_lpDevice->Acquire() ))
			return false; //	Could not re-acquire the Device.

		ClearBufferedData();

		//	Now try reading it
		if (FAILED( m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_didod, &m_dwBufferElements, 0) ))
			return false;
	}

	//	Success.
	return true;
}


bool DIMouse::ButtonDown(unsigned char ucButton)
{
	//	if the high bit is on, it is pressed.
	return (m_diMouseState.rgbButtons[ucButton] & 0x80) ? true : false;
}

bool DIMouse::ButtonPressed(unsigned char ucButton)
{
	//	if the button is down and wasn't previously pressed.
	return ButtonDown(ucButton) && !(m_diPrevMouseState.rgbButtons[ucButton] & 0x80);
}

bool DIMouse::ButtonUp(unsigned char ucButton)
{
	//	if the high bit is off, it isn't pressed.
	return !ButtonDown(ucButton);
}

bool DIMouse::ButtonReleased(unsigned char ucButton)
{
	//	if the button is up and was previously pressed.
	return ButtonUp(ucButton) && (m_diPrevMouseState.rgbButtons[ucButton] & 0x80);
}

int DIMouse::CheckBufferedButtons(void)
{
	int nButton = -1;

	//	Go through all mouse buttons.
	for (int j = 0; j < GetNumButtons(); j++)
	{
		//	Find the first button that was pressed
		if (ButtonPressed((unsigned char)j))
		{
			//	return the first one that was found to be pressed.
			nButton = j;
			break;
		}
	}

	//	return the button.
	return nButton;
}

long DIMouse::MovementX(void)
{
	return m_diMouseState.lX;
}

long DIMouse::MovementY(void)
{
	return m_diMouseState.lY;
}

long DIMouse::WheelMovement(void)
{
	return m_diMouseState.lZ;
}

const int	JOYSTICK_AXIS_RANGE = 1024;
const float PERCENTAGE_RANGE	= 0.7f;
const int	JOYSTICK_THRESHOLD	= (int)(JOYSTICK_AXIS_RANGE * PERCENTAGE_RANGE);

const float ONE_OVER_RANGE = 1.0f / (float)JOYSTICK_AXIS_RANGE;


DIJoystick::DIJoystick(LPDIRECTINPUT8 pDI, HWND hWnd, const DIDEVICEINSTANCE* lpdidi, bool bIsExclusive)
{

	//	Create the Joystick Device.
	if (FAILED( pDI->CreateDevice(lpdidi->guidInstance, &m_lpDevice, NULL) ))
	{
	}

	//	Set the Data Format for the Joystick.
	if (FAILED( m_lpDevice->SetDataFormat(&c_dfDIJoystick2) ))
	{
	}

	DIDEVCAPS  didCaps;

	// clear out struct
	memset(&didCaps, 0, sizeof(didCaps));
	didCaps.dwSize = sizeof(didCaps); 

	m_lpDevice->GetCapabilities(&didCaps);
	{
		//if (didCaps.dwFlags & DIDC_POLLEDDATAFORMAT)
		//	int y = 4;
		//if (didCaps.dwFlags & DIDC_POLLEDDEVICE)
			//int y = 5;

		if (didCaps.dwFlags & DIDC_FORCEFEEDBACK)
			bIsExclusive = true; // forces true so that the device can use ForceFeedback (has to be exclusive to use FF).
	}

	//DWORD axes = didCaps.dwAxes;
	//DWORD povs = didCaps.dwPOVs;

	// will be zero if it failed because the struct was cleared out
	m_nNumButtons = didCaps.dwButtons;

	//	Set the Cooperative level for the Joystick.
	DWORD dwFlags = DISCL_FOREGROUND;

	if (bIsExclusive)
		dwFlags |= DISCL_EXCLUSIVE;
	else
		dwFlags |= DISCL_NONEXCLUSIVE;

	if (FAILED( m_lpDevice->SetCooperativeLevel(hWnd, dwFlags) ))
	{
	}

	//	Set the Properties for the Joystick Axes:

	//	Set the ranges for the axes:
	DIPROPRANGE dipr;
	dipr.diph.dwSize		= sizeof(DIPROPRANGE);
	dipr.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
	dipr.diph.dwHow			= DIPH_BYOFFSET;
	dipr.lMin				= -JOYSTICK_AXIS_RANGE;	//	Minimum range.
	dipr.lMax				= +JOYSTICK_AXIS_RANGE;	//	Maximum range.

	dipr.diph.dwObj			= DIJOFS_X;				//	Change the X-Axis.
	m_lpDevice->SetProperty(DIPROP_RANGE, &dipr.diph);

	//	Change the Y-Axis.
	dipr.diph.dwObj			= DIJOFS_Y;
	m_lpDevice->SetProperty(DIPROP_RANGE, &dipr.diph);

	//	Is it not an Xbox360 controller?
	if (!m_bIsXbox360Pad)
	{
		//	Change the Z-Axis //(left/right on R-stick).
		dipr.diph.dwObj			= DIJOFS_Z;
		m_lpDevice->SetProperty(DIPROP_RANGE, &dipr.diph);

		//	Change the RotationZ-Axis //(up/down on R-stick).
		dipr.diph.dwObj			= DIJOFS_RZ;
		m_lpDevice->SetProperty(DIPROP_RANGE, &dipr.diph);
	}
	else // it is an Xbox360 controller
	{
		//	Change the Z-Axis (for L + R triggers).
		dipr.diph.dwObj			= DIJOFS_Z;
		m_lpDevice->SetProperty(DIPROP_RANGE, &dipr.diph);

		//	Change the RotationX-Axis (left/right on R-stick).
		dipr.diph.dwObj			= DIJOFS_RX;
		m_lpDevice->SetProperty(DIPROP_RANGE, &dipr.diph);

		//	Change the RotationY-Axis (up/down on R-stick).
		dipr.diph.dwObj			= DIJOFS_RY;
		m_lpDevice->SetProperty(DIPROP_RANGE, &dipr.diph);
	}

	//	Setup a Dead Zone for the axes.
	DIPROPDWORD deadZone;
	deadZone.diph.dwSize	   = sizeof (deadZone);
	deadZone.diph.dwHeaderSize = sizeof (deadZone.diph);
	deadZone.diph.dwObj		   = DIJOFS_X;
	deadZone.diph.dwHow		   = DIPH_BYOFFSET;
	deadZone.dwData			   = 1000;

	//	Setup the X-Axis Dead Zone.
	m_lpDevice->SetProperty(DIPROP_DEADZONE, &deadZone.diph);

	//	Setup the Y-Axis Dead Zone.
	deadZone.diph.dwObj		   = DIJOFS_Y;
	m_lpDevice->SetProperty(DIPROP_DEADZONE, &deadZone.diph);

	if (!m_bIsXbox360Pad)
	{
		//	Setup the Z-Axis Dead Zone.
		deadZone.diph.dwObj		   = DIJOFS_Z;
		m_lpDevice->SetProperty(DIPROP_DEADZONE, &deadZone.diph);

		//	Setup the ZR-Axis Dead Zone.
		deadZone.diph.dwObj		   = DIJOFS_RZ;
		m_lpDevice->SetProperty(DIPROP_DEADZONE, &deadZone.diph);
	}
	else
	{

		//	Setup the RotationX-Axis Dead Zone.
		deadZone.diph.dwObj		   = DIJOFS_RX;
		m_lpDevice->SetProperty(DIPROP_DEADZONE, &deadZone.diph);

		//	Setup the RotationY-Axis Dead Zone.
		deadZone.diph.dwObj		   = DIJOFS_RY;
		m_lpDevice->SetProperty(DIPROP_DEADZONE, &deadZone.diph);
	}

	//	Set up the device to use buffered input
	//	For Use With Buffered Input.
	DIPROPDWORD dipdw;

	//	Clear the structure to all zeroes.
	memset(&dipdw, 0, sizeof(dipdw));

	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = 10;	//	Arbitrary buffer size

	//	Set the buffer size on the device.
	if (FAILED( m_lpDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph) ))
	{
		
	}

	//	Acquire the Joystick.
	if (FAILED( m_lpDevice->Acquire() ))
	{
		
	}

	//	clear out struct
	memset(&m_diJoyState, 0, sizeof(m_diJoyState));
	memset(&m_diPrevJoyState, 0, sizeof(m_diPrevJoyState));

	m_bIsUnplugged = false;
}

bool DIJoystick::ReadDevice(void)
{
	//	Just in case
	if (!m_lpDevice)
		return false;

	//	Remember the previous state of the joystick
	memcpy(&m_diPrevJoyState, &m_diJoyState, sizeof(m_diPrevJoyState));

	//	Clear out the current state's data
	memset(&m_diJoyState, 0, sizeof(m_diJoyState));

	//	Poll the joystick to update its state
	if (FAILED( m_lpDevice->Poll() ))
	{
		//	Try to Acquire the Joystick.
		HRESULT hr = m_lpDevice->Acquire();

		//	Make sure the joystick is plugged in.
		if (!m_bIsUnplugged)
		{
			//	Check if the joystick was unplugged
			if (hr == DIERR_UNPLUGGED)
				m_bIsUnplugged = true;
		}

		//	Try to re-acquire the joystick if it is unplugged.
		if (m_bIsUnplugged)
		{
			if (SUCCEEDED( m_lpDevice->Acquire() ))
				m_bIsUnplugged = false;
		}

		//	If no input from joystick re-acquire.
		if (hr == DIERR_INPUTLOST)
			hr = m_lpDevice->Acquire();

	}

	//	Attempt to read the joystick state...
	if (FAILED( m_lpDevice->GetDeviceState(sizeof(m_diJoyState), (LPVOID)&m_diJoyState) ))
		return false;

	return true;
}

bool DIJoystick::ReadBufferedDevice(void)
{
	//	Make sure the device was made.
	if (!m_lpDevice)
		return false;

	ClearBufferedData();

	//	Attempt to read the device...
	if (FAILED( m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_didod, &m_dwBufferElements, 0) ))
	{
		//	If we couldn't, try to re-acquire the device.
		if (FAILED( m_lpDevice->Acquire() ))
			return false; //	Could not re-acquire the Device.

		ClearBufferedData();

		//	Now try reading it
		if (FAILED( m_lpDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_didod, &m_dwBufferElements, 0) ))
			return false;
	}

	return true;
}

bool DIJoystick::ButtonDown(unsigned char ucButton)
{
	//	if the high bit is on, it is pressed.
	return (m_diJoyState.rgbButtons[ucButton] & 0x80) ? true : false;
}

bool DIJoystick::ButtonPressed(unsigned char ucButton)
{
	return ButtonDown(ucButton) && !(m_diPrevJoyState.rgbButtons[ucButton] & 0x80);
}

bool DIJoystick::ButtonUp(unsigned char ucButton)
{
	return !ButtonDown(ucButton);
}

bool DIJoystick::ButtonReleased(unsigned char ucButton)
{
	return ButtonUp(ucButton) && (m_diPrevJoyState.rgbButtons[ucButton] & 0x80);
}

bool DIJoystick::TranslatePOV(int nDir, DWORD dwPOVDir)
{
	// means neutral
	bool bIsPOVCentered = (LOWORD(dwPOVDir) == 0xFFFF);

	if (bIsPOVCentered)
		return false;

	int nPOV = (int)LOWORD(dwPOVDir);

	switch(nDir)
	{
	case DIR_UP: // could be up/left, up, or up/right.
		{
			return (nPOV > POV_LEFT || nPOV < POV_RIGHT);
		}
		break;

	case DIR_DOWN: // could be dwn/left, dwn, or dwn/right.
		{
			return (nPOV > POV_RIGHT && nPOV < POV_LEFT);
		}
		break;

	case DIR_LEFT: // could be up/left, left, or dwn/left.
		{
			return (/*dwPOVDir > POV_UP && */nPOV > POV_DOWN);
		}
		break;

	case DIR_RIGHT: // could be up/right, right, or dwn/right.
		{
			return (nPOV > POV_UP && nPOV < POV_DOWN);
		}
		break;
	};

	return false;
}

LONG DIJoystick::TranslateRStickX(DIJOYSTATE2& diJoyState)
{
	//	Just in case
	if (!m_lpDevice)
		return 0;

	//	Check for the Direction.
	if (!m_bIsXbox360Pad)
	{
		return (m_bIsZAxisY) ? diJoyState.lRz : diJoyState.lZ;
	}
	else	//	is Xbox 360 pad
	{
		return diJoyState.lRx;
	}
}

LONG DIJoystick::TranslateRStickY(DIJOYSTATE2& diJoyState)
{
	// Just in case
	if (!m_lpDevice)
		return 0;

	//	Check for the Direction.
	if (!m_bIsXbox360Pad)
	{
		return (m_bIsZAxisY) ? diJoyState.lZ : diJoyState.lRz; 
	}
	else	//	is Xbox 360 pad
	{
		return diJoyState.lRy;
	}
}

bool DIJoystick::DPadDown(int nDir)
{
//	DWORD dwDir = m_diJoyState.rgdwPOV[0];

	return TranslatePOV(nDir, m_diJoyState.rgdwPOV[0]);
}

bool DIJoystick::DPadPressed(int nDir)
{
	return DPadDown(nDir) && !TranslatePOV(nDir, m_diPrevJoyState.rgdwPOV[0]);
}

bool DIJoystick::DPadUp(int nDir)
{
	return !DPadDown(nDir);
}
bool DIJoystick::DPadReleased(int nDir)
{
	return !DPadDown(nDir) && TranslatePOV(nDir, m_diPrevJoyState.rgdwPOV[0]);
}

bool DIJoystick::GetLStickDirDown(int nDir)
{
	//	Just in case
	if (!m_lpDevice)
		return false;

	//	Check for the Direction.
	switch(nDir)
	{
	case DIR_LEFT:
		{
			if (m_diJoyState.lX < 0) 
				return true;
		}		
		break;

	case DIR_RIGHT:
		{
			if (m_diJoyState.lX > 0) 
				return true;
		}	
		break;

	case DIR_UP:
		{
			if (m_diJoyState.lY < 0) 
				return true;
		}
		break;

	case DIR_DOWN:
		{
			if (m_diJoyState.lY > 0) 
				return true;
		}	
		break;
	};

	//	If nothing was pressed
	return false;
}

bool DIJoystick::GetLStickDirPressed(int nDir)
{
	//	Just in case
	if (!m_lpDevice)
		return false;

	//	Check for the Direction.
	switch(nDir)
	{
	case DIR_LEFT:
		{
			if (m_diJoyState.lX < -JOYSTICK_THRESHOLD && !(m_diPrevJoyState.lX < -JOYSTICK_THRESHOLD)) 
				return true;
		}		
		break;

	case DIR_RIGHT:
		{
			if (m_diJoyState.lX > JOYSTICK_THRESHOLD && !(m_diPrevJoyState.lX > JOYSTICK_THRESHOLD)) 
				return true;
		}	
		break;

	case DIR_UP:
		{
			if (m_diJoyState.lY < -JOYSTICK_THRESHOLD && !(m_diPrevJoyState.lY < -JOYSTICK_THRESHOLD)) 
				return true;
		}
		break;

	case DIR_DOWN:
		{
			if (m_diJoyState.lY > JOYSTICK_THRESHOLD && !(m_diPrevJoyState.lY > JOYSTICK_THRESHOLD)) 
				return true;
		}	
		break;
	};

	//	If nothing was pressed
	return false;
}

int DIJoystick::GetLStickXAmount(void)
{
	//	Just in case
	if (!m_lpDevice)
		return 0;

	return m_diJoyState.lX;
}

int DIJoystick::GetLStickYAmount(void)
{
	// Just in case
	if (!m_lpDevice)
		return 0;

	return m_diJoyState.lY;
}

float DIJoystick::GetLStickXNormalized()
{
	return (float)GetLStickXAmount() * ONE_OVER_RANGE;
}

float DIJoystick::GetLStickYNormalized()
{
	return (float)GetLStickYAmount() * ONE_OVER_RANGE;
}

bool DIJoystick::GetRStickDirDown(int nDir)
{
	//	Just in case
	if (!m_lpDevice)
		return false;

	// Check Direction
	switch(nDir)
	{
	case DIR_LEFT:
		{
			if ( TranslateRStickX(m_diJoyState) < 0 ) 
				return true;
		}		
		break;

	case DIR_RIGHT:
		{
			if ( TranslateRStickX(m_diJoyState) > 0 ) 
				return true;
		}	
		break;

	case DIR_UP:
		{
			if ( TranslateRStickY(m_diJoyState) < 0 ) 
				return true;
		}
		break;

	case DIR_DOWN:
		{
			if ( TranslateRStickY(m_diJoyState) > 0 ) 
				return true;
		}	
		break;
	};

	//	If nothing was pressed
	return false;
}

bool DIJoystick::GetRStickDirPressed(int nDir)
{
	//	Just in case
	if (!m_lpDevice)
		return false;

	//	Check for the Direction.
	switch(nDir)
	{
	case DIR_LEFT:
		{
			if ( TranslateRStickX(m_diJoyState) < -JOYSTICK_THRESHOLD && !(TranslateRStickX(m_diPrevJoyState) < -JOYSTICK_THRESHOLD) ) 
				return true;
		}		
		break;

	case DIR_RIGHT:
		{
			if ( TranslateRStickX(m_diJoyState) > JOYSTICK_THRESHOLD && !(TranslateRStickX(m_diPrevJoyState) > JOYSTICK_THRESHOLD) ) 
				return true;
		}	
		break;

	case DIR_UP:
		{
			if ( TranslateRStickY(m_diJoyState) < -JOYSTICK_THRESHOLD && !(TranslateRStickY(m_diPrevJoyState) < -JOYSTICK_THRESHOLD) ) 
				return true;
		}
		break;

	case DIR_DOWN:
		{
			if ( TranslateRStickY(m_diJoyState) > JOYSTICK_THRESHOLD && !(TranslateRStickY(m_diPrevJoyState) > JOYSTICK_THRESHOLD) ) 
				return true;
		}	
		break;
	};

	// If nothing was pressed
	return false;
}

int DIJoystick::GetRStickXAmount(void)
{
	//	Just in case
	if (!m_lpDevice)
		return 0;

	return TranslateRStickX(m_diJoyState);
}

int DIJoystick::GetRStickYAmount(void)
{
	// Just in case
	if (!m_lpDevice)
		return 0;

	return TranslateRStickY(m_diJoyState);
}

float DIJoystick::GetRStickXNormalized()
{
	return (float)GetRStickXAmount() * ONE_OVER_RANGE;
}

float DIJoystick::GetRStickYNormalized()
{
	return (float)GetRStickYAmount() * ONE_OVER_RANGE;
}

int DIJoystick::GetLTriggerAmount(void)
{
	if (!m_bIsXbox360Pad) return 0;

	return m_diJoyState.lZ;
}

int DIJoystick::GetRTriggerAmount(void)
{
	if (!m_bIsXbox360Pad) return 0;

	return -m_diJoyState.lZ;
}

float DIJoystick::GetLTriggerNormalized(void)
{
	return GetRTriggerAmount() * ONE_OVER_RANGE;
}

float DIJoystick::GetRTriggerNormalized(void)
{
	return GetRTriggerAmount() * ONE_OVER_RANGE;
}

int	DIJoystick::CheckBufferedButtons(void)
{
	int nButton = -1;

	return nButton;
}