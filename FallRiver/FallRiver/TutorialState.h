#pragma once

#include "IMenuState.h"
#include <vector>
using namespace std;

#include "ObjectFactory.h"
#include "BaseObject.h"
#include "EventSystem.h"
#include "MessageSystem.h"

class ViewManager;
class DirectInput;
class AudioManager;
class Player;
class Level;
class HUD;
class Bush;
class Weapon;
class CompanionAI;
class Enemy;
class ObjectManager;
class Particle_Manager;

typedef CObjectFactory< std::wstring, BaseObject> Factory;

class TutorialState : public IMenuState
{
private:
	ViewManager*	m_pVM;
	DirectInput*	m_pDI;
	AudioManager*	m_pAM;
	Factory*		m_pOF;
	ObjectManager*	m_pOM;
	EventSystem*	m_pES;
	MessageSystem*	m_pMS;
	Particle_Manager*	m_pPM;


	// Characters
	Player*			m_cPlayer;
	Level*			m_clevel;
	HUD*			m_pHUD;
	CompanionAI*	m_cBuddy;
	vector<Enemy*>	m_cEnemies;
	vector<Bush*>	m_cBushes;
	Weapon*			m_cWeapon;

	// Sound Ids
	int backGroundID;
	int swingHitID;
	int soundID2;
	int musicID;

	bool right;
	bool goback;

	// Smoke particles
	int smokeL;

	// Blood Particles
	int bloodL1;
	int bloodL2;
	int bloodL3;
	int bloodL4;
	int bloodL5;
	int bloodL6;
	int bloodL7;
	int bloodL8;

	int goreL1;
	int goreL2;
	int goreL3;
	int goreL4;
	int goreL5;
	int goreL6;
	int goreL7;
	int goreL8;


	TutorialState(void);
	~TutorialState(void);
	TutorialState(const TutorialState&);
	TutorialState& operator=(const TutorialState&);

public:
	static TutorialState* GetInstance();

	Player* GetPlayer() {return m_cPlayer;}
	CompanionAI* GetCompanion() {return m_cBuddy;}

	void GoBack(bool go) {goback = go;}

	void Enter(void);
	void ReEnter();

	void Exit(void);

	bool Input(void);

	void Update(float fElapsedTime);

	void Render(void);

	void AddEnemy(Enemy* enemy) { m_cEnemies.push_back(enemy); }

	static void MessageProc(IMessage* pMsg);

};

