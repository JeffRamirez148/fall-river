
#include "Enemy.h"
#include "Player.h"
#include "GamePlayState.h"
#include "ViewManager.h"
#include "DirectInput.h"
#include "BaseCharacter.h"

Enemy::Enemy()
{
	m_nVelX = 0;
	m_nVelY = 0;
	m_nCharacterType = CHA_ENEMY;
	SetDirection(DIRE_UP);
}

Enemy::~Enemy()
{

}

void Enemy::Update(float fElapsedTime) 
{ 
	DirectInput* pDI = DirectInput::GetInstance();

	BaseCharacter::Update(fElapsedTime);
}

void Enemy::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 255, 0, 0);
}

void Enemy::MoveTo(float x, float y, float speed) 
{
	if(GetPosY() == y)
		SetVelY(0);
	else if(GetPosY() < y)
		SetVelY(speed);
	else if(GetPosY() > y+5)
		SetVelY(-speed);

	if(GetPosX() == x)
		SetVelX(0);
	else if(GetPosX() < x)
		SetVelX(speed);
	else if(GetPosX() > x+5)
		SetVelX(-speed);
}

bool Enemy::CheckCollision(IObjects* pBase) 
{
	if( BaseCharacter::CheckCollision(pBase) )
	{
		return true;
	}
	return false;
}

RECT Enemy::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight())};

	return cRect;
}

void Enemy::HandleEvent(Event* aPEvent) 
{
}
