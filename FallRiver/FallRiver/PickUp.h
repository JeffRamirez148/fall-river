#ifndef __PickUp_h__
#define __PickUp_h__

#include "BaseObject.h"
class AudioManager;

enum PICKUPTYPES { PISTOL_AMMO = 0, SHOTGUN_AMMO, RIFLE_AMMO, MEDICINE, BATTERY, HEALTH };

class PickUp : public BaseObject
{

	int ammoID;
	int batteriesID;
	int medicineID;
	int healthID;
	int m_nPickUpType;
	AudioManager* audio;

public:
	PickUp();
	virtual ~PickUp();

	virtual void Update(float fElapsedTime);

	virtual void Render();

	RECT GetRect();

	int GetPickUpType() { return m_nPickUpType; }
	void SetPickUpType(int x) { m_nPickUpType = x; }

	bool CheckCollision(IObjects* pBase);
};

#endif
