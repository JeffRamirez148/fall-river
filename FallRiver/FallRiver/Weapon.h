#include <Windows.h>
using namespace std;

#ifndef __Weapon_h__
#define __Weapon_h__

// #include "Player.h"
// #include "CompanionAI.h"
#include "BaseObject.h"

class Player;
class CompanionAI;
// class BaseObject;
class Weapon;

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
	void Update(float aTime);
	void Input();
	void Render();
};

#endif
