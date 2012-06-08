#include <exception>
using namespace std;

#ifndef __DIMouse_h__
#define __DIMouse_h__

// #include "DirectInput.h"
#include "IDirectInputDevice.h"

class DirectInput;
// class IDirectInputDevice;
class DIMouse;

class DIMouse: public IDirectInputDevice
{
	private: DIMOUSESTATE2 _m_diMouseState;
	private: DIMOUSESTATE2 _m_diPrevMouseState;
	private: int _m_nNumButtons;
	private: int _m_nPosX;
	private: int _m_nPosY;
	public: DirectInput* _unnamed_DirectInput_;

	public: void clearMouseButtons();

	public: DIMouse(LPDIRECTINPUT8 aPDI, HWND aHWnd, bool aBIsExclusive);

	public: bool readDevice();

	public: bool readBufferedDevice();

	public: bool buttonDown(unsigned char aUcButton);

	public: bool buttonPressed(unsigned char aUcButton);

	public: bool buttonUp(unsigned char aUcButton);

	public: bool buttonReleased(unsigned char aUcButton);

	public: int checkBufferedButtons();

	public: virtual bool acquire();

	public: virtual bool unacquire();
};

#endif
