#include <Windows.h>

#ifndef __CompanionAI_h__
#define __CompanionAI_h__

#include "BaseCharacter.h"
#include "ObjectFactory.h"
#include "ObjectManager.h"

class Weapon;
class Event;
class Player;
class Enemy;

typedef CObjectFactory< std::wstring, BaseObject> Factory;

class CompanionAI: public BaseCharacter
{
private: 
	Factory* m_pOF;
	Player* m_cFriend;
	Weapon* m_cWeapon;
	vector<Enemy*>	m_cEnemies;

	int m_nFontID;
	int m_nStages;
	int m_nStep;
	int m_nNumTimes;
	int talkBox;
	bool teaching;
	bool talking;
	bool spawning;

	int m_nSpawnCounter;
	int enemies;
	float m_fSpawnTime;

	DWORD m_dwGunDelay;

public: 

	CompanionAI();
	~CompanionAI();

	bool IsTeaching() {return teaching;}
	void SetTeaching(bool teach) {teaching = teach;}

	bool IsSpawning() {return spawning;}

	int GetStage() {return m_nStages;}
	int GetStep() {return m_nStep;}
	void NextStep() { m_nStep++; }

	virtual void Update(float fElapsedTime);

	virtual void Render();

	virtual bool CheckCollision(IObjects* pBase);

	virtual void HandleEvent(Event* pEvent);

	void Spawn();
	void SpawnRight();
	void SetWeapon(Weapon* wep) {m_cWeapon = wep;}

	void SaySomething();
};

#endif
