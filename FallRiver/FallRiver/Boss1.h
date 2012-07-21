#ifndef __Boss1_h__
#define __Boss1_h__

#include "Enemy.h"
#include <vector>
using namespace std;
#include "IListener.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"

typedef CObjectFactory< std::wstring, BaseObject> Factory;

class Boss1: public Enemy
{	
	DWORD m_dwFireDelay;

	Weapon*			m_pWeapon;
	ObjectManager*	m_pOM;
	Factory*		m_pOF;
	BaseObject*		m_cInTheWay;
	vector<Enemy*>	m_cEnemies;

	int m_nStages;
	int zombieHitID;
	int zombieWalkingID;

public: 
	// Spawn
	int m_nSpawnCounter;
	int enemies;
	float m_fSpawnTime;
	int oldSize;

	Boss1();
	~Boss1();

	void SetWeapon(Weapon* pWeapon) {m_pWeapon = pWeapon;}

	void Summon();

	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual bool CheckCollision(IObjects* pBase);

	virtual void HandleEvent(Event* pEvent);
	void SetEnemies(vector<Enemy*> enemies) { m_cEnemies = enemies; }
};

#endif
