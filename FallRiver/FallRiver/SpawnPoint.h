


#ifndef __SpawnPoint_h__
#define __SpawnPoint_h__

#include "BaseObject.h"
#include "ObjectFactory.h"
#include "ObjectManager.h"

#include <string>
using namespace std;
class Enemy;

//typedef CObjectFactory< std::wstring, BaseObject> Factory;

class SpawnPoint :	public BaseObject
{
private:
	float m_fSpawnTime;
	bool m_bCanSpawn;
	bool m_bIsColliding;
	//Factory*		m_pOF;
	//ObjectManager*	m_pOM;

public:
	SpawnPoint(void);
	virtual ~SpawnPoint(void);
	virtual void Update(float fElapsedTime);
	virtual void Render();
	bool CanSpawn() { return m_bCanSpawn; }
	void SetSpawn(bool x) { m_bCanSpawn = x ;}
	void SetCollding(bool x) { m_bIsColliding = x ;}
	RECT GetRect();
	virtual bool CheckCollision(IObjects* pBase);
	bool TestCollision(Enemy* pEnemy );
};

#endif

