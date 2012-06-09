#include <Windows.h>
#include <vector>
using namespace std;

#pragma once

//	The version of DirectInput to use.
#ifndef DIRECTInput_VERSION
#define DIRECTInput_VERSION 0X800
#endif
#include <dInput.h>

#pragma comment(lib, "dInput8.lib")
#pragma comment(lib, "dxguid.lib")


#include <tchar.h>
#include <vector>
using std::vector;

//#include "SGD_Util.h"	//	for utility macros

//	Forward declarations:
class DIKeyboard;
class DIMouse;
class DIJoystick;

//	Enumerations:
//		Devices:
enum DeviceFlags { DI_KEYBOARD = 1, DI_MOUSE = 2, DI_JOYSTICKS = 4 };

//		Directions
enum Directions { DIR_LEFT = 0, DIR_RIGHT = 1, DIR_UP = 2, DIR_DOWN = 3, DIR_MAX };

//		Mouse buttons
enum MouseButtons { MOUSE_LEFT = 0, MOUSE_RIGHT = 1, MOUSE_MIDDLE = 2, MOUSE_MAX };

class DirectInput
{
private: 
	vector<DIJoystick*> m_vpJoysticks;
	DIKeyboard* m_pKeyboard;
	DIMouse* m_pMouse;
	LPDIRECTINPUT8 m_lpDIObject;
	static DirectInput m_Instance;

	struct tJoystickSetupInfo
	{
		HWND hWnd;
		bool bIsExclusive;
	};

	DirectInput();

	~DirectInput(void);

	DirectInput(DirectInput& ref);

	bool InitMouse(HWND aHWnd, bool bIsExclusive);

	bool InitJoysticks(HWND aHWnd, bool bIsExclusive);

	bool InitKeyboard(HWND aHWnd, bool bIsExclusive);

public:
	static DirectInput* GetInstance();

	bool InitDirectInput(HWND hWnd, HINSTANCE hInstance, unsigned int unInitDevices, unsigned int aUnExclusiveDevices);

	void ShutdownDirectInput();

	void ReadDevices();

	void ClearInput();

	void AcquireAll();

	void UnacquireAll();

	bool KeyDown(unsigned char ucDIKey);

	bool KeyPressed(unsigned char ucDIKey);

	bool KeyUp(unsigned char ucDIKey);

	bool KeyReleased(unsigned char ucDIKey);

	char CheckKeys();

	unsigned char GetDIKCode();

	bool MouseButtonDown(unsigned char ucButton);

	bool MouseButtonPressed(unsigned char ucButton);

	bool MouseButtonUp(unsigned char ucButton);

	bool MouseButtonReleased(unsigned char ucButton);

	int MouseCheckBufferedButtons();

	long MouseMovementX();

	long MouseMovementY();

	long MouseWheelMovement();

	int MouseGetNumButtons(void);

	int MouseGetPosX(void);

	int MouseGetPosY(void);

	void MouseSetPosX(int nPosX);

	void MouseSetPosY(int nPosY);

	bool JoystickButtonDown(unsigned char ucButton, int nJoyNum);

	bool JoystickButtonPressed(unsigned char ucButton, int nJoyNum);

	bool JoystickButtonUp(unsigned char ucButton, int nJoyNum);

	bool JoystickButtonReleased(unsigned char ucButton, int nJoyNum);

	bool JoystickDPadDown(int nDir, int nJoyNum);

	bool JoystickDPadPressed(int nDir, int nJoyNum);

	bool JoystickDPadUp(int nDir, int nJoyNum);

	bool JoystickDPadReleased(int nDir, int nJoyNum);

	bool JoystickGetLStickDirDown(int nDir, int nJoyNum);		

	bool JoystickGetLStickDirPressed(int nDir, int nJoyNum);

	int JoystickGetLStickXAmount(int nJoyNum);

	int JoystickGetLStickYAmount(int nJoyNum);

	float JoystickGetLStickXNormalized(int nJoyNum);

	float JoystickGetLStickYNormalized(int nJoyNum);

	bool JoystickGetRStickDirDown(int nDir, int nJoyNum);			

	bool JoystickGetRStickDirPressed(int nDir, int nJoyNum);	

