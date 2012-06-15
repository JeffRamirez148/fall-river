
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

	if( pDI->KeyDown(DIK_RIGHT) && GamePlayState::GetInstance()->CanMoveRight() )
		SetVelX(-100);
	else if( pDI->KeyDown(DIK_LEFT) && GamePlayState::GetInstance()->CanMoveLeft() )
		SetVelX(100);
	else
		SetVelX(0);

	if( pDI->KeyDown(DIK_UP) && GamePlayState::GetInstance()->CanMoveUp() )
		SetVelY(100);
	else if( pDI->KeyDown(DIK_DOWN) && GamePlayState::GetInstance()->CanMoveDown() )
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
	return BaseCharacter::CheckCollision(pBase);
}

RECT Enemy::GetRect()
{
	RECT cRect = {GetPosX(), GetPosY(), GetPosX()+GetWidth(), GetPosY()+GetHeight()};

	return cRect;
}

void Enemy::HandleEvent(Event* aPEvent) 
{
}
