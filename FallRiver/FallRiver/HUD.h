#include <Windows.h>
using namespace std;

#ifndef __HUD_h__
#define __HUD_h__

// #include "GamePlayState.h"
// #include "ViewManager.h"
#include <tchar.h>
#include <string.h>
#include <vector>

class GamePlayState;
class ViewManager;
class HUD;

class HUD
{
private:
	float m_fHealth;
	int m_nFontID;
	float m_fTime;
	int m_nWeapon;
	int m_nLives;
	float m_fOrientation;
	float m_fFlashlightLife;
	int m_nAmmo;
	int m_nClip;
	float m_fAniSpeed;
	float m_ftest;

	int healthID;
public:
	int m_nHudID;
	vector<int> m_vFrameIDs;


	HUD();

	~HUD();

	void Update(float time);

	void Render();

	void Input();
};

#endif
