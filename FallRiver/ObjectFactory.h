#include <Windows.h>

#ifndef __ObjectFactory_h__
#define __ObjectFactory_h__

class Light;
class Level;
class Terrain;
class ShootingAi;
class ChasingAI;
class CompanionAI;
class Boss1;
class Player;
class BaseCharacter;
class BaseObject;
class Bullet;
class NPC;
class Boss2;
class ObjectFactory;

class ObjectFactory
{
	public: 
	ShootingAi* CreateShooting();

	ChasingAI* CreateChasing();

	Boss1* CreateBoss1();

	Boss2* CreateBoss2();

	NPC* CreateNPC();

	Terrain* CreateTerrain();

	Level* CreateLevel();

	BaseObject* CreateBaseObject();

	BaseCharacter* CreateBaseCharacter();

	CompanionAI* CreateCompanion();

	Bullet* CreateBullet();

	Light* CreateLight();
};

#endif
