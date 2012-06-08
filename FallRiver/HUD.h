#include <Windows.h>
using namespace std;

#ifndef __HUD_h__
#define __HUD_h__

// #include "GamePlayState.h"
// #include "ViewManager.h"

class GamePlayState;
class ViewManager;
class HUD;

class HUD
{
private: 
	float m_fHealth;
	float m_fTime;
	int m_nWeapon;
	float m_fOrientation;
	float m_fFlashlightLife;
	int m_nAmmo;
	int m_nClip;

public:
	HUD();

	~HUD();

	void Update(float time);

	void Render();

	void Input();
};

#endif