	int JoystickGetRStickXAmount(int nJoyNum);

	int JoystickGetRStickYAmount(int nJoyNum);

	float JoystickGetRStickXNormalized(int nJoyNum);

	float JoystickGetRStickYNormalized(int nJoyNum);

	int JoystickGetLTriggerAmount(int nJoyNum);

	int JoystickGetRTriggerAmount(int nJoyNum); 

	float JoystickGetLTriggerNormalized(int nJoyNum);

	float JoystickGetRTriggerNormalized(int nJoyNum);

	int JoystickCheckBufferedButtons(int nJoyNum);

	int JoystickGetNumButtons(int nJoyNum) const;

	bool JoystickIsUnplugged(int nJoyNum) const;

	static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* lpdidi, VOID* pVoid);
};

class IFRDirectInputDevice
{
public:
	virtual ~IFRDirectInputDevice(void) = 0 {};

	virtual bool ReadDevice(void) = 0;
	virtual bool ReadBufferedDevice(void) = 0;

	virtual bool Acquire(void) = 0;
	virtual bool Unacquire(void) = 0;

}; 	//	end class ISGD_DirectInputDevice

class IInputDevice : IFRDirectInputDevice
{
protected:
	LPDIRECTINPUTDEVICE8	m_lpDevice;					//	DirectInput Device pointer.

	//	For DirectX Buffered input:
	DIDEVICEOBJECTDATA		m_didod[10];	//	Receives buffered data for the device.
	DWORD					m_dwBufferElements;			//	Number of element in the buffer for the device.

	//	Utility function to clear buffered data.
	void ClearBufferedData(void)
	{
		memset(&m_didod, 0, sizeof(m_didod));	//	clear out device object data.
		m_dwBufferElements = 10;	//	set buffer elements to the size of the array.
	}

public:
	//	Constructor.
	IInputDevice(void)
	{
		m_lpDevice = NULL;

		ClearBufferedData();
	}

	//	Destructor.
	virtual ~IInputDevice(void)
	{
		if (m_lpDevice)
		{
			m_lpDevice->Unacquire();
			m_lpDevice->Release();
			m_lpDevice = NULL;
		}
	}

	virtual bool ReadBufferedDevice(void)
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

		//	Success
		return true;
	}

	//	returns true if the device was able to be acquired.
	virtual bool Acquire(void)		{ return (m_lpDevice) ? SUCCEEDED( m_lpDevice->Acquire() ) : false; }

	//	returns true if the device was able to be unacquired.
	virtual bool Unacquire(void)	{ return (m_lpDevice) ? SUCCEEDED( m_lpDevice->Unacquire() ) : false; }

}; 	//	end class CSGD_DirectInputDevice


class DIKeyboard: public IInputDevice
{
private:
	unsigned char m_ucKeysPressed[256];
	unsigned char m_ucPrevKeysPressed[256];
	unsigned char m_ucAsciiVals[256];
	HKL m_keyLayout;

public:

	DIKeyboard(LPDIRECTINPUT8 pDI, HWND hWnd, bool bIsExclusive);

	void ClearKeys(void)	
	{ 
		//	clear the currently pressed keys
		memset(m_ucKeysPressed, 0, 256 * sizeof(unsigned char)); 
		//	clear the previously pressed keys
		memset(m_ucPrevKeysPressed, 0, 256 * sizeof(unsigned char));
	}

	bool ReadDevice();

	bool ReadBufferedDevice();

	bool Acquire(void)		{ ClearKeys(); return IInputDevice::Acquire(); }

	bool Unacquire(void)	{ ClearKeys(); return IInputDevice::Unacquire();  }

	bool KeyDown(unsigned char ucDIKey);

	bool KeyPressed(unsigned char ucDIKey);

	bool KeyUp(unsigned char ucDIKey);

	bool KeyReleased(unsigned char ucDIKey);

	unsigned char DIKeyboard::GetDIKCode(void);

	char CheckKeys();
};

class DIMouse: public IInputDevice
{
private: 
	DIMOUSESTATE2 m_diMouseState;
	DIMOUSESTATE2 m_diPrevMouseState;
	int m_nNumButtons;
	int m_nPosX;
	int m_nPosY;
public: 

