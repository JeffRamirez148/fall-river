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

enum PLAYERSTATES {PSTATE_IDLE = 0, PSTATE_SHOOT, PSTATE_SWING, PSTATE_CROUCH, PSTATE_DEAD, PSTATE_RELOAD};

class Player: public BaseCharacter, public IListener
{
	bool lose;
	float m_fCurrRotation;
	vector<Weapon*> m_vpWeapons;
	vector<Light*> m_vpLights;

	Weapon* m_currWeapon;
	int m_ncurrWeap;
	Light* m_currLight;

	DWORD m_dwGunCount;
	DWORD m_dwGunReset;
	DWORD m_dwDeathTime;
	DWORD m_dwReloadTime;

	int m_nScore;
	int m_nState;
	int flashLightType; // 0 - Flashlight, 1 - Maglight, 2 - Lantern, 3 - Lighter
	float decreaseTime;
	int flickerRate;
	int m_nlightglare;
	float dammageTimer;
	float pushTimer;

	char* m_cName;
	bool m_bIsAlive;
	bool m_bLocked;
	bool m_bmove;

	bool m_bTalking;
	int m_nLives;
	int walkingID;
	int hitID;
	int flashLightID;
	int weaponChangeID;
	int sheathID;

	bool lightOn;
	float batteryTime;

	float m_fTimePlayed;

public:
	int	m_nFontID;
	int questCounter;
	int completedQuest;
	vector<Quest_Struct*> m_vpActiveQuests;
	vector<Quest_Struct*> m_vpFinishedQuests;

	bool m_bIsHidden;
	bool m_bHasMedicine;
	bool m_bShotBush;
	float m_fshotTimer;

	int battery;
	bool questLogToggle;

	Player();
	~Player();

	void Update(float fElapsedTime);
	void Render();
	bool CheckCollision(IObjects* pBase);
	bool CheckLifes();
	void HandleEvent(Event* aPEvent);
	
	int GetLightType() { return flashLightType; }

	int GetBattery() { return battery; }
	void SetBattery(int nBattery) { battery = nBattery; }

	int GetHitID(void) { return hitID;}
	// If the Player is in a bush or closet
	bool CheckHidden() {return m_bIsHidden;}

	// If the players flashlight is on
	bool IsOn() {return lightOn;}

	bool IsTalking() {return m_bTalking;}

	bool CanMove() {return m_bmove;}
	void SetMove(bool move) {m_bmove = move;}
	bool IsLocked() {return m_bLocked;}
	void SetLocked(bool lock) {m_bLocked = lock;}

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

	void MoveTo(float x, float y, float speed);
	void SetAnimation(int nAnimID) { m_playerAnim.curAnimID = nAnimID;}
	void setLose(bool lost) { lose = lost; }
	void SetTimePlayed (float fTime) { m_fTimePlayed = fTime;}
	float GetTimePlayed() {return m_fTimePlayed; }
};

#endif
