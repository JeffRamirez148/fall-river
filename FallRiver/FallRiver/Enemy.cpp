
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
}

Enemy::~Enemy()
{

}

void Enemy::Update(float fElapsedTime) 
{
	DirectInput* pDI = DirectInput::GetInstance();

	if( pDI->KeyDown(DIK_RIGHT) )
		SetVelX(-100);
	else if( pDI->KeyDown(DIK_LEFT) )
		SetVelX(150);
	else
		SetVelX(0);

	if( pDI->KeyDown(DIK_UP) )
		SetVelY(150);
	else if( pDI->KeyDown(DIK_DOWN) )
		SetVelY(-100);
	else
		SetVelY(0);

	BaseCharacter::Update(fElapsedTime);
}

void Enemy::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 255, 0, 0);
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

void Enemy::HandleEvent(Event* aPEvent) 
{
}