	void ClearMouseButtons(void)	
	{ 
		//	clear the currently pressed keys
		memset(m_diMouseState.rgbButtons, 0, 8*sizeof(BYTE)); 
		//	clear the previously pressed keys
		memset(m_diPrevMouseState.rgbButtons, 0, 8*sizeof(BYTE));
	}

	DIMouse(LPDIRECTINPUT8 pDI, HWND hWnd, bool bIsExclusive);

	bool ReadDevice();

	bool ReadBufferedDevice();

	bool ButtonDown(unsigned char aUcButton);

	bool ButtonPressed(unsigned char aUcButton);

	bool ButtonUp(unsigned char aUcButton);

	bool ButtonReleased(unsigned char aUcButton);

	int CheckBufferedButtons();

	long MovementX(void);

	long MovementY(void);

	long WheelMovement(void);

	int GetNumButtons(void)		{ return m_nNumButtons; }

	int GetPosX(void)			{ return m_nPosX; }

	int GetPosY(void)			{ return m_nPosY; }

	void SetPosX(int nPosX)			{ m_nPosX = nPosX; }

	void SetPosY(int nPosY)			{ m_nPosY = nPosY; }
};

class DIJoystick: public IInputDevice
{
private: 
	TCHAR m_szJoyName;
	DIJOYSTATE2 m_diJoyState;
	DIJOYSTATE2 m_diPrevJoyState;
	int m_nNumButtons;
	bool m_bIsUnplugged;
	bool m_bIsXbox360Pad;
	bool m_bIsZAxisY;

	// POV constants
	enum POV_dirs
	{ 
		POV_NEUTRAL		=  -1,
		POV_UP			=   0,
		POV_UPRIGHT		=  45 * DI_DEGREES, 
		POV_RIGHT		=  90 * DI_DEGREES,
		POV_DOWNRIGHT	= 135 * DI_DEGREES,
		POV_DOWN		= 180 * DI_DEGREES,
		POV_DOWNLEFT	= 225 * DI_DEGREES,
		POV_LEFT		= 270 * DI_DEGREES,
		POV_UPLEFT		= 315 * DI_DEGREES
	};

	bool TranslatePOV(int nDir, DWORD dwPOVDir);

	LONG TranslateRStickX(DIJOYSTATE2& diJoyState);
	LONG TranslateRStickY(DIJOYSTATE2& diJoyState);

public:
	void ClearJoystickButtons(void)	
	{ 
		//	clear the currently pressed keys
		memset(m_diJoyState.rgbButtons, 0, 128*sizeof(BYTE)); 
		//	clear the previously pressed keys
		memset(m_diPrevJoyState.rgbButtons, 0, 128* sizeof(BYTE));
	}

	DIJoystick(LPDIRECTINPUT8 pDI, HWND hWnd, const DIDEVICEINSTANCE* lpdidi, bool bIsExclusive);

	bool ReadDevice();

	bool ReadBufferedDevice();

	bool ButtonDown(unsigned char ucButton);

	bool ButtonPressed(unsigned char ucBotton);

	bool ButtonUp(unsigned char ucButton);

	bool ButtonReleased(unsigned char ucButton);

	bool DPadDown(int nDir);

	bool DPadPressed(int nDir);

	bool DPadUp(int nDir);

	bool DPadReleased(int nDir);

	bool GetLStickDirDown(int nDir);

	bool GetLStickDirPressed(int nDir);

	int GetLStickXAmount(void);

	int GetLStickYAmount(void);

	float GetLStickXNormalized();

	float GetLStickYNormalized();

	bool GetRStickDirDown(int nDir);

	bool GetRStickDirPressed(int nDir);

	int GetRStickXAmount(void);

	int GetRStickYAmount(void);

	float GetRStickXNormalized();

	float GetRStickYNormalized();

	int GetLTriggerAmount(void);

	int GetRTriggerAmount(void);

	float GetLTriggerNormalized(void);

	float GetRTriggerNormalized(void);

	int GetNumButtons(void)	const			{ return m_nNumButtons; }

	int CheckBufferedButtons();

	bool IsUnplugged() { return m_bIsUnplugged; }
};
