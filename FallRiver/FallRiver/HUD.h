#include <Windows.h>
using namespace std;

#ifndef __HUD_h__
#define __HUD_h__

// #include "GamePlayState.h"
// #include "ViewManager.h"
#include <tchar.h>
#include <string.h>

class GamePlayState;
class ViewManager;
class HUD;

class HUD
{
public:
	float m_fHealth;
	int m_nFontID;
	float m_fTime;
	int m_nWeapon;
	int m_nLives;
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
