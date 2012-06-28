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

	int swingMissID;
	int shotID;

	float m_fFireRate;
	float m_fReloadSpeed;
	float m_fRecoil;
	float m_fCurrRotation;
	float m_fFiringRange;

	BaseCharacter* m_pOwner;

	bool m_bMelee;

public: 
	Weapon();
	~Weapon();

	void Update(float fElapsedTime);

	void FireWeapon();

	bool Init(int wType, int nAmmo, int nDamage, float currRotation );

	void SetOwner(BaseCharacter* pOwner) {m_pOwner = pOwner;}
	BaseCharacter* GetOwner() {return m_pOwner;}
	int GetWeaponType() {return m_nWeaponType;}
	int GetAmmo() {return m_nAmmo;}
	int GetClip() {return m_nClip;}
	int GetDamage() {return m_nDamage;}
	float GetFireRate() {return m_fFireRate;}

	void Render();

	RECT GetRect();

	bool CheckCollision(IObjects* pBase);
};

#endif
