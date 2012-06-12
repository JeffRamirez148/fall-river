#include <Windows.h>
#include <vector>
using namespace std;

#ifndef __Player_h__
#define __Player_h__

#include "BaseCharacter.h"

class Quests;
class GamePlayState;
class Enemy;
class ObjectFactory;
class Weapon;
class Light;
class Player;

class Player: public BaseCharacter
{

private:
	int m_nFrameX;
	int m_nFrameY;
	vector<Weapon*> m_vpWeapons;
	vector<Light*> m_vpLights;

	Weapon* m_currWeapon;
	Light* m_currLight;

	int m_nScore;
	char* m_cName;
	bool m_bIsAlive;
	int m_nLives;
	vector<Quests*> m_vpActiveQuests;

public: 
	Player();
	~Player();

	void Update(float fElapsedTime);
	void Render();
	bool CheckCollision(BaseCharacter* pBase);
	bool CheckLifes();
	void AddQuest(Quests* pQuest);
	void AddWeapon(Weapon* pWeapon);
	void AddLight(Light* pLight);
};

#endif
