#include <Windows.h>


#ifndef __HUD_h__
#define __HUD_h__

// #include "GamePlayState.h"
// #include "ViewManager.h"
#include <tchar.h>
#include <string.h>
#include <vector>
#include "AnimInfo.h"
#include "BaseCharacter.h"

using namespace std;

class GamePlayState;
class ViewManager;
class HUD;

struct tLocation
{
	float x,y;
};


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
	float m_fRotation;
	AnimInfo m_aClipAnim;
	bool m_bShot;
	tLocation m_pTarget;
	float ScreenOffsetX;
	float ScreenOffsetY;
	int healthID;
public:
	int m_nHudID;
	int m_nArrowID;
	int m_nClipID;
	//vector<Clip> m_vClip;
	vector<int> m_vFrameIDs;


	HUD();

	~HUD();
	void SetTarget( float x, float y);

	void Update(float time);

	void Render();

	void Input();
};

#endif
