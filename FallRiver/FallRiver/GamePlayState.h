#include <vector>
using namespace std;

#ifndef __GamePlayState_h__
#define __GamePlayState_h__

#include "IMenuState.h"
#include "BaseObject.h"
#include "ObjectFactory.h"
#include "MessageSystem.h"
#include "IListener.h"

class ViewManager;
class AudioManager;
class ObjectManager;
class OptionsMenuState;
class Particle_Manager;
class EventSystem;
class Level;
class Weapon;
class DirectInput;
class Enemy;
class Player;
class HUD;
class NPC;
class IMessage;
class SpawnPoint;
class Bush;
class CompanionAI;
class Boss1;
class Boss2;

typedef CObjectFactory< std::wstring, BaseObject> Factory;

class GamePlayState : public IMenuState, public IListener
{
private: 
	// Wrapper Memebers
	Level*				m_clevel;
	ViewManager*		m_pVM;
	DirectInput*		m_pDI;
	AudioManager*		m_pAM;
	Factory*			m_pOF;
	ObjectManager*		m_pOM;
	EventSystem*		m_pES;
	MessageSystem*		m_pMS;
	Particle_Manager*	m_pPM;

	int SpawnEnemyAniID;
	int bush;
	
	// Sound Ids
	int soundID2;
//	int musicID;
	int logID;
//	int pianoID;
//	int backGroundID;
	int swingHitID;

	// Rain particles
	int rainA;
	int rainL;
	// Smoke particles
	int smokeL;

	// Fire Particles
	int fire1L;
	int fire2L;
	int fire3L;
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

	// Data Members
	float fTime;

	// Characters In the world
	Player*						m_cPlayer;
	CompanionAI*				m_cBuddy;
	vector<Enemy*>				m_cEnemies;
	vector<SpawnPoint*>			m_cSpawn;
	vector<Bush*>				m_cBushes;
	vector<NPC*>				m_cNpcs;
	Boss1*						m_cBoss1;
	Boss2*						m_cBoss2;
	Weapon*						m_cWeapon;
	vector<int>					fireA;
	vector<RECT>				streetLights;
	// For Everyone else on the screen
	POINTFLOAT camera;

	// Win/Lose/Quest Flags
	bool winLose;
	
	// Private Constructors
	GamePlayState();
	~GamePlayState()	{ }
	GamePlayState(const GamePlayState&);
	GamePlayState& operator=(const GamePlayState&);

public:
	int hospitalX;
	int hospitalY;

	int GetGoreL1() { return goreL1;}
	int GetGoreL2() { return goreL2;}
	int GetGoreL3() { return goreL3;}
	int GetGoreL4() { return goreL4;}
	int GetGoreL5() { return goreL5;}
	int GetGoreL6() { return goreL6;}
	int GetGoreL7() { return goreL7;}
	int GetGoreL8() { return goreL8;}

	int GetBloodL1() { return bloodL1;}
	int GetBloodL2() { return bloodL2;}
	int GetBloodL3() { return bloodL3;}
	int GetBloodL4() { return bloodL4;}
	int GetBloodL5() { return bloodL5;}
	int GetBloodL6() { return bloodL6;}
	int GetBloodL7() { return bloodL7;}
	int GetBloodL8() { return bloodL8;}

	void SetGoreL1(int id) { goreL1 = id;}
	void SetGoreL2(int id) { goreL2 = id;}
	void SetGoreL3(int id) { goreL3 = id;}
	void SetGoreL4(int id) { goreL4 = id;}
	void SetGoreL5(int id) { goreL5 = id;}
	void SetGoreL6(int id) { goreL6 = id;}
	void SetGoreL7(int id) { goreL7 = id;}
	void SetGoreL8(int id) { goreL8 = id;}

	void SetBloodL1(int id) { bloodL1 = id;}
	void SetBloodL2(int id) { bloodL2 = id;}
	void SetBloodL3(int id) { bloodL3 = id;}
	void SetBloodL4(int id) { bloodL4 = id;}
	void SetBloodL5(int id) { bloodL5 = id;}
	void SetBloodL6(int id) { bloodL6 = id;}
	void SetBloodL7(int id) { bloodL7 = id;}
	void SetBloodL8(int id) { bloodL8 = id;}
	void ChangeLevel();
	int GetNumEnemies() {return m_cEnemies.size(); }
	int GetLogID() {return logID;}
	vector<int> GetFireA(void) { return fireA;}
	bool questFlag;
	HUD*			m_pHUD;
	Player* GetPlayer() {return m_cPlayer;}
	CompanionAI* GetCompanion() {return m_cBuddy;}
	void SetCompanion(CompanionAI* comp) {m_cBuddy = comp;}
	void SetPlayer(Player* pPlayer) {m_cPlayer = pPlayer;}
	void SetHud(HUD* hud) {m_pHUD = hud;}

	void SetWinLose(bool wl)	{winLose = wl;}
	bool GetWinLose()			{return winLose;}

	Level* GetLevel() {return m_clevel; }

	POINTFLOAT GetCamera() {return camera;}
	void SetCamera(float x, float y) {camera.x = x; camera.y = y;}

	void Enter();

	void Exit();

	bool Input();

	void Update(float fElapsedTime);

	void Render();
	void ReEnter();

	static GamePlayState* GetInstance();

	static void MessageProc(IMessage* pMsg);
	vector<NPC*>* GetNPCs(void) { return &m_cNpcs; }

	int GetSpawnEnemyID() { return SpawnEnemyAniID; }
	void AddEnemy(Enemy* enemy) { m_cEnemies.push_back(enemy); }
	vector<Enemy*> GetEnemies() {return m_cEnemies;}
	vector<RECT> GetStreelights() { return streetLights;}
	void HandleEvent(Event* aPEvent);
};

#endif
