#include <Windows.h>
using namespace std;

#ifndef __Weapon_h__
#define __Weapon_h__

#include "BaseObject.h"

class Weapon: public BaseObject
{
private:
	int m_nWeaponType;
	int m_nAmmo;
	int m_nClip;
	int m_nDamage;
	float m_fFireRate;
	float m_fReloadSpeed;
	float m_fRecoil;
	float m_fCurrRotation;
	float m_fAccuracy;
	float m_fFiringRange;

public: 
	Weapon();
	~Weapon();

	void Update(float fElapsedTime);

	void Render();
};

#endif
