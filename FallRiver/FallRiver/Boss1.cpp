#include "Boss1.h"
#include "ObjectFactory.h"
#include "BaseCharacter.h"
#include "Enemy.h"

Boss1::Boss1()
{

}

Boss1::~Boss1()
{

}

void Boss1::Update(float fElapsedTime)
{
	Enemy::Update(fElapsedTime);
}

void Boss1::Render()
{

}

bool Boss1::CheckCollision(IObjects* pBase)
{
	if( BaseCharacter::CheckCollision(pBase) == false )
		return false;

	return true;
}

void Boss1::HandleEvent(Event* pEvent)
{

}




