#include <Windows.h>
using namespace std;

#ifndef __LoadMenuState_h__
#define __LoadMenuState_h__

#include "IMenuState.h"

class ViewManager;
class AudioManager;
class XMLManager;
class DirectInput;

class SaveMenuState: public IMenuState
{
private: 
	ViewManager* m_pVM;
	DirectInput* m_pDI;
	int m_nCursPosY;
	int m_nCursPosX;
	AudioManager* audio;
	bool m_bSure;
	bool m_bCheck;

	int m_nFontID;

	SaveMenuState();
	~SaveMenuState();
	SaveMenuState(const SaveMenuState&);
	SaveMenuState& operator= (const SaveMenuState&);

	int soundID;
	int soundID2;
	//int musicID;
	//int musicID2;

public:

	static SaveMenuState* GetInstance();

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();
	void ReEnter();
};

#endif
