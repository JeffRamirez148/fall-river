#include <Windows.h>
#include <vector>
using namespace std;

#ifndef __Player_h__
#define __Player_h__

// #include "Quests.h"
// #include "GamePlayState.h"
// #include "Enemy.h"
// #include "ObjectFactory.h"
// #include "Weapon.h"
// #include "Light.h"
#include "BaseCharacter.h"

class Quests;
class GamePlayState;
class Enemy;
class ObjectFactory;
class Weapon;
class Light;
// class BaseCharacter;
class Player;

class Player: public BaseCharacter
{

private:
	int m_nFrameX;
	int m_nFrameY;
	vector<Weapon*> m_vpWeapons;
	vector<Light*> m_vpLights;
	int m_nScore;
	char* m_cName;
	bool m_bIsAlive;
	int m_nLives;
	vector<Quests*> m_vpActiveQuests;

public: 
	void Update(float aFElapsedTime);
	void Render();
	bool CheckCollision(BaseCharacter* aPBase);
	bool CheckLifes();
	void AddQuest(Quests* aPQuest);
	void AddWeapon(Weapon* aPWeapon);
	void AddLight(Light* aPLight);
};

#endif
