#include <Windows.h>
#include <vector>
using namespace std;

#ifndef __Player_h__
#define __Player_h__

#include "BaseCharacter.h"

class Quests;
class GamePlayState;
class Weapon;
class Light;

class Player: public BaseCharacter
{

private:
	int m_nFrameX;
	int m_nFrameY;
	float m_fCurrRotation;
	vector<Weapon*> m_vpWeapons;
	vector<Light*> m_vpLights;

	Weapon* m_currWeapon;
	Light* m_currLight;

	int m_nScore;
	char* m_cName;
	bool m_bIsAlive;
	bool m_bIsHidden;
	int m_nLives;
	vector<Quests*> m_vpActiveQuests;

public: 
	Player();
	~Player();

	void Update(float fElapsedTime);
	void Render();
	bool CheckCollision(IObjects* pBase);
	bool CheckLifes();

	// If the Player is in a bush or closet
	bool CheckHidden() {return m_bIsHidden;}

	int GetScore() { return m_nScore;}
	int GetLives() { return m_nLives;}
	vector<Weapon*> GetWeapons() {return m_vpWeapons;}
	vector<Light*> GetLights() {return m_vpLights;}
	void SetScore(int sc) {m_nScore = sc;}
	void SetLives(int live) {m_nLives = live;}
	
	void AddQuest(Quests* pQuest);
	void AddWeapon(Weapon* pWeapon);
	void AddLight(Light* pLight);
};

#endif
