#include <Windows.h>
using namespace std;

#include "ObjectFactory.h"
#include "Light.h"
#include "Terrain.h"
#include "ShootingAi.h"
#include "ChasingAI.h"
#include "CompanionAI.h"
#include "Boss1.h"
#include "Player.h"
#include "BaseCharacter.h"
#include "BaseObject.h"
#include "Bullet.h"
#include "NPC.h"
#include "Boss2.h"

ShootingAi* ObjectFactory::CreateShooting() 
{
	return NULL;
}

ChasingAI* ObjectFactory::CreateChasing() 
{
	return NULL;
}

Boss1* ObjectFactory::CreateBoss1() 
{
	return NULL;
}

Boss2* ObjectFactory::CreateBoss2() 
{
	return NULL;
}

NPC* ObjectFactory::CreateNPC() 
{
	return NULL;
}

Terrain* ObjectFactory::CreateTerrain() 
{
	return NULL;
}

Level* ObjectFactory::CreateLevel() 
{
	return NULL;
}

BaseObject* ObjectFactory::CreateBaseObject() 
{
	return NULL;
}

BaseCharacter* ObjectFactory::CreateBaseCharacter() 
{
	return NULL;
}

CompanionAI* ObjectFactory::CreateCompanion() 
{
	return NULL;
}

Bullet* ObjectFactory::CreateBullet() 
{
	return NULL;
}

Light* ObjectFactory::CreateLight() 
{
	return NULL;
}

