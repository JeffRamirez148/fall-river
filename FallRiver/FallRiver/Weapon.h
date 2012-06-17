#ifndef __Weapon_h__
#define __Weapon_h__

#include "BaseObject.h"
#include "Player.h"

enum WEAPONTYPE { WPN_PISTOL = 0, WPN_SHOTGUN, WPN_RIFLE, WPN_MACHETE, WPN_MAX };

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
	float m_fFiringRange;
	DWORD m_dwTickCount;

	Player* m_pOwner;

	bool m_bMelee;

public: 
	Weapon();
	~Weapon();

	void Update(float fElapsedTime);

	bool Init(WEAPONTYPE wType, int nAmmo, int nDamage, float currRotation );

	void SetOwner(Player* pOwner) {m_pOwner = pOwner;}
	Player* GetOwner() {return m_pOwner;}

	void Render();

	RECT GetRect();

	bool CheckCollision(IObjects* pBase);
};

#endif
