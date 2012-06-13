#include <Windows.h>

#include "Boss1.h"
#include "ObjectFactory.h"
#include "BaseCharacter.h"
#include "Enemy.h"

void Boss1::Update(float fElapsedTime)
{

}

void Boss1::Render()
{

}

bool Boss1::CheckCollision(BaseObject* pBase)
{
	if( BaseCharacter::CheckCollision(pBase) == false )
		return false;

	return true;
}

void Boss1::HandleEvent(Event* pEvent)
{

}




