#ifndef __HowToPlayMenuState_h__
#define __HowToPlayMenuState_h__

#include "IMenuState.h"

class ViewManager;
class AudioManager;
class DirectInput;

class HowToPlayMenuState: public IMenuState
{
private: 
	ViewManager* m_pVM;
	DirectInput* m_pDI;
	AudioManager* audio;
	int		m_nHowToKeyID;
	int		m_nHowToJoyID;
	int		m_nHowToXboxID;
	int soundID2;
	int musicID;
	int musicID2;
	int m_nFontID;

	HowToPlayMenuState();
	~HowToPlayMenuState();
	HowToPlayMenuState(const HowToPlayMenuState&);
	HowToPlayMenuState& operator=(const HowToPlayMenuState&);

public: 
	static HowToPlayMenuState* GetInstance();

	void Enter(void);

	void Exit(void);

	bool Input(void);

	void Update(float fElapsedTime);

	void Render(void);
	void ReEnter();
};

#endif
