#include <Windows.h>
#include <vector>
using namespace std;

#ifndef __Player_h__
#define __Player_h__

#include "BaseCharacter.h"
#include "AnimInfo.h"
#include "IListener.h"
#include "Quests.h"
#include "Weapon.h"
class Quests;

class GamePlayState;
class Weapon;
#include "Light.h"

enum PLAYERSTATES {PSTATE_IDLE = 0, PSTATE_SHOOT, PSTATE_SWING, PSTATE_CROUCH};

class Player: public BaseCharacter, public IListener
{

private:
	float m_fCurrRotation;
	vector<Weapon*> m_vpWeapons;
	vector<Light*> m_vpLights;

	Weapon* m_currWeapon;
	Light* m_currLight;

	DWORD m_dwGunCount;
	DWORD m_dwGunReset;

	int m_nScore;
	int m_nState;
public:
	int	m_nFontID;
	int questCounter;
	int completedQuest;
	vector<Quest_Struct*> m_vpActiveQuests;
private:
	char* m_cName;
	bool m_bIsAlive;
public:
	bool m_bIsHidden;
private:
	bool m_bTalking;
	int m_nLives;
	int walkingID;
	int hitID;
	bool lightOn;
public:
	int battery;
private:
	float batteryTime;

	AnimInfo m_playerAnim;

public: 
	Player();
	~Player();


	void Update(float fElapsedTime);
	void Render();
	bool CheckCollision(IObjects* pBase);
	bool CheckLifes();
	void HandleEvent(Event* aPEvent);

	// If the Player is in a bush or closet
	bool CheckHidden() {return m_bIsHidden;}

	bool IsTalking() {return m_bTalking;}

	int GetScore() { return m_nScore;}
	int GetAmmo();
	int GetWeaponType();
	int GetClip();

	int GetLives() { return m_nLives;}
	vector<Weapon*> GetWeapons() {return m_vpWeapons;}
	vector<Light*> GetLights() {return m_vpLights;}
	void SetScore(int sc) {m_nScore = sc;}
	void SetLives(int live) {m_nLives = live;}
	
	void AddQuest(Quest_Struct* pQuest);
	void AddWeapon(Weapon* pWeapon);
	void AddLight(Light* pLight);

	void SetAnimation(int nAnimID) { m_playerAnim.curAnimID = nAnimID;}
};

#endif
