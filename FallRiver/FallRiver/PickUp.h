#ifndef __PickUp_h__
#define __PickUp_h__

#include "BaseObject.h"
class AudioManager;

class PickUp : public BaseObject
{

	int ammoID;
	int batteriesID;
	int medicineID;
	int healthID;
	AudioManager* audio;

public:
	PickUp();
	virtual ~PickUp();

	virtual void Update(float fElapsedTime);

	virtual void Render();

	RECT GetRect();

	bool CheckCollision(BaseObject* pBase);
};

#endif
