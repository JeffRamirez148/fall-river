
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
	else if(GetPosY() < y-10)
		SetVelY(speed);
	else if(GetPosY() > y+10)
		SetVelY(-speed);

	if(GetPosX() == x)
		SetVelX(0);
	else if(GetPosX() < x-10)
		SetVelX(speed);
	else if(GetPosX() > x+10)
		SetVelX(-speed);
}

bool Enemy::CheckCollision(IObjects* pBase) 
{
	if( BaseCharacter::CheckCollision(pBase) )
	{
		if( pBase->GetObjectType() != OBJ_LEVEL)
		{
			if(pBase->GetObjectType() == OBJ_CHARACTER)
			{
				BaseCharacter* pCH = (BaseCharacter*)pBase;
				if(pCH->GetCharacterType() == CHA_ENEMY)
				{
					if(pBase->GetRect().left <= GetRect().right && GetRect().right - pBase->GetRect().left <= 5)
						SetPosX(float(pBase->GetRect().left-GetWidth()));
					else if(pBase->GetRect().right >= GetRect().left && pBase->GetRect().right - GetRect().left <= 5)
						SetPosX(float(pBase->GetRect().right));
					else if(pBase->GetRect().top <= GetRect().bottom && GetRect().bottom - pBase->GetRect().top <= 5)
						SetPosY(float(pBase->GetRect().top-GetHeight()));
					else if(pBase->GetRect().bottom >= GetRect().top && pBase->GetRect().bottom - GetRect().top <= 5)
						SetPosY(float(pBase->GetRect().bottom));
				}
			}
			return true;
		}
		else
		{
			if( pBase->CheckCollision(this) == true )
			{
				return true;
			}

		}
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
