
#include "Enemy.h"
#include "Player.h"
#include "GamePlayState.h"
#include "BaseCharacter.h"

void Enemy::HandleEvent(Event* aPEvent) 
{
}

void Enemy::Update(float fElapsedTime) 
{
}

void Enemy::Render() 
{
}

void Enemy::MoveTo(int c, int y) 
{
}

bool Enemy::CheckCollision(BaseObject* pBase) 
{
	return false;
}

RECT Enemy::GetRect()
{
	RECT cRect = {GetPosX(), GetPosY(), GetPosX()+GetWidth(), GetPosY()+GetHeight()};

	return cRect;
}
